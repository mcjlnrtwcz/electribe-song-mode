cmake_minimum_required(VERSION 3.7.2)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything -Ofast")

project(patternSelect)

set(PROJECT_LINK_LIBS librtmidi.a)
link_directories(/Users/mcjlnrtwcz/Projects/PatternSelect/Libs/rtmidi-2.1.1/.libs)
include_directories(/Users/mcjlnrtwcz/Projects/PatternSelect/Libs/rtmidi-2.1.1)

include_directories(/Users/mcjlnrtwcz/Projects/PatternSelect/Libs/rapidjson/include)

include_directories(/Users/mcjlnrtwcz/Projects/PatternSelect/Libs/fltk-1.3.4-1/)
# http://www.fltk.org/doc-1.3/basics.html#basics_standard_compiler
# http://stackoverflow.com/questions/11783932/how-to-add-linker-or-compile-flag-in-cmake-file#11797272
#./fltk-config --cxxflags
set(FLTK_FLAGS "-D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_THREAD_SAFE -D_REENTRANT")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLTK_FLAGS}")
#./fltk-config --ldstaticflags
set(FLTK_LINK_FLAGS "/Users/mcjlnrtwcz/Projects/PatternSelect/Libs/fltk-1.3.4-1/build/lib/libfltk.a -lpthread -framework Cocoa")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${FLTK_LINK_FLAGS}")

include_directories(./include)
file(GLOB SOURCES "src/*.cpp")

add_executable(PatSelleck PatSelleck.cpp ${SOURCES})
target_link_libraries(PatSelleck ${PROJECT_LINK_LIBS})

install(TARGETS PatSelleck DESTINATION bin)
