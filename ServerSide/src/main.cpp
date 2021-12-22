#ifdef ARDUINO_MOCK
#   include "../../Tests/headers/Arduino.h"
#else 
#   include <Arduino.h>
#endif

#include "../headers/essentials.h"
#include "../headers/input.h"
#include "../headers/kernel.h"

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
        Serial.print(connection_status);
    }
    while( (connection_status & 0xFF) != HANDSHAKE_CONST);
}

void loop()
{   
    switch( receive_mode() ){
        case MAN_vs_MAN:
            Serial.print(1);
            game_session();
            break;
    }

}
