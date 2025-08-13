#pragma once

#include <manapihttp/ManapiHttp.hpp>
#include <manapihttp/ManapiFilesystem.hpp>
#include <manapihttp/services/ManapiFetch2.hpp>
#include <manapihttp/ManapiJson.hpp>

#define MANAPI_MAXBOT_STATUS_WRAP(n__) auto response = co_await n__; if (!response) { co_return response.err(); } \
co_return manapi::json::parse(response.unwrap());
#define MANAPI_MAXBOT_STATUS_WRAP_RES(n__) auto response = co_await n__; if (!response) {co_return response.err(); } \
auto res = manapi::json::parse(response.unwrap()); \
if (!res) { co_return res.err(); } co_return this->generate_res_(res.unwrap());

namespace manapi {
    /**
     *
     * object PhotoAttachmentPayload
     * @code
     *  {
     *      photo_id: integer,
     *      token: string,
     *      url: string
     *  }
     * @endcode
     *
     * object MediaAttachmentPayload
     * @code
     *  {
     *      type: strirng("video"),
     *      payload: {
     *      url: string,
     *      token: string|none
     *  }
     * @endcode
     *
     * object FileAttachmentPayload
     * @code
     *  {
     *      url: string,
     *      token: string|none
     *  },
     * @endcode
     *
     * object StickerAttachmentPayload
     * @code
     *  {
     *      url: string,
     *      code: string|none
     *  }
     * @endcode
     *
     * object ContactAttachmentPayload
     * @code
     *  {
     *      vcf_info: string|null|none,
     *      max_info: object User|null
     *  }
     * @endcode
     *
     * object ShareAttachmentPayload
     * @code
     *  {
     *      url: string|null|none,
     *      token: string|null|none
     *  }
     * @endcode
     *
     * object Attachment
     * @code
     *      {
     *          type: string("image"),
     *          payload: object PhotoAttachmentPayload,
     *      }|{
     *          type: string("video"),
     *          payload: object MediaAttachmentPayload,
     *          thumbnail: {
     *              url: string
     *          }|null,
     *          width: integer|null|none,
     *          height: integer|null|none,
     *          duration: integer|null|none
     *      }|{
     *          type: string("audio"),
     *          payload: object MediaAttachmentPayload,
     *          transcription: string|null|none
     *      }|{
     *          type: string("file"),
     *          payload: object FileAttachmentPayload,
     *          filename: string|none,
     *          size: integer|none
     *      }|{
     *          type: string("sticker"),
     *          payload: object StickerAttachmentPayload,
     *          width: integer|none,
     *          height: integer|none
     *      }|{
     *          type: string("contact"),
     *          payload: object ContactAttachmentPayload
     *      }|{
     *          type: string("shared"),
     *          payload: object ShareAttachmentPayload
     *      }|{
     *          type: string("location"),
     *          latitude: decimal|none,
     *          longitude: decimal|none
     *      }|{
     *          type: string("inline_keyboard"),
     *          payload: object Keyboard
     *      }
     * @endcode
     *
     * object MessageBody
     * @code
     * {
     *      mid: string,
     *      seq: integer,
     *      text: string|null,
     *      attachments: object Attachment[]|null,
     *      markup: object MarkupElement[]|null|none
     *  }
     * @endcode
     *
     * object BotCommand
     * @code
     *  {
     *      name: string(>=1 <=64),
     *      description: string(>=1 <=128)|null|none
     *  }
     * @endcode
     *
     * object PhotoAttachmentRequestPayload
     * @code
     *  {
     *      url: string|null|none,
     *      token: string|null|none,
     *      photos: object|null|none
     *  }
     * @endcode
     *
     * enum ChatType
     * @code
     * string("dialog")|string("chat")
     * @endcode
     *
     * enum ChatStatus
     * @code
     * string("active")|string("removed")|string("left")|string("closed")|string("suspended")
     * @endcode
     *
     * object UserWithPhoto
     * @code
     *  {
     *      user_id: integer,
     *      first_name: string,
     *      last_name: string|none,
     *      username: string|null,
     *      is_bot: bool,
     *      last_activity_time: integer,
     *      description: string|null|none,
     *      avatar_url: string|none,
     *      full_avatar_url: string|none
     *  }
     * @endcode
     *
     * object User
     * @code
     *  {
     *      user_id: integer,
     *      first_name: string,
     *      last_name: string|none,
     *      username: string|null,
     *      is_bot: bool,
     *      last_activity_time: integer
     *  }
     * @endcode
     *
     * object Recipient
     * @code
     *  {
     *      chat_id: integer|null,
     *      chat_type: enum ChatType,
     *      user_id: integer|null
     *  }
     * @endcode
     *
     * enum MessageLinkType
     * @code
     * string("forward")|string("reply")
     * @endcode
     *
     * object MessageStat
     * @code
     *  {
     *      view: integer
     *  }
     * @endcode
     *
     * object Message
     * @code
     *  {
     *      sender: object User,
     *      recipient: object Recipient,
     *      timestamp: integer,
     *      link: {
     *          type: enum MessageLinkType,
     *          sender: object User,
     *          chat_id: integer|none,
     *          message: object MessageBody
     *      },
     *      body: object MessageBody,
     *      stat: object MessageStat|null,
     *      url: string|null|none
     *
     *  }
     * @endcode
     *
     * object Image
     * @code
     *  {
     *      url: string
     *  }
     * @endcode
     *
     * object Chat
     * @code
     *  {
     *      chat_id: integer,
     *      type: enum ChatType,
     *      status: enum ChatStatus,
     *      title: string|null,
     *      icon: object Image|null,
     *      last_event_time: integer,
     *      participants_count: integer,
     *      owner_id: integer|null|none,
     *      participants: object|null|none,
     *      is_public: bool,
     *      link: string|null|none,
     *      description: string|null,
     *      dialog_with_user: object UserWithPhoto|null,
     *      messages_count: integer|null|none,
     *      chat_message_id: string|null|none,
     *      pinned_message: object Message|null
     *  }
     * @endcode
     */
    class maxbot {
    public:
        using action_cb_t = std::move_only_function<manapi::future<bool>(maxbot &self, manapi::json &data)>;
        using response_status_t = std::pair<bool, std::string>;

        struct data_t {
            std::string token;
            manapi::timer timer;
            std::map<std::string, std::map<std::size_t, std::unique_ptr<action_cb_t>>> handlers;
        };

        maxbot (std::shared_ptr<maxbot::data_t> data);

        maxbot ();

        maxbot (std::string token);

        ~maxbot();

