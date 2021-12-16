#include <Arduino.h>

#include "../headers/essentials.h"

void setup()
{   
    Serial.begin(9600);

    //until connection with serial is established
    while(!Serial);
}

void loop()
{   
    //Serial.println("Hello world!!!");
    game_session();
}
