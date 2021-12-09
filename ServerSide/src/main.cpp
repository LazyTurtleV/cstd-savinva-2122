#include <Arduino.h>

#include "../headers/kernel.h"

void setup()
{   
    Serial.begin(9600);
    Serial.setTimeout(1000);

    while(!Serial);
}

void loop()
{   
    if(!Serial.available()) return;

    char msg[100];
    memset(msg, 0, 100);
    
    Serial.readBytesUntil('0', msg, 100);
    Serial.print("Read symbol: ");
    Serial.println(msg);
}
