#pragma once
#ifndef MESH_H
#define MESH_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "../led/led.hpp"

namespace TableDisco
{    
    static const String SSID = "TableDisco Network";
    static const String Password = "FunkyDiscoBeat";

    class Mesh 
    {
        public:
            Mesh(LED& led);

            void setup();
            bool isRoot();
            IPAddress getParentIp();

        private:
            LED& led;
            String ssid = SSID;
            IPAddress parentIp;
    };
}

#endif // MESH_H