cmake_minimum_required(VERSION 3.17.3)

set(CMAKE_CXX_STANDARD 17)
set(NAME client_src)
set(OPENSSL_ROOT_DIR /usr/local/opt/openssl)

find_package(Qt5 COMPONENTS Core Widgets Network Sql Gui Quick NetworkAuth REQUIRED)
find_package(OpenSSL REQUIRED)

add_compile_options(
    -std=c++17
#    -Wall
#    -Wextra
#    -Werror
#    -Wpedantic
)

file(GLOB SRC *.cpp model/*.cpp Components/src/*.cpp)
file(GLOB HDR *.h model/*.h Components/src/*.h)

add_definitions("-DQPM_INIT\\(E\\)=E.addImportPath\\(QStringLiteral\\(\\\"qrc:/\\\"\\)\\)\\;")

#include(material/vendor.cmake)

add_library(${NAME} ${SRC} ${HDR})

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
	    OpenSSL::SSL
)

#target_compile_definitions(utracker
#		PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)