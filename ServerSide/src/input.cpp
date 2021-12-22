#include <stdlib.h>
#ifdef ARDUINO_MOCK
#   include "../../Tests/headers/Arduino.h"
#else 
#   include <Arduino.h>
#endif

#include "../headers/input.h" 
#include "../headers/kernel.h"

#define COORD_X_MASK 0b0011
#define COORD_Y_MASK 0b1100


char* _process_package(char _package);
char _read_byte();

char* receive_input()
{
    while(!Serial.available());

    char in = Serial.read();

    return _process_package(in); 
}

char receive_mode()
{
    while(!Serial.available());

    return Serial.read();
}

char handshake()
{
    char in = _read_byte();

    Serial.print(in);

    return _read_byte();
}

char _read_byte()
{
    while(!Serial.available());

    return Serial.read();
}

char* _process_package(char _package)
{
    char *c = (char*)malloc(2);

    if ((_package & 0xFF ) == SAVE_REQUEST)
    {
        c[0] = SAVE_REQUEST;
        c[1] = SAVE_REQUEST;
    }
    else
    {
        c[0] = ( _package & COORD_Y_MASK ) >> 2;
        c[1] = _package & COORD_X_MASK;
    }

    return c;
}