        /**
         * Создаст нового наблюдателя
         *
         * Данные будут примерно такими
         * @code
         *  {
         *      update_type: string,
         *      timestamp: integer,
         *      message: {
         *          sender: object User {
         *              user_id: integer,
         *              first_name: string,
         *              last_name: string|none,
         *              username: string|null,
         *              is_bot: boolean,
         *              last_activity_time: integer
         *          },
         *          recipient: object Recipient {
         *              chat_id: integer|null,
         *              chat_type: enum ChatType "dialog"|"chat",
         *              user_id: integer|null
         *          },
         *          timestamp: integer,
         *          stat: object MessageStat {
         *              views: integer
         *          }|null,
         *          url: string|null|none,
         *          link: object LinkedMessage {
         *              type: enum MessageLinkType "forward"|"reply",
         *              sender: object User,
         *              chat_id: integer|none,
         *              message: object MessageBody {
         *                  mid: string,
         *                  seq: integer,
         *                  text: string|null,
         *                  attachments: object Attachment[]|null,
         *                  markup: {
         *                      type: string,
         *                      from: integer,
         *                      length: integer
         *                  }[]|null
         *              }
         *          }|null,
         *          body: object MessageBody
         *      },
         *      user_locale: string|null|none
         *  }
         * @endcode
         *
         * @param action action name
         * @param callback action callback
         * @param cancellation Токен отмены
         */

        void on (std::string action, action_cb_t callback, manapi::async::cancellation_action cancellation = nullptr);

        void token (std::string token);

        void bind (std::string ip, std::string port);

        manapi::error::status bind (std::size_t ms = 0, std::size_t limit = 100) MANAPIHTTP_NOEXCEPT;

        void stop ();

        /**
         * Возвращает информацию о текущем боте,
         * который идентифицируется с помощью токена доступа.
         * Метод возвращает ID бота, его имя и аватар (если есть).
         *
         * Схема результата
         * @code
         *  {
         *      user_id: integer,
         *      first_name: string,
         *      last_name: string|none,
         *      username: string|null,
         *      is_bot: bool,
         *      last_activity_time: integer,
         *      description: string(<=16000)|null|none,
         *      avatar_url: string|none,
         *      full_avatar_url: string|none,
         *      commands: object BotCommand[<=32]|none
         *  }
         * @endcode
         *
         * @param cancellation Токен отмены
         * @return
         *
         * @exception manapi::exception Default Manapi Exception
         */
        manapi::future<manapi::error::status_or<manapi::json>> me (manapi::async::cancellation_action cancellation = nullptr);

        /**
         * Позволяет изменить информацию о текущем боте.
         * Заполняйте только те поля, которые требуется обновить.
         * Все остальные останутся без изменений.
         *
         * Схема meta
         * @code
         *  {
         *      name: string(>=1 <=64)|null|none,
         *      description: string(>=1 <=16000)|null|none,
         *      commands: object BotCommand[<=32]|null|none,
         *      photo: object PhotoAttachmentRequestPayload|null
         *  }
         * @endcode
         *
         * Схема результата
         * @code
         *  {
         *      user_id: integer,
         *      first_name: string,
         *      last_name: string|none,
         *      username: string|null,
         *      is_bot: bool,
         *      last_activity_time: integer,
         *      description: string(<=16000)|null|none,
         *      avatar_url: string|none,
         *      full_avatar_url: string|none,
         *      commands: object BotCommand[<=32]|none
         *  }
         * @endcode
         *
         * @param meta Тело запроса
         * @param cancellation Токен отмены
         * @return
         *
         * @exception manapi::exception Default Manapi Exception
         */

        manapi::future<manapi::error::status_or<manapi::json>> me (manapi::json meta, manapi::async::cancellation_action cancellation = nullptr);

        /**
         * Возвращает информацию о чатах, в которых участвовал бот.
         * Результат включает список чатов и маркер для перехода к следующей странице.
         *
         *
         * Схема результата
         * @code
         *  {
         *      chats: object Chat[<=50],
         *      marker: integer|null
         *  }
         * @endcode
         *
         *
         * @param count Количество запрашиваемых чатов
         * @param marker Указатель на следующую страницу данных. Для первой страницы передайте 1
         * @param cancellation Токен отмены
         * @return
         *
         * @exception manapi::exception Default Manapi Exception
         */

        manapi::future<manapi::error::status_or<manapi::json>> chats (int count = 50, ssize_t marker = 1, manapi::async::cancellation_action cancellation = nullptr);

        /**
         * Возвращает информацию о чате по его публичной ссылке,
         * либо информацию о диалоге с пользователем по его username.
         *
         * Схема результата
         * @code
         *  {
         *      chat_id: integer,
         *      type: enum ChatType,
         *      status: enum ChatStatus,
         *      title: string|null,
         *      icon: object Image|null,
         *      last_event_time: integer,
         *      participiants_count: integer,
         *      owner_id: integer|null|none,
         *      participiants: object|null|none,
         *      is_public: bool,
         *      link: string|null|none,
         *      description: string|null,
         *      dialog_with_user: object UserWithPhoto|null,
         *      messages_count: integer|null|none,
         *      chat_message_id: string|null|none,
         *      pinned_message: object Message|null
         *  }
         * @endcode
         *
         * @param link Публичная ссылка на чат или username пользователя. Должна соответствовать регулярному выражению @?[a-zA-Z]+[a-zA-Z0-9-_]*
         * @param cancellation Токен отмены
         * @return
         *
         * @exception manapi::exception Default Manapi Exception
         */

        manapi::future<manapi::error::status_or<manapi::json>> chat (std::string link, manapi::async::cancellation_action cancellation = nullptr);

        /**
         * Возвращает информацию о чате по его ID.
         *
         * Схема результата
         * @code
         *  {
         *      chat_id: integer,
         *      type: enum ChatType,
         *      status: enum ChatStatus,
         *      title: string|null,
         *      icon: object Image|null,
         *      last_event_time: integer,
         *      participiants_count: integer,
         *      owner_id: integer|null|none,
         *      participiants: object|null|none,
         *      is_public: bool,
         *      link: string|null|none,
         *      description: string|null,
         *      dialog_with_user: object UserWithPhoto|null,
         *      messages_count: integer|null|none,
         *      chat_message_id: string|null|none,
         *      pinned_message: object Message|null
         *  }
         * @endcode
         *
         * @param chat_id ID запрашиваемого чата
         * @param cancellation Токен отмены
         * @return
         *
         * @exception manapi::exception Default Manapi Exception
         */
        manapi::future<manapi::error::status_or<manapi::json>> chat (ssize_t chat_id, manapi::async::cancellation_action cancellation = nullptr);

        /**
         * Позволяет редактировать информацию о чате,
         * включая название, иконку и закреплённое сообщение.
         *
         * Схема тела
         * @code
         *  {
         *      icon: object PhotoAttachmentRequestPayload|null,
         *      title: string|null|none,
         *      ping: string|null|none,
         *      notify: bool|null|none
         *  }
         * @endcode
         *
         * Схема результата
         * @code
         *  {
         *      chat_id: integer,
         *      type: enum ChatType,
         *      status: enum ChatStatus,
         *      title: string|null,
         *      icon: object Image|null,
         *      last_event_time: integer,
         *      participiants_count: integer,
         *      owner_id: integer|null|none,
         *      participiants: object|null|none,
         *      is_public: bool,
         *      link: string|null|none,
         *      description: string|null,
         *      dialog_with_user: object UserWithPhoto|null,
         *      messages_count: integer|null|none,
         *      chat_message_id: string|null|none,
         *      pinned_message: object Message|null
         *  }
         * @endcode
         *
         * @param chat_id ID чата
         * @param data Тело запроса
         * @param cancellation Токен отмены
         * @return
         *
         * @exception manapi::exception Default Manapi Exception
         */
        manapi::future<manapi::error::status_or<manapi::json>> chat (ssize_t chat_id, manapi::json data, manapi::async::cancellation_action cancellation = nullptr);

