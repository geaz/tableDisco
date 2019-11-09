#pragma once
#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include "../led/led.hpp"

namespace TableDisco
{
    class Visualization
    {
        public:
            Visualization(LED& led);

            void loop();
            void toogleDiscoMode();
            void setBrightnessRange(const uint8_t newMinBrightness, const uint8_t newMaxBrightness);

        private:
            LED& led;
            bool isDiscoMode = false;
            float lastVolume = 0;
            uint32_t maxValue = 0;
            uint32_t minValue = 1023;
            uint8_t minBrightness = 1;
            uint8_t maxBrightness = 90;
    };
}

#endif // VISUALIZATION_H