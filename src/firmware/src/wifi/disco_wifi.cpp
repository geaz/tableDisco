#include "disco_wifi.hpp"

namespace TableDisco
{
    DiscoWifi::DiscoWifi()
    {
        WiFi.disconnect();
        WiFi.mode(WIFI_AP_STA);
        WiFi.setSleepMode(WIFI_NONE_SLEEP);
    }

    bool DiscoWifi::isUpdaterAvailable()
    {
        bool isAvailable = false;
        unsigned char foundNetworkCount = WiFi.scanNetworks();
        for (int i = 0; i < foundNetworkCount; ++i)
        {
            if(WiFi.SSID(i).equals("Table Disco Updater"))
            {
                isAvailable = true;
                break;
            }
        }
        return isAvailable;
    }

    void DiscoWifi::connectToUpdater()
    {
        unsigned char foundNetworkCount = WiFi.scanNetworks();
        unsigned char updaterId = -1;
        for (int i = 0; i < foundNetworkCount; ++i)
        {
            if(WiFi.SSID(i).equals(UpdaterSSID))
            {
                updaterId = i;
                break;
            }
        }

        WiFi.begin(WiFi.SSID(updaterId), UpdaterPassword);    
        while (WiFi.status() != WL_CONNECTED)
        {
            delay(500);
            Serial.print(".");
        }  
    }

    void DiscoWifi::startMesh()
    {
        Serial.println("Scanning for TableDiscos ...");
        unsigned char foundNetworkCount = WiFi.scanNetworks();
        unsigned char discoNr = 1;
        short nearestTableDisco = -1;
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

        if(nearestTableDisco != -1) 
        {
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
    }

    bool DiscoWifi::isRootNode() 
    { 
        return ssid.endsWith(" #1"); 
    }

    IPAddress DiscoWifi::getParentIp()
    {
        return parentIp;
    }
}