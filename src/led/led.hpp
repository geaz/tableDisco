#pragma once
#ifndef LED_H
#define LED_H

#include <vector>
#include <FastLED.h>

namespace TableDisco
{
    static const short LedCount = 4;
    static const short DataPin = D3;

    class LED
    {    
        public:
            LED();

            void setColor(CRGB color);
            void setBrightness(short brightness);
            void fade(const float factor, const short stopBrightness);
            void blink(const CRGB color, const short times = 3);

        private:
            void setAllLeds(CRGB color);

            std::vector<CRGB> leds;
            CRGB currentColor = CRGB::Ivory;
    };
}

#endif // LED_H