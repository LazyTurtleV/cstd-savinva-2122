cmake_minimum_required(VERSION 3.0.0)

set(PRJ tic-tac-toe-game)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_ASM_COMPILER avr-gcc)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)

#################################################
#               MCU PROPERTIES
#################################################

set(MCU atmega328p)
set(BAUD 9600)
set(PROG_TYPE arduino)
set(PORT /dev/ttyUSB0)

#################################################
#             BUILD & DEPLOYMENT
#################################################

set(SRC
    src/kernel.c
    src/main.c
)
set(HDR
    headers/kernel.h
)
    
project(${PRJ})

##################################################
#                     Tests
##################################################
set(TESTED_PROJECT tested_prj)

#instance of project for tests
add_library(${TESTED_PROJECT} STATIC ${SRC} ${HDR})

enable_testing()

add_subdirectory(googletest)
add_subdirectory(tests)

##################################################
#                   Firmware
##################################################


add_definitions(-DBAUD=${BAUD})
set(CMAKE_EXE_LINKER_FLAGS -mmcu=${MCU})


add_compile_options(
    -mmcu=${MCU}
    -Os
)

add_executable(${PRJ} ${SRC})

set_target_properties(${PRJ} PROPERTIES OUTPUT_NAME ${PRJ}.elf)

add_custom_target(strip ALL avr-strip ${PRJ}.elf DEPENDS ${PRJ})
add_custom_target(hex ALL avr-objcopy -R .eeprom -O ihex ${PRJ}.elf ${PRJ}.hex DEPENDS strip)
add_custom_target(upload ALL avrdude -c ${PROG_TYPE} -b 57600 -P ${PORT} -p ${MCU} -U flash:w:${PRJ}.hex DEPENDS hex)
    