        /**
         * Удаляет чат для всех участников
         *
         * @param chat_id ID чата
         * @param cancellation Токен отмены
         * @return pair обьект, где первое принимает значение true, если запрос был успешным, false в противном случае,
         *  а второе объяснительное сообщение, если результат не был успешным
         *
         * @exception manapi::exception Default Manapi Exception
         */
        manapi::future<manapi::error::status_or<response_status_t>> remove_chat (ssize_t chat_id, manapi::async::cancellation_action cancellation = nullptr);

        /**
         * 
         * @param chat_id ID чата
         * @param action Enum: "typing_on" "sending_photo" "sending_video" "sending_audio" "sending_file" "mark_seen"
         * @param cancellation Токен отмены
         *
         * - "typing_on" — Бот набирает сообщение.
         * - "sending_photo" — Бот отправляет фото.
         * - "sending_video" — Бот отправляет видео.
         * - "sending_audio" — Бот отправляет аудиофайл.
         * - "sending_file" — Бот отправляет файл.
         * - "mark_seen" — Бот помечает сообщения как прочитанные.
         *
         * @return pair обьект, где первое принимает значение true, если запрос был успешным, false в противном случае,
         *  а второе объяснительное сообщение, если результат не был успешным
         *
         * @exception manapi::exception Default Manapi Exception
         */
        manapi::future<manapi::error::status_or<response_status_t>> status_chat (ssize_t chat_id, std::string action, manapi::async::cancellation_action cancellation = nullptr);


        /**
         * Возвращает закрепленное сообщение в чате.
         *
         * Схема результата
         * @code
         *  {
         *      message: object Message|null
         *  }
         * @endcode
         *
         * @param chat_id ID чата
         * @param cancellation Токен отмены
         * @return
         *
         * @exception manapi::exception Default Manapi Exception
         */
        manapi::future<manapi::error::status_or<manapi::json>>  pinned_msg (ssize_t chat_id, manapi::async::cancellation_action cancellation = nullptr);


        /**
         * Закрепляет сообщение в чате.
         *
         * @param chat_id ID чата, где должно быть закреплено сообщение
         * @param cancellation Токен отмены
         * @param message_id ID сообщения, которое нужно закрепить. Соответствует полю Message.body.mid
         * @param notify Если true, участники получат уведомление с системным сообщением о закреплении
         * @return pair обьект, где первое принимает значение true, если запрос был успешным, false в противном случае,
         *  а второе объяснительное сообщение, если результат не был успешным
         *
         * @exception manapi::exception Default Manapi Exception
         */
        manapi::future<manapi::error::status_or<response_status_t>> pin_msg (ssize_t chat_id, std::string message_id, bool notify = true, manapi::async::cancellation_action cancellation = nullptr);

        /**
         * Удаляет закрепленное сообщение в чате.
         *
         * @param chat_id ID чата, из которого нужно удалить закрепленное сообщение
         * @param cancellation Токен отмены
         * @return pair обьект, где первое принимает значение true, если запрос был успешным, false в противном случае,
         *  а второе объяснительное сообщение, если результат не был успешным
         *
         * @exception manapi::exception Default Manapi Exception
         */
        manapi::future<manapi::error::status_or<response_status_t>> unpin_msg (ssize_t chat_id, manapi::async::cancellation_action cancellation = nullptr);

        /**
         * Возвращает информацию о членстве текущего бота в чате.
         *
         * Схема результата
         * @code
         *  {
         *      user_id: integer,
         *      first_name: string,
         *      last_name: string|none,
         *      username: string|null,
         *      is_bot: bool,
         *      last_activity_time: integer,
         *      description: string|null|none,
         *      avatar_url: string|none,
         *      full_avatar_url: string|none,
         *      last_access_time: integer|none,
         *      is_owner: bool|none,
         *      is_admin: bool|none,
         *      join_time: integer|none,
         *      permissions: enum ChatAdminPermission[]
         *  }
         * @endcode
         *
         * enum ChatAdminPermission
         * @code
         *  "read_all_messages" "add_remove_members" "add_admins" "change_chat_info" "pin_message" "write"
         * @endcode
         *
         * Перечень прав пользователя. Возможные значения:
         * - "read_all_messages" — Читать все сообщения.
         * - "add_remove_members" — Добавлять/удалять участников.
         * - "add_admins" — Добавлять администраторов.
         * - "change_chat_info" — Изменять информацию о чате.
         * - "pin_message" — Закреплять сообщения.
         * - "write" — Писать сообщения.
         *
         * @param chat_id ID чата
         * @param cancellation Токен отмены
         * @return
         *
         * @exception manapi::exception Default Manapi Exception
         */
        manapi::future<manapi::error::status_or<manapi::json>>  permissions (ssize_t chat_id, manapi::async::cancellation_action cancellation = nullptr);


        /**
         * Удаляет бота из участников чата.
         *
         * @param chat_id ID чата
         * @param cancellation Токен отмены
         * @return pair обьект, где первое принимает значение true, если запрос был успешным, false в противном случае,
         *  а второе объяснительное сообщение, если результат не был успешным
         *
         * @exception manapi::exception Default Manapi Exception
         */
        manapi::future<manapi::error::status_or<response_status_t>> leave (ssize_t chat_id, manapi::async::cancellation_action cancellation = nullptr);

        /**
         * Возвращает всех администраторов чата.
         * Бот должен быть администратором в запрашиваемом чате.
         *
         * Схема результата
         * @code
         *  {
         *      members: object ChatMember[],
         *      marker: integer|null|none
         *  }
         * @endcode
         *
         * @param chat_id ID чата
         * @param cancellation Токен отмены
         * @return
         *
         * @exception manapi::exception Default Manapi Exception
         */
        manapi::future<manapi::error::status_or<manapi::json>>  admins (ssize_t chat_id, manapi::async::cancellation_action cancellation = nullptr);

        /**
         * Возвращает значение true, если добавлены все администраторы
         *
         * Схема запроса
         * @code
         *  {
         *      admins: ChatAdmin[],
         *      marker: integer|null|none
         *  }
         * @endcode
         *
         * @param chat_id ID чата
         * @param data Тело запроса
         * @param cancellation Токен отмены
         * @return pair обьект, где первое принимает значение true, если запрос был успешным, false в противном случае,
         *  а второе объяснительное сообщение, если результат не был успешным
         *
         * @exception manapi::exception Default Manapi Exception
         */
        manapi::future<manapi::error::status_or<response_status_t>> add_admins (ssize_t chat_id, manapi::json data, manapi::async::cancellation_action cancellation = nullptr);

