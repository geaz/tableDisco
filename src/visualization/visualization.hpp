#pragma once
#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include "../led/led.hpp"

namespace TableDisco
{    
    static const uint8_t SampleWindow = 20;

    class Visualization
    {
        public:
            Visualization(LED& led);

            void loop();
            void toogleDiscoMode();
            void setBrightnessRange(const short newMinBrightness, const short newMaxBrightness);

        private:
            LED& led;
            bool isDiscoMode = false;
            float lastVolume = 0;
            unsigned int signalMaxOverall = 700; // Start Values to get an effect even in silent environments
            unsigned int signalMinOverall = 300; // Start Values to get an effect even in silent environments
            unsigned short minBrightness = 0;
            unsigned short maxBrightness = 200;
    };
}

#endif // VISUALIZATION_H