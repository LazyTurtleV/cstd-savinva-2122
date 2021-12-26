#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "headers/IO.h"
#include "headers/USB.h"
#include "headers/kernel.h"
#include "headers/db.h"

void _game_loop();

int main() 
{  
    init_db();
    set_up_port("/dev/ttyUSB0");
    handshake();

    while(1)
    {
        if (main_menu())
        {
            switch (get_game_mode())
            {
                case MAN_vs_MAN:
                    _game_loop();
                    break;
                case MAN_vs_AI:
                    _combined_game_loop();
                    break;
                case AI_vs_AI:
                    _ai_game_loop();
                    break;
            }
        }
        else
            puts("Wrong input!");
    }
}

void _game_loop()
{
    while(1)
    {  
        user_input();
        if(receive_response()) return;
    }
}

void _ai_game_loop()
{
    while(!receive_response());
}

void _combined_game_loop()
{
    char isAI = 0;
    while(1)
    {
        if(!isAI) user_input();
        if(receive_response()) return;
        isAI = !isAI;
    }
}