        /**
         * Отменяет права администратора у пользователя в чате, лишая его административных привилегий
         *
         * @param chat_id ID чата
         * @param user_id Идентификатор пользователя
         * @param cancellation Токен отмены
         * @return pair обьект, где первое принимает значение true, если запрос был успешным, false в противном случае,
         *  а второе объяснительное сообщение, если результат не был успешным
         *
         * @exception manapi::exception Default Manapi Exception
         */
        manapi::future<manapi::error::status_or<response_status_t>> remove_admin (ssize_t chat_id, int64_t user_id, manapi::async::cancellation_action cancellation = nullptr);

        /**
         * Возвращает пользователей, участвующих в чате.
         *
         * Схема запроса
         * @code
         *  {
         *      user_ids: integer[]|null|none,
         *      marker: integer|none,
         *      count: integer(>=1 <=100)|none
         *  }
         * @endcode
         *
         * Схема результата
         * @code
         *  {
         *      members: object ChatMember[],
         *      marker: integer|null|none
         *  }
         * @endcode
         *
         * @param chat_id ID чата
         * @param data Тело запроса
         * @param cancellation Токен отмены
         * @return
         *
         * @exception manapi::exception Default Manapi Exception
         */
        manapi::future<manapi::error::status_or<manapi::json>>  members (ssize_t chat_id, manapi::json data, manapi::async::cancellation_action cancellation = nullptr);


        /**
         * Добавляет участников в чат. Для этого могут потребоваться дополнительные права.
         *
         * Схема запроса
         * @code
         *  {
         *      user_ids: integer[]
         *  }
         * @endcode
         *
         * @param chat_id ID чата
         * @param data Тело запроса
         * @param cancellation Токен отмены
         * @return pair обьект, где первое принимает значение true, если запрос был успешным, false в противном случае,
         *  а второе объяснительное сообщение, если результат не был успешным
         *
         * @exception manapi::exception Default Manapi Exception
         */
        manapi::future<manapi::error::status_or<response_status_t>> add_members (ssize_t chat_id, manapi::json data, manapi::async::cancellation_action cancellation = nullptr);

        /**
         * Удаляет участника из чата. Для этого могут потребоваться дополнительные права.
         *
         * @param chat_id ID чата
         * @param user_id Идентификатор пользователя
         * @param block Если установлено в true, пользователь будет заблокирован в чате. Применяется только для чатов с публичной или приватной ссылкой. Игнорируется в остальных случаях
         * @param cancellation Токен отмены
         * @return pair обьект, где первое принимает значение true, если запрос был успешным, false в противном случае,
         *  а второе объяснительное сообщение, если результат не был успешным
         *
         * @exception manapi::exception Default Manapi Exception
         */
        manapi::future<manapi::error::status_or<response_status_t>> remove_member (ssize_t chat_id, int64_t user_id, bool block = false, manapi::async::cancellation_action cancellation = nullptr);

        /**
         * Если ваш бот получает данные через WebHook, этот метод возвращает список всех подписок.
         *
         * Схема результата
         * @code
         *  {
         *      subscriptions: object Subscription[]
         *  }
         * @endcode
         *
         * @param cancellation Токен отмены
         * @return
         *
         * @exception manapi::exception Default Manapi Exception
         */
        manapi::future<manapi::error::status_or<manapi::json>>  subscriptions (manapi::async::cancellation_action cancellation = nullptr);

        /**
         * Подписывает бота на получение обновлений через WebHook.
         * После вызова этого метода бот будет получать уведомления
         * о новых событиях в чатах на указанный URL.
         * Ваш сервер должен прослушивать один из следующих портов: 80, 8080, 443, 8443, 16384-32383.
         *
         *
         * @param url URL HTTP(S)-эндпойнта вашего бота. Должен начинаться с http(s)://
         * @param update_types Пример: ["message_created", "bot_started"] Список типов обновлений, которые ваш бот хочет получать.
         * @param cancellation Токен отмены
         * @return
         *
         * @exception manapi::exception Default Manapi Exception
         */
        manapi::future<manapi::error::status_or<response_status_t>> subscribe (std::string url, std::vector<std::string> update_types, manapi::async::cancellation_action cancellation = nullptr);

        /**
         * Отписывает бота от получения обновлений через WebHook.
         * После вызова этого метода бот перестает получать уведомления о новых событиях,
         * и доступна доставка уведомлений через API с длительным опросом.
         *
         *
         * @param url URL, который нужно удалить из подписок на WebHook
         * @param cancellation Токен отмены
         * @return
         *
         * @exception manapi::exception Default Manapi Exception
         */
        manapi::future<manapi::error::status_or<response_status_t>> unsubscribe (std::string url, manapi::async::cancellation_action cancellation = nullptr);

        /**
         * Этот метод можно использовать для получения обновлений,
         * если ваш бот не подписан на WebHook.
         * Метод использует долгий опрос (long polling).
         * Каждое обновление имеет свой номер последовательности.
         * Свойство marker в ответе указывает на следующее ожидаемое обновление.
         * Все предыдущие обновления считаются
         * завершенными после прохождения параметра marker.
         * Если параметр marker не передан,
         * бот получит все обновления, произошедшие после последнего подтверждения.
         *
         * Схема запроса
         * @code
         *  {
         *      limit: integer(>=1 <=1000)|none,
         *      timeout: integer(>=0 <=90)|none,
         *      marker: integer|null|none,
         *      types: string[]|null|none
         *  }
         * @endcode
         *
         * Схема результата
         * @code
         *  {
         *      updates: object Update[],
         *      marker: integer|null
         *  }
         * @endcode
         *
         * @param data Тело запроса
         * @param cancellation Токен отмены
         * @return
         *
         * @exception manapi::exception Default Manapi Exception
         */
        manapi::future<manapi::error::status_or<manapi::json>>  recv_updates (manapi::json data, manapi::async::cancellation_action cancellation = nullptr);

        /**
         * Возвращает URL для последующей загрузки файла.
         *
         * @param type Enum: "image" "video" "audio" "file" Тип загружаемого файла
         * @param cancellation Токен отмены
         * @return
         *
         * @exception manapi::exception Default Manapi Exception
         */
        manapi::future<manapi::error::status_or<std::string>> url_to_upload (std::string type, manapi::async::cancellation_action cancellation = nullptr);

