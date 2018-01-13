cmake_minimum_required(VERSION 3.0)
project(TsukiBot-Tests)

set(TSUKIBOT_VERSION_MAJOR 3)
set(TSUKIBOT_VERSION_MINOR 14)

set(CMAKE_CXX_EXTENSIONS 14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

include_directories("${PROJECT_SOURCE_DIR}/TsukiBot/include")
include_directories("${PROJECT_SOURCE_DIR}/TryxPS/include")

set(HEADERS "../TsukiBot/include/constants.hpp"
            "../TsukiBot/include/ircconnector.hpp"
            "../TsukiBot/include/ircmessage.hpp"
            "../TsukiBot/include/TsukiIRC.hpp")

set(SOURCES "../TsukiBot/src/constants.cpp"
            "../TsukiBot/src/ircconnector.cpp"
            "../TsukiBot/src/ircmessage.cpp"
            "../TsukiBot/src/TsukiIRC.cpp")

set(MSG_TEST "msg-test.cpp")
add_executable(msg-test "msg-test.cpp" ${MSG_TEST} ${HEADERS} ${SOURCES})

