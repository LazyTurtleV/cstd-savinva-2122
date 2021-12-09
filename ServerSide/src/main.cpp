#include <Arduino.h>

#include "../headers/kernel.h"

extern "C" 
{

}

void setup()
{   
    Serial.begin(9600);
}

void loop()
{
    Serial.println("HELLO WORLD!!!");
    delay(1000);
}