        /**
         * Возвращает сообщения в чате: страницу с результатами и маркер,
         * указывающий на следующую страницу.
         * Сообщения возвращаются в обратном порядке,
         * то есть последние сообщения в чате будут
         * первыми в массиве.
         * Поэтому, если вы используете параметры
         * from и to, то to должно быть меньше, чем from.
         *
         * Схема запроса
         * @code
         *  {
         *      chat_id: integer|none,
         *      message_ids: integer[]|none,
         *      from: integer|none,
         *      to: integer|none,
         *      count: integer(>=1 <=100)|none
         *  }
         * @endcode
         *
         * Схема результата
         * @code
         *  {
         *      messages: object Message[]
         *  }
         * @endcode
         *
         * @param data Тело запроса
         * @param cancellation Токен отмены
         * @return
         *
         * @exception manapi::exception Default Manapi Exception
         */
        manapi::future<manapi::error::status_or<manapi::json>>  get_messages (manapi::json data, manapi::async::cancellation_action cancellation = nullptr);

        /**
         * Отправляет сообщение в чат
         *
         * Схема запроса
         * @code
         *  {
         *      text: string(<=4000),
         *      attachments: object AttachmentRequest[]|null,
         *      link: object NewMessageLink|null,
         *      notify: bool|none,
         *      format: enum TextFormat|null
         *  }
         * @endcode
         *
         * Схема результата
         * @code
         *  {
         *      message: object Message
         *  }
         * @endcode
         *
         * enum TextFormat
         * @code
         *  "markdown" "html"
         * @endcode
         *
         * @param user_id Если вы хотите отправить сообщение пользователю, укажите его ID
         * @param chat_id Если сообщение отправляется в чат, укажите его ID
         * @param disable_link_preview Если false, сервер не будет генерировать превью для ссылок в тексте сообщения
         * @param data Тело запроса
         * @param cancellation Токен отмены
         * @return
         *
         * @exception manapi::exception Default Manapi Exception
         */
        manapi::future<manapi::error::status_or<manapi::json>>  send_message (int64_t user_id, int64_t chat_id, manapi::json data, bool disable_link_preview = false, manapi::async::cancellation_action cancellation = nullptr);

        /**
         * Редактирует сообщение в чате.
         * Если поле attachments равно null,
         * вложения текущего сообщения не изменяются.
         * Если в этом поле передан пустой список,
         * все вложения будут удалены.
         *
         * Схема запроса
         * @code
         *  {
         *      text: string(<=4000)|null,
         *      attachements: object AttachmentRequest[]|null,
         *      link: object NewMessageLink|null,
         *      notify: bool|none,
         *      format: enum TextFormat|null
         *  }
         * @endcode
         *
         * enum TextFormat
         * @code
         *  "markdown" "html"
         * @endcode
         *
         * @param message_id ID удаляемого сообщения
         * @param data Тело запроса
         * @param cancellation Токен отмены
         * @return
         *
         * @exception manapi::exception Default Manapi Exception
         */
        manapi::future<manapi::error::status_or<response_status_t>> edit_message (std::string message_id, manapi::json data, manapi::async::cancellation_action cancellation = nullptr);

        /**
         * Удаляет сообщение в диалоге или чате,
         * если бот имеет разрешение на удаление сообщений.
         *
         * @param message_id ID удаляемого сообщения
         * @param cancellation Токен отмены
         * @return
         *
         * @exception manapi::exception Default Manapi Exception
         */
        manapi::future<manapi::error::status_or<response_status_t>> remove_message (std::string message_id, manapi::async::cancellation_action cancellation = nullptr);

        /**
         * Возвращает одно сообщение по его ID.
         * Схема результата
         * @code
         *  {
         *      sender: object User,
         *      recipient: object Recipient,
         *      timestamp: integer,
         *      link: object LinkedMessage|null,
         *      body: object MessageBody,
         *      stat: object MessageStat|null,
         *      url: string|null|none
         *  }
         * @endcode
         *
         * @param message_id ID сообщения (mid), чтобы получить одно сообщение в чате
         * @param cancellation Токен отмены
         * @return
         *
         * @exception manapi::exception Default Manapi Exception
         */
        manapi::future<manapi::error::status_or<manapi::json>>  get_messages (std::string message_id, manapi::async::cancellation_action cancellation = nullptr);

        /**
         * Возвращает подробную информацию о приклеплённом видео.
         * URL-адреса воспроизведения и дополнительные метаданные
         *
         * Схема результата
         * @code
         *  {
         *      token: string,
         *      urls: object VideoUrls|null,
         *      thumbnail: object PhotoAttachmentPayload|null,
         *      width: integer,
         *      height: integer,
         *      duration: integer
         *  }
         * @endcode
         *
         * @param video_token Токен видео-вложения
         * @param cancellation Токен отмены
         * @return
         *
         * @exception manapi::exception Default Manapi Exception
         */
        manapi::future<manapi::error::status_or<manapi::json>>  about_video (std::string video_token, manapi::async::cancellation_action cancellation = nullptr);

        /**
         * Этот метод используется для отправки ответа после того,
         * как пользователь нажал на кнопку.
         * Ответом может быть обновленное сообщение
         * и/или одноразовое уведомление для пользователя.
         *
         * Схема запроса
         * @code
         *  {
         *      message: object NewMessageBody|null,
         *      notification: string|null|none
         *  }
         * @endcode
         *
         * @param callback_id Идентификатор кнопки, по которой пользователь кликнул. Бот получает идентификатор как часть Update с типомmessage_callback.
         * @param data 
         * @param cancellation 
         * @return 
         */
        manapi::future<manapi::error::status_or<maxbot::response_status_t>> handle_callback (std::string callback_id, manapi::json data, manapi::async::cancellation_action cancellation = nullptr);
    private:
        static constexpr char service[] = "\01maxbot";

        static manapi::future<> handle_updates_ (std::shared_ptr<maxbot::data_t> data, manapi::json updates);

        manapi::future<manapi::error::status_or<std::string>> fetch_custom_bot_simple_ (std::string_view url, std::string data, std::string method = {"GET"}, manapi::async::cancellation_action cancellation = nullptr);

        manapi::future<manapi::error::status_or<std::string>> fetch_post_bot_simple_ (std::string_view url, std::string data = {}, manapi::async::cancellation_action cancellation = nullptr);

        manapi::future<manapi::error::status_or<std::string>> fetch_delete_bot_simple_ (std::string_view url, std::string data = {}, manapi::async::cancellation_action cancellation = nullptr);

        manapi::future<manapi::error::status_or<std::string>> fetch_get_bot_simple_ (std::string_view url, std::string data = {}, manapi::async::cancellation_action cancellation = nullptr);

        manapi::future<manapi::error::status_or<std::string>> fetch_patch_bot_simple_ (std::string_view url, std::string data, manapi::async::cancellation_action cancellation = nullptr);

        manapi::future<manapi::error::status_or<std::string>> fetch_put_bot_simple_ (std::string_view url, std::string data, manapi::async::cancellation_action cancellation = nullptr);

        static std::string generate_url_ (const std::shared_ptr<maxbot::data_t> &data, std::string_view path);

        maxbot::response_status_t generate_res_ (manapi::json response);

        std::shared_ptr<data_t> data;
    };

    inline maxbot::maxbot(std::shared_ptr<maxbot::data_t> data) {
        this->data = std::move(data);
    }

