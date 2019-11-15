#pragma once
#ifndef LED_H
#define LED_H

#include <vector>
#include <FastLED.h>

namespace TableDisco
{
    struct Color
    {
        unsigned char Red;
        unsigned char Green;
        unsigned char Blue;
    };
    
    static const char LedCount = 4;
    static const char DataPin = D3;

    static const Color Black = { 0, 0, 0 };
    static const Color Red = { 255, 0, 0 };
    static const Color Green = { 0, 255, 0 };
    static const Color Blue = { 0, 0, 255 };
    static const Color Yellow = { 255, 255, 0 };
    static const Color Ivory = { 255, 255, 240 };
    static const Color Cyan = { 0, 255, 255 };

    class LED
    {    
        public:
            LED();

            void setColor(Color color);
            void fade(const char value);
            void blink(const Color color, const char times = 3);

        private:
            void setAllLeds(Color color);

            std::vector<CRGB> leds;
            Color currentColor = TableDisco::Ivory;
    };
}

#endif // LED_H