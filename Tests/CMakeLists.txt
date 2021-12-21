cmake_minimum_required(VERSION 3.0.0)

set(PRJ TEST_SRC)
set(TESTED_PRJ prj)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_C_COMPILER gcc)

project(${PRJ})

file(GLOB SRC 
    ../ServerSide/src/*.cpp
)

file(GLOB HDR 
    ../ServerSide/headers/*.h
)

#instance of project for tests
add_library(${TESTED_PRJ} STATIC ${SRC} ${HDR})

enable_testing()

add_subdirectory(googletest)
add_subdirectory(tests)