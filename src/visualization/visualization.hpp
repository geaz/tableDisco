#pragma once
#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include <deque>
#include "../led/led.hpp"

namespace TableDisco
{    
    static const unsigned char Noise = 35;  // Pretty high noise, because of the LEDs even with the capacitor
    static const unsigned char MaxRMSCount = 100;
    static const unsigned char SampleWindow = 50;
    static const unsigned short FFTDataSize = 256;
    static const unsigned short SampleRate = 10000;
    static const double MinimumMaxRMS = 512 / 3;

    static const Color LowFreqColor = TableDisco::Blue;
    static const Color MidFreqColor = TableDisco::Green;
    static const Color HighFreqColor = TableDisco::Red;

    // https://en.wikipedia.org/wiki/Audio_frequency
    static const short MidFrequency = 1046; // Highest note reproducible by average female
    static const short MaxFrequency = 2093; // Everything above will be full HighFreqColor

    class Visualization
    {
        public:
            Visualization(LED& led);

            void loop();
            void toogleDiscoMode();

        private:
            double collectSamples();
            unsigned char getVolumeBrightness(const float sampleRMS) const;
            unsigned short getDominantFrequency();
            void visualizeData(unsigned char volumeBrightness, unsigned short dominantFrequency);

            LED& led;
            bool isDiscoMode = false;
            int16_t fftData[FFTDataSize];
            std::deque<double> lastRMSDeque;
    };
}

#endif // VISUALIZATION_H