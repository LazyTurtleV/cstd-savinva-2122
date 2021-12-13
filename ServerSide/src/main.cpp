#include <Arduino.h>

#include "../headers/kernel.h"
#include "../headers/input.h"

void setup()
{   
    Serial.begin(9600);

    //until connection with serial is established
    while(!Serial);

    init_game();
}

void loop()
{   
    char *in = receive_input();
    if(in == WAIT_FOR_INPUT) return;

    char move_stat = make_move(in[0], in[1]);
    Serial.print(move_stat);

    char game_stat = game_status();
    Serial.print(game_stat);
    if (game_stat != GAME_CONTINUES)
    {
        announce_winner();
        end_game();
    }
}
