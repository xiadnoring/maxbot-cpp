cmake_minimum_required(VERSION 3.10)
project(maxbot)

set(CMAKE_CXX_STANDARD 23)

find_package(manapihttp)

add_executable(${PROJECT_NAME}
        src/main.cpp
        include/MaxBot.hpp
)

target_include_directories  (${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} manapihttp::manapihttp)