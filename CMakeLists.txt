cmake_minimum_required(VERSION 3.13.0)

include(FetchContent)
include(ExternalProject)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything -Ofast")

project(electribe-song-mode)

# Prepare dependenies

ExternalProject_Add(
    fltk
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/fltk
    GIT_REPOSITORY https://github.com/fltk/fltk.git
    GIT_TAG 43b511b784e4350562d0639dfd7a078d761ec54d
    CONFIGURE_COMMAND ""
    BUILD_COMMAND "make"
    BUILD_IN_SOURCE 1
    INSTALL_COMMAND ""
)
set(fltk_INCLUDE_DIRS ${CMAKE_CURRENT_BINARY_DIR}/fltk/src/fltk)

# Compiler flags
execute_process(
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/fltk/src/fltk/fltk-config --cxxflags
    OUTPUT_VARIABLE fltk_COMPILER_FLAGS
)
# TODO: Add compiler flags

# Linker flags
execute_process(
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/fltk/src/fltk/fltk-config --ldflags
    OUTPUT_VARIABLE fltk_LINK_LIBS
)
# TODO: --ldstaticflags

ExternalProject_Add(
    rtmidi
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/rtmidi
    GIT_REPOSITORY https://github.com/thestk/rtmidi.git
    GIT_TAG 2.1.1
    CONFIGURE_COMMAND "./autogen.sh"
    BUILD_COMMAND "make"
    BUILD_IN_SOURCE 1
    INSTALL_COMMAND ""
)
set(rtmidi_INCLUDE_DIRS ${CMAKE_CURRENT_BINARY_DIR}/rtmidi/src/rtmidi)
link_directories(${CMAKE_CURRENT_BINARY_DIR}/rtmidi/src/rtmidi)
execute_process(
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/rtmidi/src/rtmidi/rtmidi-config --libs
    OUTPUT_VARIABLE rtmidi_LINK_LIBS
)

ExternalProject_Add(
    rapidjson
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/rapidjson
    GIT_REPOSITORY https://github.com/Tencent/rapidjson.git
    GIT_TAG v1.1.0
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    BUILD_IN_SOURCE 1
    INSTALL_COMMAND ""
)
set(rapidjson_INCLUDE_DIRS ${CMAKE_CURRENT_BINARY_DIR}/rapidjson/src/rapidjson/include)

# Prepare executable

include_directories(${fltk_INCLUDE_DIRS})
include_directories(${rtmidi_INCLUDE_DIRS})
include_directories(${rapidjson_INCLUDE_DIRS})
include_directories(./include)

file(GLOB SOURCES "src/*.cpp")
add_executable(electribe-song-mode electribe-song-mode.cpp ${SOURCES})

add_dependencies(electribe-song-mode rtmidi)
add_dependencies(electribe-song-mode fltk)

target_link_libraries(electribe-song-mode ${rtmidi_LINK_LIBS} ${fltk_LINK_LIBS})
install(TARGETS electribe-song-mode DESTINATION bin)
