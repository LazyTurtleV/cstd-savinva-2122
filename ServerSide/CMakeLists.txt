cmake_minimum_required(VERSION 2.8)
set(PROJECT_NAME tic-tac-toe-game)

set(CMAKE_ARDUINO_PATH arduino-cmake)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_ARDUINO_PATH}/cmake/ArduinoToolchain.cmake) # Arduino Toolchain
set(CMAKE_EXTERNAL_LIBS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/libraries) # arduino external libs
set(SOURCE_DIRECTORIES src)
set(BOARD_NAME uno)

set (CMAKE_CXX_STANDARD 11)
project(${PROJECT_NAME} C CXX)

#link_libraries(${ARDUINO_SDK}/libraries)

# Link external libs directories (as Arduino-IDE uses it)
link_directories(${CMAKE_EXTERNAL_LIBS_PATH})

# set source files

file (GLOB Sources 
    ${SOURCE_DIRECTORIES}/*.cpp
    ${SOURCE_DIRECTORIES}/*.c
)

set(${PROJECT_NAME}_BOARD ${BOARD_NAME})
set(${PROJECT_NAME}_SRCS ${Sources})
set(${PROJECT_NAME}_PORT /dev/ttyUSB0)

# Command to generate code arduino firmware (.hex file)
generate_arduino_firmware(${PROJECT_NAME})