cmake_minimum_required (VERSION 3.0)

project (TsukiBot)

set(TsukiBot_VERSION_MAJOR 0.3)
set(TsukiBot_VERSION_MINOR 17)

set(CMAKE_CXX_EXTENSIONS 14)

if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 6.3)
        message(FATAL_ERROR "g++ version must be at least 6.3!")
  endif()
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -O2")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins)
include_directories("${PROJECT_SOURCE_DIR}/TsukiBot/include")
include_directories("${PROJECT_SOURCE_DIR}/TryxPS/include")
include_directories("${PROJECT_SOURCE_DIR}/plugins-src/")
set(HEADERS "TsukiBot/include/constants.hpp"
            "TsukiBot/include/ircconnector.hpp"
            "TsukiBot/include/ircmessage.hpp"
             "TsukiBot/include/irchelpers.hpp"
            "TsukiBot/include/TsukiIRC.hpp")

set(SOURCES "TsukiBot/src/constants.cpp"
            "TsukiBot/src/ircconnector.cpp"
            "TsukiBot/src/ircmessage.cpp"
            "TsukiBot/src/irchelpers.cpp"
            "TsukiBot/src/TsukiIRC.cpp")

set(BASEPLUGIN "plugins-src/BasePlugin.hpp"
               "plugins-src/BasePlugin.cpp")

set(BASICPLG "plugins-src/BasicPlg/BasicPlg.hpp"
             "plugins-src/BasicPlg/BasicPlg.cpp")

set (TryxPS_DIR "${CMAKE_SOURCE_DIR}/TryxPS/cmake")
find_package(TryxPS REQUIRED)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/TryxPS/cmake")

add_library(basicplg SHARED ${BASICPLG} ${BASEPLUGIN})

find_file(SDL2_INCLUDE_DIR NAME SDL.h HINTS SDL2)
find_library(SDL2_LIBRARY NAME SDL2 HINTS SDL2)
find_file(SDL2NET_INCLUDE_DIR NAME SDL_net.h HINTS SDL2_net)
find_library(SDL2NET_LIBRARY NAME SDL2_net HINTS SDL2_net)

add_executable(tsukibot "main.cpp" ${SOURCES} ${HEADERS})
target_link_libraries(tsukibot ${SDL2_LIBRARY} ${SDL2NET_LIBRARY} TryxPS::tryxps ${CMAKE_DL_LIBS})
