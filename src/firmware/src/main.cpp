#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266httpUpdate.h>
#include "led/led.hpp"
#include "wifi/disco_wifi.hpp"
#include "disco/disco.hpp"

TableDisco::LED led;
TableDisco::DiscoWifi wifi;
TableDisco::Disco disco(led, wifi);
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

    // Check for updater, if button pressed during startup
    if(digitalRead(D2) == HIGH)
    {
        led.setColor(TableDisco::Cyan);
        Serial.println("Checking for updates ...");
        Serial.println("Scanning for Updater ...");

        while(!wifi.isUpdaterAvailable())
        {
            delay(500);
            Serial.print(".");
            led.blink(TableDisco::Cyan, 1);
        }
        Serial.println();

        led.setColor(TableDisco::Yellow);
        wifi.connectToUpdater();
        led.setColor(TableDisco::Blue);
        ESPhttpUpdate.update("192.168.255.1", 80, "/update");        
    }
    // Else start normally
    else
    {
        // Setting up Disco
        wifi.startMesh();
        disco.setup();
    }
}

void loop() 
{    
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