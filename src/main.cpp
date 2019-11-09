#include <Arduino.h>
#include <FastLED.h>

#include "led/led.hpp"
#include "wifi/wifi.hpp"
#include "visualization/visualization.hpp"

TableDisco::LED led;
TableDisco::Wifi wifi(led);
TableDisco::Visualization visualization(led);

uint8_t lastButtonVal = LOW;

void setup() 
{
    Serial.begin(9600);
    Serial.println("Starting TableDisco ...");
    pinMode(D2, INPUT); 

    wifi.checkMode();
}

void loop() 
{
    uint8_t buttonVal = digitalRead(D2);
    if(buttonVal == HIGH && lastButtonVal == LOW)
        visualization.toogleDiscoMode();
    lastButtonVal = buttonVal;

    visualization.loop();
}