    inline maxbot::maxbot() {
        this->data = std::make_shared<maxbot::data_t>(maxbot::data_t{});
    }

    inline maxbot::maxbot(std::string token) {
        this->data = std::make_shared<maxbot::data_t>(maxbot::data_t{});

        this->data->token = std::move(token);
    }

    inline maxbot::~maxbot() = default;

    inline void maxbot::on(std::string action, action_cb_t callback, manapi::async::cancellation_action cancellation) {
        auto stored = std::make_unique<action_cb_t>(std::move(callback));
        auto &handlers = this->data->handlers[action];
        auto key = reinterpret_cast<std::size_t>(stored.get());
        auto it = handlers.insert({key, std::move(stored)});
        assert((it.second && "DUDE? HOW?!"));
    }

    inline void maxbot::token(std::string token) {
        this->data->token = std::move(token);
    }

    inline void maxbot::bind(std::string ip, std::string port) {

    }

    inline manapi::error::status maxbot::bind(std::size_t ms, std::size_t limit) MANAPIHTTP_NOEXCEPT {
        try {
            auto res = manapi::async::current()->timerpool()->append_timer_async(ms,
                [data_ = this->data, ms_ = ms, marker = std::optional<int64_t>{}, limit] (manapi::timer t) mutable
                -> manapi::future<> {
                    try {
                        int timeout = 90;

                        std::string purl = std::format("/updates?timeout={}", timeout);

                        if (marker.has_value())
                            purl.append(std::format("&marker={}", marker.value()));

                        if (limit)
                            purl.append(std::format("&limit={}", limit));

                        purl += '&';

                        auto fetch_res = co_await manapi::net::fetch2::fetch(generate_url_(data_, purl), manapi::json {
                            {"method", "GET"},
                            {"timeout", timeout}
                        });

                        auto fetch = fetch_res.unwrap();

                        if (!fetch.ok()) {
                            manapi_log_trace(manapi::debug::LOG_TRACE_HIGH,
                                "%s:%s failed due to %zu", "maxbot", "connection", fetch.status());
                            t.again(ms_);
                            co_return;
                        }

                        auto remained = (co_await fetch.json()).unwrap();

                        auto const marker_it = remained.as_object().find("marker");
                        if (marker_it != remained.as_object().end()
                            && marker_it->second.is_integer())
                            marker = marker_it->second.as_integer();
                        else
                            marker = {};


                        manapi::async::run(maxbot::handle_updates_(data_, std::move(remained["updates"])));
                    }
                    catch (std::exception const &e) {
                        manapi_log_error("maxbot: long polling failed due to %s. Retrying...", e.what());
                    }
            });

            if (!res)
                return res.err();

            this->data->timer = res.unwrap();
            return error::status_ok();
        }
        catch (std::exception const &e) {
            manapi_log_error("%s due to %s", "maxbot:bind failed", e.what());
            return error::status_internal("maxbot:bind failed");
        }
    }

    inline void maxbot::stop() {
        if (this->data->timer) {
            this->data->timer.stop();
            this->data->timer = nullptr;
        }
    }

    inline manapi::future<manapi::error::status_or<manapi::json>> maxbot::me(manapi::async::cancellation_action cancellation) {
        auto plaintext = co_await fetch_get_bot_simple_("/me", {}, cancellation);
        if (!plaintext)
            co_return plaintext.err();
        co_return manapi::json::parse(plaintext.unwrap());
    }

    inline manapi::future<manapi::error::status_or<manapi::json>> maxbot::me(manapi::json meta, manapi::async::cancellation_action cancellation) {
        auto plaintext = co_await fetch_patch_bot_simple_("/me", meta.dump(), std::move(cancellation));
        if (!plaintext)
            co_return plaintext.err();
        co_return manapi::json::parse(plaintext.unwrap());
    }

    inline manapi::future<manapi::error::status_or<manapi::json>> maxbot::chats(int count, ssize_t marker, manapi::async::cancellation_action cancellation) {
        std::string const url = "/chats";
        /* WHAT THE HELL AAA */
        auto response = co_await fetch_get_bot_simple_(url, (manapi::json{
            {"count", count},
            {"marker", marker}
        }).dump(), std::move(cancellation));
        if (!response)
            co_return response.err();
        co_return manapi::json::parse(response.unwrap());
    }

    inline manapi::future<manapi::error::status_or<manapi::json>> maxbot::
    chat(std::string link, manapi::async::cancellation_action cancellation) {
        std::string const url = std::format("/chats/{}", link);
        MANAPI_MAXBOT_STATUS_WRAP(fetch_get_bot_simple_(url, std::string{}, std::move(cancellation)));
    }

    inline manapi::future<manapi::error::status_or<manapi::json>> maxbot::chat(ssize_t chat_id, manapi::async::cancellation_action cancellation) {
        std::string const url = std::format("/chats/{}", chat_id);
        MANAPI_MAXBOT_STATUS_WRAP(fetch_get_bot_simple_(url, std::string{}, std::move(cancellation)));

    }

    inline manapi::future<manapi::error::status_or<manapi::json>> maxbot::chat(ssize_t chat_id, manapi::json data, manapi::async::cancellation_action cancellation) {
        std::string const url = std::format("/chats/{}", chat_id);
        MANAPI_MAXBOT_STATUS_WRAP(fetch_patch_bot_simple_(url, (data.dump()), std::move(cancellation)));
    }

    inline manapi::future<manapi::error::status_or<maxbot::response_status_t>> maxbot::remove_chat(ssize_t chat_id, manapi::async::cancellation_action cancellation) {
        std::string const url = std::format("/chats/{}", chat_id);
        MANAPI_MAXBOT_STATUS_WRAP_RES(fetch_delete_bot_simple_(url, std::string{}, std::move(cancellation)));
    }

    inline manapi::future<manapi::error::status_or<maxbot::response_status_t>> maxbot::status_chat(ssize_t chat_id, std::string action, manapi::async::cancellation_action cancellation) {
        std::string const url = std::format("/chats/{}/actions", chat_id);
        MANAPI_MAXBOT_STATUS_WRAP_RES(fetch_post_bot_simple_(url, manapi::json{{"action", std::move(action)}}.dump(), std::move(cancellation)));

    }

    inline manapi::future<manapi::error::status_or<manapi::json>>  maxbot::pinned_msg(ssize_t chat_id, manapi::async::cancellation_action cancellation) {
        std::string const url = std::format("/chats/{}", chat_id);
        MANAPI_MAXBOT_STATUS_WRAP(fetch_get_bot_simple_(url, std::string{}, std::move(cancellation)));
    }

    inline manapi::future<manapi::error::status_or<maxbot::response_status_t>> maxbot::pin_msg(ssize_t chat_id, std::string message_id, bool notify, manapi::async::cancellation_action cancellation) {
        std::string const url = std::format("/chats/{}/pin", chat_id);
        MANAPI_MAXBOT_STATUS_WRAP_RES(fetch_put_bot_simple_(url, manapi::json{
                {"message_id", std::move(message_id)},
                {"notify", notify}
            }.dump(), std::move(cancellation)));
    }

