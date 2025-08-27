#include <iostream>

#include <manapihttp/ManapiInitTools.hpp>
#include <MaxBot.hpp>

int main() {
    manapi::init_tools::log_trace_init(manapi::debug::LOG_TRACE_LOW);

    manapi::async::context::threadpoolfs(2);
    manapi::async::context::gbs = manapi::async::context::blockedsignals();

    auto ctx = manapi::async::context::create(2).unwrap();
    ctx->eventloop()->setup_handle_interrupt();

    auto server_ctx = manapi::net::http::server_ctx::create().unwrap();

    ctx->run(ctx, 0, [server_ctx] (auto cb) -> void {
        manapi::maxbot maxbot;

        std::set<size_t> states;

        manapi::async::run ([&states, maxbot, server_ctx] () mutable MANAPIHTTP_NOEXCEPT
            -> manapi::future<> {
            auto resread = co_await manapi::filesystem::async_read("../trash/config.json");
            manapi::json config = manapi::json::parse(
                (resread.unwrap())).unwrap();

            maxbot.token(config["maxbot"].as_string());
            std::string openrouter_key = config["openrouter"].as_string();

            maxbot.on("message_created", [&states](manapi::maxbot &self, manapi::json &data)
                    -> manapi::future<bool> {
                auto const user_id = data["message"]["sender"]["user_id"].as_integer();
                auto const chat_id = data["message"]["recipient"]["chat_id"].as_integer();
                auto const &text = data["message"]["body"]["text"];

                if (!text.is_string()
                    || !text.as_string().starts_with('/'))
                    co_return false;

                /* is a command */

                std::string_view const cmd{text.as_string().data() + 1, text.as_string().size() - 1};

                if (cmd == "start") {
                    auto res_send = co_await self.send_message(user_id, chat_id, {
                        {"text", std::format("Hello, {}. You are here.\nWhat do you want to ask me?",
                            data["message"]["sender"]["first_name"].as_string())}
                    });
                    manapi::json response = (res_send.unwrap());
                }
                else if (cmd == "ai enable") {
                    states.insert(user_id);
                }
                else if (cmd == "ai disable") {
                    states.erase(user_id);
                }
                else {
                    auto send_res = co_await self.send_message(user_id, chat_id, { {"text", std::format("Invalid command: {}", cmd)}});
                    manapi::json response = (send_res).unwrap();
                }

                co_return true;
            });

            maxbot.on("message_created", [openrouter_key, &states](manapi::maxbot &self, manapi::json &data)
                -> manapi::future<bool> {
                auto const user_id = data["message"]["sender"]["user_id"].as_integer();
                auto const chat_id = data["message"]["recipient"]["chat_id"].as_integer();
                auto const &firstname = data["message"]["sender"]["first_name"].as_string();

                if (!states.contains(user_id)) {
                    std::string_view text;
                    if (data["message"]["body"].contains("text"))
                        text = data["message"]["body"]["text"].as_string();
                    else
                        text = "no response";

                    auto res_send = co_await self.send_message(user_id, chat_id, {{"text", text}});
                    auto response = res_send.unwrap();

                    co_return true;
                }

                ssize_t const from = std::chrono::duration_cast<std::chrono::seconds>(
                    std::chrono::system_clock::now().time_since_epoch()).count();

                auto res_send = co_await self.get_messages(manapi::json {
                    {"chat_id", chat_id},
                    {"count", 15}
                });
                manapi::json history = res_send.unwrap();

                manapi::json memory = manapi::json::array();

                for (auto &history_block : history["messages"].each()) {
                    if (history_block["sender"]["is_bot"].as_bool()) {
                        /* assistant */
                        memory.push_back(manapi::json::object({
                            {"role", "assistant"}
                        }));
                    }
                    else {
                        memory.push_back(manapi::json::object({
                            {"role", "user"}
                        }));
                    }

                    if (history_block["body"]["text"].is_string())
                        (*memory.as_array().rbegin())["content"] = history_block["body"]["text"].as_string_cast();
                    else
                        (*memory.as_array().rbegin())["content"] = std::string{};
                }

                memory.push_back({
                    {"role", "user"},
                    {"content", std::move(data["message"]["body"]["text"])}
                });

                std::string err{};

                try {
                    auto jdata = manapi::json({
                        {"model", "deepseek/deepseek-r1-0528:free"},
                        {"messages", std::move(memory)}
                    });
                    auto response_res = co_await manapi::net::fetch2::fetch("https://openrouter.ai/api/v1/chat/completions", {
                        {"headers", {
                            {"content-type", "application/json"},
                            {"authorization", std::format("Bearer {}", openrouter_key)}
                        }},
                        {"method", "POST"}
                    }, jdata.dump());
                    auto response = response_res.unwrap();

                    auto msg_res = co_await response.json();
                    auto msg = msg_res.unwrap();
                    std::string const text = std::move(std::move(msg["choices"][0]["message"]["content"].as_string()));
                    for (size_t pos = 0; pos < text.size(); pos+=4000) {
                        auto send_res = co_await self.send_message(user_id, chat_id, {
                               {"text", text.substr(pos, 4000)},
                        });
                        send_res.unwrap();
                    }
                }
                catch (std::exception const &e) {
                    err = e.what();
                }

                if (!err.empty()) {
                    auto send_res = co_await self.send_message(user_id, chat_id, {
                            {"text", std::format("error was occurred due to {}", err)},
                    });
                    manapi::json response = send_res.unwrap();
                }

                co_return true;
            });

            auto res = co_await maxbot.bind(server_ctx, "127.0.0.1", "8888", {
                {"site", "http://127.0.0.1:8888"}
            });
            res.unwrap();
        });

        cb();
    }).unwrap();

    manapi::clear_tools::curl_library_clear();
    manapi::clear_tools::ev_library_clear();
    manapi::clear_tools::ssl_library_clear();

    return 0;
}