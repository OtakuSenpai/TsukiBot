cmake_minimum_required (VERSION 3.0)

project (TsukiBot)

set(TsukiBot_VERSION_MAJOR 0.00.1)
set(TsukiBot_VERSION_MINOR 13)

set(CMAKE_CXX_EXTENSIONS 14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/TryxPS/include")
set(HEADERS "include/constants.hpp"
            "include/ircconnector.hpp"
            "include/ircmessage.hpp"
            "include/TsukiIRC.hpp")

set(SOURCES "src/constants.cpp"
            "src/ircconnector.cpp"
            "src/ircmessage.cpp"
            "src/TsukiIRC.cpp")

set (TryxPS_DIR "${CMAKE_SOURCE_DIR}/TryxPS/cmake")
find_package(TryxPS REQUIRED)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/TryxPS/cmake")

find_file(SDL2_INCLUDE_DIR NAME SDL.h HINTS SDL2)
find_library(SDL2_LIBRARY NAME SDL2 HINTS SDL2)
find_file(SDL2NET_INCLUDE_DIR NAME SDL_net.h HINTS SDL2_net)
find_library(SDL2NET_LIBRARY NAME SDL2_net HINTS SDL2_net)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -O2")

add_executable(Nyu "main.cpp" ${SOURCES} ${HEADERS})
target_link_libraries(Nyu ${SDL2_LIBRARY} ${SDL2NET_LIBRARY} TryxPS::tryxps ${CMAKE_DL_LIBS})
