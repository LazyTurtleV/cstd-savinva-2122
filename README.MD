### General info

Student: Volodymyr Savin  
Group: CE-47  
Subject: CSDT  
Version: 1.1

Project Name: tic-tac-toe game  
Programming language: C  
HW interface: UART  
Data driven format: binary  
Target board: **arduino uno**  
Target OS: **Linux**

Play modes:  
>Man vs AI  
>Man vs Man  
>AI vs AI

AI supports complexity lvls:    
>Random move  
>Win strategy

Actions:  
>New  
>Save  
>Load

### Requirements

For automated build **cmake** and **git** are required, other software'll be installed automatically.  
For manual it's needed:
* gcc-avr
* binutils-avr
* avr-libc
* avrdude
* arduino-mk
* git clone https://github.com/queezythegreat/arduino-cmake into ServerSide folder

### Build

To start automated build & firmware execute ci.sh.  
For manual build:
* met requirements
* cmake -S ./ServerSide/ -B ./ServerSide/build/  
**in order to build a serverside**
* cd ./ServerSide/build  
make upload  
cd ../../  
**in order to firmware the HW**
* cmake -S ./Client/ -B ./Client/build/  
cd ./Client/build  
make  
**in order to build a client**

### Running the client

To run the client ./Client/build/appclient 

### Testing

The project uses gtest testing framework, it'll be automatically installed on automated build execution.  
Tests are automatically run on automated build or you can do it yourself by running **ctest --verbose** (or any other set of flags)
in ./Tests dir