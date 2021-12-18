#include <stdlib.h>
#include <Arduino.h>

#include "../headers/input.h" 

#define COORD_X_MASK 0b0011
#define COORD_Y_MASK 0b1100


char* _process_package(char _package);

char* receive_input()
{
    while(!Serial.available());

    char in = Serial.read();

    return _process_package(in); 
}

char _read_byte()
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

char* _process_package(char _package)
{
    char *c = (char*)malloc(2);
    
    c[0] = ( _package & COORD_Y_MASK ) >> 2;
    c[1] = _package & COORD_X_MASK;

    return c;
}
