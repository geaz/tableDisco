#ifndef WIFI_H
#define WIFI_H

#include <Arduino.h>
#include <ESP8266WiFi.h>

namespace TableDisco 
{
    static const String SSID = "TableDisco Network";
    static const String Password = "FunkyDiscoBeat";
    static const String UpdaterSSID = "Table Disco Updater";
    static const String UpdaterPassword = "FunkyUpdates";

    class DiscoWifi
    {
        public:
            DiscoWifi();

            bool isUpdaterAvailable();
            void connectToUpdater();
            
            void startMesh();
            bool isRootNode();
            IPAddress getParentIp();

        private:
            String ssid = SSID;
            IPAddress parentIp;
    };
}

#endif // WIFI_H