    inline manapi::future<manapi::error::status_or<maxbot::response_status_t>> maxbot::unpin_msg(ssize_t chat_id, manapi::async::cancellation_action cancellation) {
        std::string const url = std::format("/chats/{}/pin", chat_id);
        MANAPI_MAXBOT_STATUS_WRAP_RES(fetch_delete_bot_simple_(url, std::string{}, std::move(cancellation)));
    }

    inline manapi::future<manapi::error::status_or<manapi::json>>  maxbot::permissions(ssize_t chat_id, manapi::async::cancellation_action cancellation) {
        std::string const url = std::format("/chats/{}/members/me", chat_id);
        MANAPI_MAXBOT_STATUS_WRAP( fetch_get_bot_simple_(url, std::string{}, std::move(cancellation)));
    }

    inline manapi::future<manapi::error::status_or<maxbot::response_status_t>> maxbot::leave(ssize_t chat_id, manapi::async::cancellation_action cancellation) {
        std::string const url = std::format("/chats/{}/members/me", chat_id);
        MANAPI_MAXBOT_STATUS_WRAP_RES(fetch_delete_bot_simple_(url, std::string{}, std::move(cancellation)));
    }

    inline manapi::future<manapi::error::status_or<manapi::json>>  maxbot::admins(ssize_t chat_id, manapi::async::cancellation_action cancellation) {
        std::string const url = std::format("/chats/{}/members/admins", chat_id);
        MANAPI_MAXBOT_STATUS_WRAP(fetch_get_bot_simple_(url, std::string{}, std::move(cancellation)));
    }

    inline manapi::future<manapi::error::status_or<maxbot::response_status_t>> maxbot::add_admins(ssize_t chat_id, manapi::json data, manapi::async::cancellation_action cancellation) {
        std::string const url = std::format("/chats/{}/members/admins", chat_id);
        MANAPI_MAXBOT_STATUS_WRAP_RES(fetch_post_bot_simple_(url, data.dump(), std::move(cancellation)));
    }

    inline manapi::future<manapi::error::status_or<maxbot::response_status_t>> maxbot::remove_admin(ssize_t chat_id, int64_t user_id, manapi::async::cancellation_action cancellation) {
        std::string const url = std::format("/chats/{}/members/admins/{}", chat_id, user_id);
        MANAPI_MAXBOT_STATUS_WRAP_RES(fetch_delete_bot_simple_(url, std::string{}, std::move(cancellation)));
    }

    inline manapi::future<manapi::error::status_or<manapi::json>>  maxbot::members(ssize_t chat_id, manapi::json data, manapi::async::cancellation_action cancellation) {
        std::string const url = std::format("/chats/{}/members", chat_id);
        MANAPI_MAXBOT_STATUS_WRAP(fetch_get_bot_simple_(url, data.dump(), std::move(cancellation)));
    }

    inline manapi::future<manapi::error::status_or<maxbot::response_status_t>> maxbot::add_members(ssize_t chat_id, manapi::json data, manapi::async::cancellation_action cancellation) {
        std::string const url = std::format("/chats/{}/members", chat_id);
        MANAPI_MAXBOT_STATUS_WRAP_RES(fetch_post_bot_simple_(url, data.dump(), std::move(cancellation)));
    }

    inline manapi::future<manapi::error::status_or<maxbot::response_status_t>> maxbot::remove_member(ssize_t chat_id, int64_t user_id, bool block, manapi::async::cancellation_action cancellation) {
        std::string const url = std::format("/chats/{}/members", chat_id);
        MANAPI_MAXBOT_STATUS_WRAP_RES(fetch_delete_bot_simple_(url, (manapi::json{
                {"user_id", user_id},
                {"block", block}
            }).dump(), std::move(cancellation)));
    }

    inline manapi::future<manapi::error::status_or<manapi::json>>  maxbot::subscriptions(manapi::async::cancellation_action cancellation) {
        std::string const url = "/subscriptions";
        MANAPI_MAXBOT_STATUS_WRAP( fetch_get_bot_simple_(url, std::string{}, std::move(cancellation)));
    }

    inline manapi::future<manapi::error::status_or<maxbot::response_status_t>> maxbot::subscribe(std::string url, std::vector<std::string> update_types, manapi::async::cancellation_action cancellation) {
        std::string const purl = "/subscriptions";

        manapi::json update_types_json = manapi::json::array();
        for (auto &c : update_types)
            update_types_json.push_back(std::move(c));

        MANAPI_MAXBOT_STATUS_WRAP_RES(fetch_post_bot_simple_(purl, manapi::json({
                {"url", std::move(url)},
                {"update_types", std::move(update_types_json)}
            }).dump(), std::move(cancellation)));
    }

    inline manapi::future<manapi::error::status_or<maxbot::response_status_t>> maxbot::unsubscribe(std::string url, manapi::async::cancellation_action cancellation) {
        std::string const purl = "/subscriptions";
        MANAPI_MAXBOT_STATUS_WRAP_RES(fetch_delete_bot_simple_(purl, manapi::json ({{"url", std::move(url)}}).dump(), std::move(cancellation)));
    }

    inline manapi::future<manapi::error::status_or<manapi::json>>  maxbot::recv_updates(manapi::json data, manapi::async::cancellation_action cancellation) {
        std::string const purl = "/updates";
        MANAPI_MAXBOT_STATUS_WRAP(fetch_get_bot_simple_(purl, data.dump(), std::move(cancellation)));
    }

    inline manapi::future<manapi::error::status_or<std::string>> maxbot::url_to_upload(std::string type, manapi::async::cancellation_action cancellation) {
        std::string const purl = "/uploads";
        auto response = co_await fetch_post_bot_simple_(purl, manapi::json({{"type", std::move(type)}}).dump(), std::move(cancellation));
        if (!response) { co_return response.err(); }
        auto data = manapi::json::parse(response.unwrap());
        if (!data) co_return data.err();
        auto obj = data.unwrap();
        co_return obj["url"].as_string();
    }

    inline manapi::future<manapi::error::status_or<manapi::json>>  maxbot::get_messages(manapi::json data, manapi::async::cancellation_action cancellation) {
        std::string purl = "/messages?";

        {
            auto &obj = data.as_object();
            auto it = obj.find("count");
            if (it != obj.end())
                purl.append(std::format("count={}&", it->second.as_integer_cast()));
            it = obj.find("from");
            if (it != obj.end())
                purl.append(std::format("from={}&", it->second.as_integer_cast()));
            it = obj.find("to");
            if (it != obj.end())
                purl.append(std::format("to={}&", it->second.as_integer_cast()));
            it = obj.find("chat_id");
            if (it != obj.end())
                purl.append(std::format("chat_id={}&", it->second.as_integer_cast()));
            it = obj.find("message_ids");
            if (it != obj.end()) {
                purl.append("message_ids=");
                auto hit = it->second.as_array().begin();
                goto skip;
                for (; hit != it->second.as_array().end(); ++hit) {
                    purl.append(",");
                    skip:
                    purl.append(hit->as_string());
                }
                purl.append("&");
            }
        }

        MANAPI_MAXBOT_STATUS_WRAP(fetch_get_bot_simple_(purl, {}, std::move(cancellation)));
    }

