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
    char mode = receive_mode();
    Serial.print((char)1);
    if(LOAD_REQUEST == mode)
    {
        char *li = receive_load_info();
        init_game(li);

        mode = receive_mode();
        Serial.print((char)1);
    }
    else
    {
        init_game(NULL);
    }

    switch( mode ){
        case MAN_vs_MAN:
        {
            game_session();
            break;
        }
    }

}
