#include <Arduino.h>

#include "../headers/essentials.h"
#include "../headers/input.h"

void setup()
{   
    Serial.begin(9600);

    //until connection with serial is established
    while(!Serial);

    //try to establish communication between Server and client
    char connection_status = 0x00;
    do
    {
        connection_status = handshake();
        delay(1000);
        Serial.print(connection_status);
    }
    while( (connection_status & 0xFF) != HANDSHAKE_CONST);
}

void loop()
{   
    game_session();
}
