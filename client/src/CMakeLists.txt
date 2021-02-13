cmake_minimum_required(VERSION 3.17.3)

set(CMAKE_CXX_STANDARD 20)
set(NAME client_src)
set(OPENSSL_ROOT_DIR /usr/local/opt/openssl)

find_package(Qt5 COMPONENTS Core Widgets Network Sql REQUIRED)
find_package(OpenSSL REQUIRED)

add_compile_options(
    -std=c++17
    -Wall
    -Wextra
    -Werror
    -Wpedantic
)

file(GLOB SRC *.cpp)
file(GLOB HDR *.h)

add_library(${NAME} ${SRC} ${HDR})

target_link_libraries(
        ${NAME}
        Qt5::Core
        Qt5::Widgets
        Qt5::Network
        Qt5::Sql
	    OpenSSL::SSL
)