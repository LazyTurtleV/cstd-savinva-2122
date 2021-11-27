cmake_minimum_required(VERSION 3.0.0)

set(PROJECT tic-tac-toe-game)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)

set(Sources
    main.c
    kernel.c
)
    
set(Headers
    headers/kernel.h
)
    
project(${PROJECT} C CXX)
add_executable(${PROJECT} ${Sources})
    
##################################################
#                   Testing
##################################################
set(TESTED_PROJECT tested_prj)

#instance of project for tests
add_library(${TESTED_PROJECT} STATIC ${Sources} ${Headers})

enable_testing()

add_subdirectory(googletest)
add_subdirectory(tests)
