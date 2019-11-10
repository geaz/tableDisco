#include <Arduino.h>
#include <FastLED.h>

#include "led/led.hpp"
#include "mesh/mesh.hpp"
#include "visualization/visualization.hpp"

TableDisco::LED led;
TableDisco::Mesh mesh(led);
TableDisco::Visualization visualization(led);

short lastButtonVal = LOW;

void setup() 
{
    Serial.begin(9600);
    Serial.println("Starting TableDisco ...");
    pinMode(D2, INPUT); 

    mesh.setup();    
}

void loop() 
{
    short buttonVal = digitalRead(D2);
    if(buttonVal == HIGH && lastButtonVal == LOW)
        visualization.toogleDiscoMode();
    lastButtonVal = buttonVal;

    visualization.loop();
}