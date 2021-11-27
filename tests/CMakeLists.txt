cmake_minimum_required(VERSION 3.0.0)

set(PROJECT tests)
set(TESTED_PROJECT tested_prj)
set(Sources
    kernel_tests.cpp
)

add_executable(${PROJECT} ${Sources})
target_link_libraries(${PROJECT} PUBLIC
    gtest
    gtest_main
    ${TESTED_PROJECT}
)

add_test(
    NAME ${PROJECT}
    COMMAND ${PROJECT}
)