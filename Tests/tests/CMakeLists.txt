cmake_minimum_required(VERSION 3.0.0)

set(PROJECT tests)
set(TESTED_PROJECT prj)
set(SRC
    kernel_tests.cpp
    client_usb_tests.cpp
)

add_executable(${PROJECT} ${SRC})
target_link_libraries(${PROJECT} PUBLIC
    gtest
    gtest_main
    ${TESTED_PROJECT}
)

add_test(
    NAME ${PROJECT}
    COMMAND ${PROJECT}
)