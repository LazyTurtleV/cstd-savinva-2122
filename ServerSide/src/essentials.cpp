#include <Arduino.h>

#include "../headers/kernel.h"
#include "../headers/input.h"

void game_session()
{   
    init_game();

    while(1)
    {
        char *in = receive_input();

        char move_stat = make_move(in[0], in[1]);
        Serial.print(move_stat);

        char game_stat = game_status();
        Serial.print(game_stat);
        if (game_stat != GAME_CONTINUES)
        {
            announce_winner();
            break;
        }
    }

    end_game();
}