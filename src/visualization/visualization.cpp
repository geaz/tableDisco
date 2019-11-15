#include "Adafruit_ZeroFFT.h"
#include "visualization.hpp"

namespace TableDisco
{
    Visualization::Visualization(LED& led) : led(led) { }

    void Visualization::loop()
    {
        if(!isDiscoMode) return;
        led.fade(64);

        double sampleRMS = collectSamples();
        if(sampleRMS > lastRMSDeque.front())
        {
            unsigned char volumeBrightness = getVolumeBrightness(sampleRMS);
            unsigned short dominantFrequency = getDominantFrequency();
            visualizeData(volumeBrightness, dominantFrequency);

            Serial.print("Sample RMS: " + String(sampleRMS));
            Serial.print("| New Brightness: " + String(volumeBrightness));
            Serial.print("| Dominant Frequency: " + String(dominantFrequency) + " Hz");
            Serial.println("");
        }        
        lastRMSDeque.push_front(sampleRMS);
        if(lastRMSDeque.size() > MaxRMSCount) lastRMSDeque.pop_back();      

        delay(30); 
    }

    void Visualization::toogleDiscoMode()
    {
        isDiscoMode = !isDiscoMode;
        if(!isDiscoMode) led.setColor(TableDisco::Ivory);
        else 
        {
            led.blink(TableDisco::Cyan);
            led.setColor(TableDisco::Cyan);
        }
    }

    double Visualization::collectSamples()
    {
        unsigned short signalMax = 0;
        unsigned short signalMin = 1024;
        unsigned short signalCount = 0;
        unsigned long signalSquare = 0;
        unsigned long startMillis = millis();    

        while(millis() - startMillis < SampleWindow)
        {
            unsigned short sample = analogRead(A0);
            signalMin = min(signalMin, sample);
            signalMax = max(signalMax, sample);
            signalSquare += sample * sample;
            
            if(signalCount < FFTDataSize) fftData[signalCount] = sample;
            signalCount++;
        }
        double sampleRMS = sqrt(signalSquare / signalCount);
        sampleRMS = abs(sampleRMS - 512); 
        sampleRMS = sampleRMS <= Noise ? 0 : sampleRMS - Noise;

        return sampleRMS;
    }

    unsigned char Visualization::getVolumeBrightness(const float sampleRMS) const
    {
        double minRMS = sampleRMS;
        double maxRMS = sampleRMS;
        for(double lastRMS : lastRMSDeque) {
            minRMS = min(minRMS, lastRMS);
            maxRMS = max(maxRMS, lastRMS);
        }
        maxRMS = max(maxRMS, MinimumMaxRMS);

        return map(sampleRMS, minRMS, maxRMS, 0, 255);
    }

    unsigned short Visualization::getDominantFrequency() 
    {
        ZeroFFT(fftData, FFTDataSize);
        unsigned short dominantFrequency = 0;
        short dominantFrequencyData = 0;

        // Discard first two bins (We want to ignore silence)
        for(unsigned short i = 2; i < FFTDataSize / 2; i++)
        {
            if(fftData[i] > dominantFrequencyData)
            {
                dominantFrequency = FFT_BIN(i, SampleRate, FFTDataSize);
                dominantFrequencyData = fftData[i];
            }
        }
        return dominantFrequency > MaxFrequency ? MaxFrequency : dominantFrequency;
    }

    void Visualization::visualizeData(unsigned char volumeBrightness, unsigned short dominantFrequency)
    {       
        float volumeBrightnessFactor = (float)volumeBrightness / 255;
        if(dominantFrequency < MidFrequency)
        {
            unsigned short mappedRed = map(dominantFrequency, 0, MidFrequency - 1, LowFreqColor.Red, MidFreqColor.Red);
            unsigned short mappedGreen = map(dominantFrequency, 0, MidFrequency - 1, LowFreqColor.Green, MidFreqColor.Green);
            unsigned short mappedBlue = map(dominantFrequency, 0, MidFrequency - 1, LowFreqColor.Blue, MidFreqColor.Blue);
            led.setColor({ mappedRed * volumeBrightnessFactor, mappedGreen * volumeBrightnessFactor, mappedBlue * volumeBrightnessFactor });
        }
        else
        {
            unsigned short mappedRed = map(dominantFrequency, MidFrequency, MaxFrequency, MidFreqColor.Red, HighFreqColor.Red);
            unsigned short mappedGreen = map(dominantFrequency, MidFrequency, MaxFrequency, MidFreqColor.Green, HighFreqColor.Green);
            unsigned short mappedBlue = map(dominantFrequency, MidFrequency, MaxFrequency, MidFreqColor.Blue, HighFreqColor.Blue);
            led.setColor({ mappedRed * volumeBrightnessFactor, mappedGreen * volumeBrightnessFactor, mappedBlue * volumeBrightnessFactor });
        }
    }
}