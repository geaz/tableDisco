#pragma once
#ifndef LED_H
#define LED_H

#include <vector>
#include <FastLED.h>
#include "color.hpp"

namespace TableDisco
{    
    static const char LedCount = 4;
    static const char DataPin = D3;

    class LED
    {    
        public:
            LED();
            
            void blink(const Color color, const char times = 3);
            
            Color getColor() const;
            void setColor(Color color);

        private:
            void setAllLeds(Color color);

            std::vector<CRGB> leds;
            Color currentColor = TableDisco::Ivory;
    };
}

#endif // LED_H