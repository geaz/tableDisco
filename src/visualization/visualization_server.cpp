#include "Adafruit_ZeroFFT.h"
#include "visualization_server.hpp"

namespace TableDisco
{
    VisualizationServer::VisualizationServer(LED& led, SocketServer& socketServer) 
        : led(led), socketServer(socketServer) { }

    void VisualizationServer::loop()
    {
        if(!isDiscoMode) return;
        led.fade(64);

        double sampleRMS = collectSamples();
        if(sampleRMS > lastRMSDeque.front())
        {
            unsigned char volumeBrightness = getVolumeBrightness(sampleRMS);
            unsigned short dominantFrequency = getDominantFrequency();
            Color color = getNewColor(volumeBrightness, dominantFrequency);
            
            socketServer.broadcast(String(color.Red) + "," + String(color.Green) + "," + String(color.Blue));
            led.setColor(color);

            Serial.print("Sample RMS: " + String(sampleRMS));
            Serial.print("| New Brightness: " + String(volumeBrightness));
            Serial.print("| Dominant Frequency: " + String(dominantFrequency) + " Hz");
            Serial.print("| New Color: " + String(color.Red) + " " + String(color.Green) + " " + String(color.Blue));
            Serial.println("");
        }        
        lastRMSDeque.push_front(sampleRMS);
        if(lastRMSDeque.size() > MaxRMSCount) lastRMSDeque.pop_back();      

        delay(30); 
    }

    void VisualizationServer::toogleDiscoMode()
    {
        isDiscoMode = !isDiscoMode;
        if(!isDiscoMode) led.setColor(TableDisco::Ivory);
        else 
        {
            led.blink(TableDisco::Cyan);
            led.setColor(TableDisco::Cyan);
        }
    }

    double VisualizationServer::collectSamples()
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

    unsigned char VisualizationServer::getVolumeBrightness(const float sampleRMS) const
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

    unsigned short VisualizationServer::getDominantFrequency() 
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

    Color VisualizationServer::getNewColor(unsigned char volumeBrightness, unsigned short dominantFrequency)
    {    
        Color newColor = { 0, 0, 0};   
        float volumeBrightnessFactor = (float)volumeBrightness / 255;
        if(dominantFrequency < MidFrequency)
        {
            unsigned short mappedRed = map(dominantFrequency, 0, MidFrequency - 1, LowFreqColor.Red, MidFreqColor.Red);
            unsigned short mappedGreen = map(dominantFrequency, 0, MidFrequency - 1, LowFreqColor.Green, MidFreqColor.Green);
            unsigned short mappedBlue = map(dominantFrequency, 0, MidFrequency - 1, LowFreqColor.Blue, MidFreqColor.Blue);
            newColor = { mappedRed * volumeBrightnessFactor, mappedGreen * volumeBrightnessFactor, mappedBlue * volumeBrightnessFactor };
        }
        else
        {
            unsigned short mappedRed = map(dominantFrequency, MidFrequency, MaxFrequency, MidFreqColor.Red, HighFreqColor.Red);
            unsigned short mappedGreen = map(dominantFrequency, MidFrequency, MaxFrequency, MidFreqColor.Green, HighFreqColor.Green);
            unsigned short mappedBlue = map(dominantFrequency, MidFrequency, MaxFrequency, MidFreqColor.Blue, HighFreqColor.Blue);
            newColor = { mappedRed * volumeBrightnessFactor, mappedGreen * volumeBrightnessFactor, mappedBlue * volumeBrightnessFactor };
        }
        return newColor;
    }
}