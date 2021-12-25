#ifdef ARDUINO_MOCK
#   include "../../Tests/headers/Arduino.h"
#else 
#   include <Arduino.h>
#endif

#include <time.h>
#include <stdlib.h>

#include "../headers/essentials.h"
#include "../headers/input.h"
#include "../headers/kernel.h"

void setup()
{   
    Serial.begin(9600);

    srand(time(0));

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
    if(LOAD_REQUEST == ( mode & 0xFF ))
    {
        char *li = receive_load_info();
        init_game(li);
        Serial.print((char)1);

        mode = receive_mode();
        Serial.print((char)1);
    }
    else
    {
        init_game(NULL);
        Serial.print((char)1);
    }

    switch( mode ){
        case MAN_vs_MAN:
        {
            game_session();
            break;
        }
        case MAN_vs_AI:
        {   
            set_up_ai();
            combined_game_session();
            break;
        }
        case AI_vs_AI:
        {
            set_up_ai();
            AI_game_session();
            break;
        }
    }

}
