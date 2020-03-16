#include <Arduino.h>
#include <ESP8266HTTPUpdateServer.h>
#include "disco/disco.hpp"

ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;

TableDisco::Disco disco;
char lastButtonVal = LOW;
unsigned long lastButtonUpdate = 0;

void checkModeButton();

void setup() 
{
    Serial.begin(9600);
    Serial.println("Starting TableDisco ...");
    pinMode(A0, INPUT);     // Mic Input
    pinMode(D2, INPUT);     // Switch Mode Button
    pinMode(D3, OUTPUT);    // LED Data

    // Setting up Disco
    disco.setup();

    // Setting up Update Server
    httpUpdater.setup(&httpServer);
    httpServer.begin();
}

void loop() 
{    
    // Handle Update Server
    httpServer.handleClient();
    // Handle Table Disco
    checkModeButton();
    disco.loop();
}

// Check, if the switch mode button was pressed
void checkModeButton()
{
    // Only check the button every 100 millis
    // this was necessary because of the button type I was using in my build
    if(lastButtonUpdate + 100 > millis()) return;

    char buttonVal = digitalRead(D2);
    if(buttonVal == HIGH && lastButtonVal == LOW)
    {
        disco.switchMode();
    }
    lastButtonVal = buttonVal;
    lastButtonUpdate = millis();
}