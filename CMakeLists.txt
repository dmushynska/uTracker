cmake_minimum_required(VERSION 3.17)

project(utracker VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(client_1)
add_subdirectory(server)

#set_target_properties(utracker PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../)

