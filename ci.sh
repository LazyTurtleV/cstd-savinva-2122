#!/bin/bash
echo "====================================================================================="
echo -e "ESSENTIALS & LIBS INSTALLATION"
echo -e "=====================================================================================\n"

check_for_package()
{
    PKG_OK=$(dpkg-query -W --showformat='${Status}\n' $1|grep "install ok installed")
    echo Checking for $1: $PKG_OK
    if [ "" = "$PKG_OK" ]; then
    echo "No $1. Setting up $1."
    sudo apt-get --yes install $1
    fi
    echo -e "\n"
}

check_for_package gcc-avr
check_for_package binutils-avr
check_for_package avr-libc
check_for_package avrdude
check_for_package arduino-mk

if [ ! -d "./ServerSide/arduino-cmake" ]
then
    cd ./ServerSide
    git clone https://github.com/queezythegreat/arduino-cmake
    cd ../
fi

echo -e "\nDONE\n"
echo "====================================================================================="
echo "SERVERSIDE BUILD"
echo -e "=====================================================================================\n"

cmake -S ./ServerSide/ -B ./ServerSide/build/

echo -e "\nDONE\n"
echo "====================================================================================="
echo "FIRMWARE THE HW"
echo -e "=====================================================================================\n"

cd ./ServerSide/build
make upload
cd ../../

echo -e "\nDONE\n"
echo "====================================================================================="
echo "BUILD THE CLIENT"
echo -e "=====================================================================================\n"

cmake -S ./Client/ -B ./Client/build/
cd ./Client/build
make

echo -e "\nDONE\n"