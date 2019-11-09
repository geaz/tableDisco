
#include <ESP8266WiFi.h>
#include "wifi.hpp"

namespace TableDisco
{
    Wifi::Wifi(LED& led) : led(led) { }

    void Wifi::checkMode()
    {
        Serial.println("Checking Wifi Mode ...");
        WiFi.mode(WIFI_STA);
        WiFi.disconnect();
        delay(100);
        
        Serial.println("Scanning for parent TableDisco ...");
        uint32_t foundNetworkCount = WiFi.scanNetworks();
        uint32_t parentTableDiscoIndex = 0;
        bool parentFound = false;
        for (uint32_t i = 0; i < foundNetworkCount; ++i)
        {
            if(WiFi.SSID(i) == SSID)
            {
                Serial.println("Found parent TableDisco!");

                parentTableDiscoIndex = i;
                parentFound = true;
                break;
            }
        }

        if(parentFound) 
        {
            Serial.println("Parent found! Connecting to network ...");
            WiFi.mode(WIFI_STA);
            /* TODO */
        }
        else
        {
            Serial.println("No parent found. Starting new network ...");
            WiFi.mode(WIFI_AP);
            WiFi.softAP(SSID, Password);
            led.blink(CRGB::Green);
        }
    }
}