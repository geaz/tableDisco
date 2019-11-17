#pragma once
#ifndef MESH_H
#define MESH_H

#include <Arduino.h>
#include <ESP8266WiFi.h>

namespace TableDisco
{    
    static const String SSID = "TableDisco Network";
    static const String Password = "FunkyDiscoBeat";

    class Mesh 
    {
        public:
            void setup();
            bool isRoot();
            IPAddress getParentIp();

        private:
            String ssid = SSID;
            IPAddress parentIp;
    };
}

#endif // MESH_H