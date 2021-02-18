cmake_minimum_required(VERSION 3.17.3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(NAME client)
set(SOURCE_EXE main.cpp)

add_compile_options(
    -std=c++17
#    -Wall
#    -Wextra
#    -Werror
#    -Wpedantic
)

find_package(Qt5 COMPONENTS Core Widgets Network Sql Gui Quick NetworkAuth REQUIRED)
find_package(Qt5 COMPONENTS Core Quick QuickControls2 REQUIRED)
#target_link_libraries(${NAME} PRIVATE Qt5::Core Qt5::Quick Qt5::QuickControls2)

#find_package(Qt5 COMPONENTS Core Gui Quick NetworkAuth LinguistTools REQUIRED)

include_directories(src)

add_subdirectory(src)

#add_definitions("-DQPM_INIT\\(E\\)=E.addImportPath\\(QStringLiteral\\(\\\"qrc:/\\\"\\)\\)\\;")
include(src/material/vendor.cmake)

add_executable(${NAME} main.cpp ${VENDOR_SOURCES} src/qml.qrc )

target_compile_definitions(${NAME}
PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(
    ${NAME}
    Qt5::Core
    Qt5::Widgets
    Qt5::Network
    Qt5::Sql
    Qt5::Widgets
    Qt5::Gui
    Qt5::Quick
    Qt5::QuickControls2
    client_src
)
