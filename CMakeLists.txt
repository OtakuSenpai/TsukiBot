cmake_minimum_required (VERSION 3.0)

project (TsukiBot)

set(TsukiBot_VERSION_MAJOR 0.3)
set(TsukiBot_VERSION_MINOR 14)

set(CMAKE_CXX_EXTENSIONS 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -O2")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins)
include_directories("${PROJECT_SOURCE_DIR}/TsukiBot/include")
include_directories("${PROJECT_SOURCE_DIR}/TryxPS/include")
set(HEADERS "TsukiBot/include/constants.hpp"
            "TsukiBot/include/ircconnector.hpp"
            "TsukiBot/include/ircmessage.hpp"
            "TsukiBot/include/TsukiIRC.hpp")

set(SOURCES "TsukiBot/src/constants.cpp"
            "TsukiBot/src/ircconnector.cpp"
            "TsukiBot/src/ircmessage.cpp"
            "TsukiBot/src/TsukiIRC.cpp")

set(MOOPLG "plugins-src/MooPlugin/mooplg.hpp"
           "plugins-src/MooPlugin/mooplg.cpp")
set(PINGPLG "plugins-src/PingPlugin/pingplg.hpp"
           "plugins-src/PingPlugin/pingplg.cpp")

set (TryxPS_DIR "${CMAKE_SOURCE_DIR}/TryxPS/cmake")
find_package(TryxPS REQUIRED)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/TryxPS/cmake")

find_file(SDL2_INCLUDE_DIR NAME SDL.h HINTS SDL2)
find_library(SDL2_LIBRARY NAME SDL2 HINTS SDL2)
find_file(SDL2NET_INCLUDE_DIR NAME SDL_net.h HINTS SDL2_net)
find_library(SDL2NET_LIBRARY NAME SDL2_net HINTS SDL2_net)

add_library(mooplg SHARED ${MOOPLG})
add_library(pingplg SHARED ${PINGPLG})

add_executable(tsukibot "main.cpp" ${SOURCES} ${HEADERS})
target_link_libraries(tsukibot ${SDL2_LIBRARY} ${SDL2NET_LIBRARY} TryxPS::tryxps ${CMAKE_DL_LIBS})
