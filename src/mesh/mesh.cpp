#include "mesh.hpp"

namespace TableDisco
{
    Mesh::Mesh(LED& led) : led(led) { }

    void Mesh::setup()
    {
        Serial.println("Checking Mesh Mode ...");
        WiFi.mode(WIFI_STA);
        WiFi.disconnect();
        delay(100);
        
        Serial.println("Scanning for TableDiscos ...");
        int foundNetworkCount = WiFi.scanNetworks();
        int nearestTableDisco = -1;
        int discoCount = 0;
        for (int i = 0; i < foundNetworkCount; ++i)
        {
            if(WiFi.SSID(i).startsWith(SSID))
            {
                Serial.println("Found TableDisco ...");
                if (nearestTableDisco == -1 ||
                    (nearestTableDisco != -1 && WiFi.RSSI(i) > WiFi.RSSI(nearestTableDisco)))
                {
                    Serial.println("New nearest TableDisco Index " + String(i) + " ...");
                    nearestTableDisco = i;
                }
                discoCount++;
            }
        }

        WiFi.mode(WIFI_AP_STA);
        if(nearestTableDisco != -1) 
        {
            led.setColor(CRGB::Yellow);
            Serial.println("Connecting to '" + WiFi.SSID(nearestTableDisco) + "' ...");
            WiFi.begin(WiFi.SSID(nearestTableDisco), Password);
            
            Serial.println("Connected to Disco ...");
            led.blink(CRGB::Yellow);
        }  
        ssid = SSID + " #" + String(discoCount);
        WiFi.softAP(ssid, Password, 1, false, 8);

        Serial.println("Lets Party!");
        led.blink(CRGB::Green);
    }

    bool Mesh::isRoot() { return ssid.endsWith(" #0"); }
}