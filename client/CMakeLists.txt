cmake_minimum_required(VERSION 3.17.3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(NAME client)
set(SOURCE_EXE main.cpp)

add_compile_options(
    -std=c++17
    -Wall
    -Wextra
    -Werror
    -Wpedantic
)

find_package(Qt5 COMPONENTS Core Widgets Network Sql REQUIRED)

include_directories(./src)

add_subdirectory(src)

add_executable(${NAME} main.cpp)

target_link_libraries(
    ${NAME}
    Qt5::Core
    Qt5::Widgets
    Qt5::Network
    Qt5::Sql
    client_src
)
