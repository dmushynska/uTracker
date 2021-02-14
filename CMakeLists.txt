cmake_minimum_required(VERSION 3.17)

project(utracker VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "/usr/local/Cellar/qt/5.15.1/")

add_subdirectory(client)
add_subdirectory(server)
