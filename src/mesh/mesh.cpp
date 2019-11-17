#include "mesh.hpp"

namespace TableDisco
{
    Mesh::Mesh(LED& led) : led(led) { }

    void Mesh::setup()
    {
        WiFi.mode(WIFI_STA);
        WiFi.disconnect();
        delay(100);
        
        Serial.println("Scanning for TableDiscos ...");
        int foundNetworkCount = WiFi.scanNetworks();
        int nearestTableDisco = -1;
        int discoNr = 1;
        for (int i = 0; i < foundNetworkCount; ++i)
        {
            if(WiFi.SSID(i).startsWith(SSID))
            {
                if (nearestTableDisco == -1 ||
                    (nearestTableDisco != -1 && WiFi.RSSI(i) > WiFi.RSSI(nearestTableDisco)))
                {
                    nearestTableDisco = i;
                }
                discoNr++;
            }
        }

        WiFi.mode(WIFI_AP_STA);
        if(nearestTableDisco != -1) 
        {
            led.blink(TableDisco::Yellow, 2);
            Serial.print("Connecting to '" + WiFi.SSID(nearestTableDisco) + "'");
            WiFi.begin(WiFi.SSID(nearestTableDisco), Password);     
            while (WiFi.status() != WL_CONNECTED)
            {
                delay(500);
                Serial.print(".");
            }       
            Serial.println(" Connected!");
            parentIp = IPAddress(192, 168, discoNr - 1, 1);
        }  
        
        ssid = SSID + " #" + String(discoNr);
        WiFi.softAPConfig(
            IPAddress(192, 168, discoNr, 1), 
            IPAddress(0, 0, 0, 0), 
            IPAddress(255, 255, 255, 0));
        WiFi.softAP(ssid, Password, 1, false, 8);

        Serial.println("Disco AP IP: " + WiFi.softAPIP().toString());
        Serial.println("Disco Local IP: " + WiFi.localIP().toString());                
        Serial.println("Lets Party!");
        led.blink(TableDisco::Green);
    }

    bool Mesh::isRoot() 
    { 
        return ssid.endsWith(" #1"); 
    }

    IPAddress Mesh::getParentIp()
    {
        return parentIp;
    }
}