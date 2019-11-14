#pragma once
#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include <deque>
#include "../led/led.hpp"

namespace TableDisco
{    
    static const unsigned short Noise = 10;
    static const unsigned short MaxVolumes = 100;
    static const unsigned short MinMaxVolume = 35;
    static const unsigned short SampleWindow = 50;
    static const unsigned short FFTDataSize = 256;
    static const unsigned short SampleRate = 10000;

    static const CRGB LowFreqColor = CRGB::Blue; // Blue
    static const CRGB MidFreqColor = CRGB::Green; // Green
    static const CRGB HighFreqColor = CRGB::Red; // Red

    // https://en.wikipedia.org/wiki/Audio_frequency
    static const unsigned int MidFrequency = 1046; // Highest note reproducible by average female
    static const unsigned int MaxFrequency = 2093; // Everything above will be full HighFreqColor

    class Visualization
    {
        public:
            Visualization(LED& led);

            void loop();
            void toogleDiscoMode();
            void setBrightnessRange(const short newMinBrightness, const short newMaxBrightness);

        private:
            double getSignalRMS();
            void visualizeVolume(const double signalRMS);
            void visualizeFrequency();

            LED& led;
            bool isDiscoMode = false;
            int16_t fftData[FFTDataSize];
            std::deque<unsigned short> lastVolumeDeque;
            unsigned short minBrightness = 0;
            unsigned short maxBrightness = 255;
    };
}

#endif // VISUALIZATION_H