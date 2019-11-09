#pragma once
#ifndef LED_H
#define LED_H

#include <vector>
#include <FastLED.h>

namespace TableDisco
{
    static const uint8_t LedCount = 4;
    static const uint8_t DataPin = D3;

    class LED
    {    
        public:
            LED();

            void setColor(CRGB color);
            void setBrightness(uint8_t brightness);
            void fade(const float factor, const uint8_t stopBrightness);
            void blink(const CRGB color, const uint8_t times = 3);

        private:
            void setAllLeds(CRGB color);

            std::vector<CRGB> leds;
            CRGB currentColor = CRGB::Ivory;
    };
}

#endif // LED_H