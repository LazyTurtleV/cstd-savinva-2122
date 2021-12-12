#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "headers/IO.h"

int main() 
{  
    set_up_port("/dev/ttyUSB0");

    while(1)
    {  
        input_coords();
        receive_response();
    }
}