    inline manapi::future<manapi::error::status_or<manapi::json>>  maxbot::send_message(int64_t user_id, int64_t chat_id, manapi::json data, bool disable_link_preview, manapi::async::cancellation_action cancellation) {
        std::string const purl = std::format("/messages?user_id={}&chat_id={}&disable_link_preview={}&", user_id, chat_id, disable_link_preview);
        MANAPI_MAXBOT_STATUS_WRAP(fetch_post_bot_simple_(purl, data.dump(), std::move(cancellation)));
    }

    inline manapi::future<manapi::error::status_or<maxbot::response_status_t>> maxbot::edit_message(std::string message_id, manapi::json data, manapi::async::cancellation_action cancellation) {
        std::string const purl = std::format("/messages?message_id={}&", message_id);
        MANAPI_MAXBOT_STATUS_WRAP_RES(fetch_put_bot_simple_(purl, data.dump(), std::move(cancellation)));
    }

    inline manapi::future<manapi::error::status_or<maxbot::response_status_t>> maxbot::remove_message(std::string message_id, manapi::async::cancellation_action cancellation) {
        std::string const purl = std::format("/messages?message_id={}&", message_id);
        MANAPI_MAXBOT_STATUS_WRAP_RES(fetch_delete_bot_simple_(purl, std::string{}, std::move(cancellation)));
    }

    inline manapi::future<manapi::error::status_or<manapi::json>>  maxbot::get_messages(std::string message_id, manapi::async::cancellation_action cancellation) {
        std::string const purl = std::format("/messages/{}", message_id);
        MANAPI_MAXBOT_STATUS_WRAP(fetch_get_bot_simple_(purl, std::string{}, std::move(cancellation)));
    }

    inline manapi::future<manapi::error::status_or<manapi::json>>  maxbot::about_video(std::string video_token, manapi::async::cancellation_action cancellation) {
        std::string const purl = std::format("/videos", video_token);
        MANAPI_MAXBOT_STATUS_WRAP(fetch_get_bot_simple_(purl, std::string{}, std::move(cancellation)));

    }

    inline manapi::future<manapi::error::status_or<maxbot::response_status_t>> maxbot::handle_callback(std::string callback_id, manapi::json data, manapi::async::cancellation_action cancellation) {
        std::string const purl = std::format("/answers?callback_id={}&", callback_id);
        MANAPI_MAXBOT_STATUS_WRAP_RES(fetch_post_bot_simple_(purl, data.dump(), std::move(cancellation)));
    }

    inline manapi::future<> maxbot::handle_updates_(std::shared_ptr<maxbot::data_t> data, manapi::json updates) {
        for (auto &update : updates.each()) {
            std::string const &update_type = update["update_type"].as_string();
            auto const it = data->handlers.find(update_type);

            if (it == data->handlers.end())
                continue;

            auto mbot = maxbot(data);
            for (auto handler = it->second.begin(); handler != it->second.end(); ++handler) {
                try {
                    if(co_await handler->second->operator()(mbot, update))
                        break;
                }
                catch (std::exception const &e) {
                    manapi_log_error("%s due to %s", "unexpected error in the user handler callback", e.what());
                }
            }
        }
    }

    inline manapi::future<manapi::error::status_or<std::string>> maxbot::fetch_custom_bot_simple_(std::string_view url, std::string data, std::string method, manapi::async::cancellation_action cancellation) {
        std::optional<std::string> data_opt;
        if (!data.empty())
            data_opt = std::move(data);
        auto fetch_res = co_await manapi::net::fetch2::fetch(manapi::maxbot::generate_url_(this->data, url), {
                    {"method", std::move(method)}
                }, std::move(data_opt), std::move(cancellation));
        if (!fetch_res)
            co_return fetch_res.err();
        auto fetch = fetch_res.unwrap();
        if (!fetch.ok()) {
            std::string text;
            auto text_res = co_await fetch.text();
            manapi_log_trace(manapi::debug::LOG_TRACE_HIGH, "%s: %zu, %s", "maxbot service returned an invalid status code", fetch.status(), "let's grab a text response");
            if (text_res)
                text = text_res.unwrap();
            manapi_log_error(manapi::debug::LOG_TRACE_HIGH, "%s: %zu, %.*s", "maxbot service returned an invalid status code", fetch.status(), text.size(), text.data());
            co_return error::status_internal("maxbot service returned an invalid status code");
        }
        co_return co_await fetch.text();
    }

    inline manapi::future<manapi::error::status_or<std::string>> maxbot::fetch_post_bot_simple_(std::string_view url, std::string data, manapi::async::cancellation_action cancellation) {
        co_return co_await fetch_custom_bot_simple_(url, std::move(data), "POST", std::move(cancellation));
    }

    inline manapi::future<manapi::error::status_or<std::string>> maxbot::fetch_delete_bot_simple_(std::string_view url, std::string data, manapi::async::cancellation_action cancellation) {
        co_return co_await fetch_custom_bot_simple_(url, std::move(data), "DELETE", std::move(cancellation));
    }

    inline manapi::future<manapi::error::status_or<std::string>> maxbot::fetch_get_bot_simple_(std::string_view url, std::string data, manapi::async::cancellation_action cancellation) {
        co_return co_await fetch_custom_bot_simple_(url, std::move(data), "GET", std::move(cancellation));
    }

    inline manapi::future<manapi::error::status_or<std::string>> maxbot::fetch_patch_bot_simple_(std::string_view url, std::string data, manapi::async::cancellation_action cancellation) {
        co_return co_await fetch_custom_bot_simple_(url, std::move(data), "PATCH", std::move(cancellation));
    }

    inline manapi::future<manapi::error::status_or<std::string>> maxbot::fetch_put_bot_simple_(std::string_view url, std::string data, manapi::async::cancellation_action cancellation) {
        co_return co_await fetch_custom_bot_simple_(url, std::move(data), "PUT", std::move(cancellation));
    }

    inline std::string maxbot::generate_url_(const std::shared_ptr<maxbot::data_t> &data, std::string_view path) {
        if (!path.empty() && (path.back() == '&'||path.back()=='?'))
            return std::format("https://botapi.max.ru{}access_token={}", path, data->token);

        return std::format("https://botapi.max.ru{}?access_token={}", path, data->token);
    }

    inline maxbot::response_status_t maxbot::generate_res_(manapi::json response) {
        std::pair<bool, std::string> res{};
        res.first = response["success"].as_bool_cast();
        auto &msg = response["message"];
        if (res.first && msg.is_string()) {
            res.second = std::move(msg.as_string());
        }
        return std::move(res);
    }
}
