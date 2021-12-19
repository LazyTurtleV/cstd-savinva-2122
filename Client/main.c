#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "headers/IO.h"
#include "headers/USB.h"

void _game_loop();

int main() 
{  
    set_up_port("/dev/ttyUSB0");

    handshake();

    while(1)
    {
        if (select_mode())
            _game_loop();
        else
            puts("Wrong input!");
    }
}

void _game_loop()
{
    while(1)
    {  
        input_coords();
        receive_response();
    }
}
