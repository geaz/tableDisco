#pragma once
#ifndef WIFI_H
#define WIFI_H

#include <Arduino.h>
#include "../led/led.hpp"

namespace TableDisco
{    
    static const String SSID = "WS2812B TableDisco Network";
    static const String Password = "FunkyDiscoBeat";

    class Wifi 
    {
        public:
            Wifi(LED& led);

            void checkMode();

        private:
            LED& led;
    };
}

#endif // WIFI_H