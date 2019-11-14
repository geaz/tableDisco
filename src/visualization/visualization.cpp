#include "Adafruit_ZeroFFT.h"
#include "visualization.hpp"

namespace TableDisco
{
    Visualization::Visualization(LED& led) : led(led) { }

    void Visualization::loop()
    {
        if(!isDiscoMode) return;
        led.fade(0.75, minBrightness);

        unsigned int signalMax = 0;
        unsigned int signalMin = 1024;
        unsigned int signalCount = 0;
        unsigned long signalSquare = 0;
        unsigned long startMillis = millis();    

        while(millis() - startMillis < SampleWindow)
        {
            unsigned int sample = analogRead(A0);
            signalMin = min(signalMin, sample);
            signalMax = max(signalMax, sample);
            signalSquare += sample * sample;
            
            if(signalCount < FFTDataSize) fftData[signalCount] = sample;
            signalCount++;
        }
        double signalRMS = sqrt(signalSquare / signalCount);
        signalRMS = abs(signalRMS - 512); 
        signalRMS = signalRMS <= Noise ? 0 : signalRMS - Noise;

        unsigned short volume = map(signalRMS, 0, 512, 0, 100); 
        if(volume > lastVolumeDeque.front()) 
        {            
            unsigned short minVolume = volume;
            unsigned short maxVolume = volume;
            for(unsigned short lastVol : lastVolumeDeque) {
                minVolume = min(minVolume, lastVol);
                maxVolume = max(maxVolume, lastVol);
            } 
            maxVolume = max(maxVolume, MinMaxVolume);
            
            unsigned short newBrightness = map(volume, minVolume, maxVolume, minBrightness, maxBrightness);
            double newBrightnessFactor = (double)newBrightness / maxBrightness;

            ZeroFFT(fftData, FFTDataSize);
            unsigned int dominantFrequency = 0;
            int dominantFrequencyData = 0;

            // Discard first two bins (We want to ignore silence)
            for(int i = 2; i < FFTDataSize / 2; i++)
            {
                if(fftData[i] > dominantFrequencyData)
                {
                    dominantFrequency = FFT_BIN(i, SampleRate, FFTDataSize);
                    dominantFrequencyData = fftData[i];
                }
            }
            dominantFrequency = dominantFrequency > MaxFrequency ? MaxFrequency : dominantFrequency;
            if(dominantFrequency < MidFrequency)
            {
                unsigned short mappedRed = map(dominantFrequency, 0, MidFrequency - 1, LowFreqColor.red, MidFreqColor.red);
                unsigned short mappedGreen = map(dominantFrequency, 0, MidFrequency - 1, LowFreqColor.green, MidFreqColor.green);
                unsigned short mappedBlue = map(dominantFrequency, 0, MidFrequency - 1, LowFreqColor.blue, MidFreqColor.blue);
                led.setColor(CRGB(mappedRed * newBrightnessFactor, mappedGreen * newBrightnessFactor, mappedBlue * newBrightnessFactor));
            }
            else
            {
                unsigned short mappedRed = map(dominantFrequency, MidFrequency, MaxFrequency, MidFreqColor.red, HighFreqColor.red);
                unsigned short mappedGreen = map(dominantFrequency, MidFrequency, MaxFrequency, MidFreqColor.green, HighFreqColor.green);
                unsigned short mappedBlue = map(dominantFrequency, MidFrequency, MaxFrequency, MidFreqColor.blue, HighFreqColor.blue);
                led.setColor(CRGB(mappedRed * newBrightnessFactor, mappedGreen * newBrightnessFactor, mappedBlue * newBrightnessFactor));
            }

            Serial.print("Sample RMS: " + String(signalRMS));
            Serial.print("| Sample Count: " + String(signalCount));
            Serial.print("| Volume (min, max): " + String(minVolume) + " " + String(maxVolume));
            Serial.print("| Volume (current): " + String(volume));
            Serial.print("| New Brightness: " + String(newBrightness));
            Serial.print("| Dominant Frequency: " + String(dominantFrequency) + " Hz");
            Serial.println("");
        } 
        lastVolumeDeque.push_front(volume);
        if(lastVolumeDeque.size() > MaxVolumes) lastVolumeDeque.pop_back();

        delay(30); 
    }

    void Visualization::toogleDiscoMode()
    {
        isDiscoMode = !isDiscoMode;
        if(!isDiscoMode) led.setColor(CRGB::Ivory);
        else 
        {
            led.blink(CRGB::Cyan);
            led.setColor(CRGB::Cyan);
        }
    }

    void Visualization::setBrightnessRange(const short newMinBrightness, const short newMaxBrightness)
    {
        minBrightness = newMinBrightness;
        maxBrightness = newMaxBrightness;
    }
}