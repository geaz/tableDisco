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
            signalCount++;
        }
        signalMinOverall = min(signalMinOverall, signalMin);
        signalMaxOverall = max(signalMaxOverall, signalMax);

        float silentValue = (signalMaxOverall + signalMinOverall) / 2.0;
        double signalRMS = sqrt(signalSquare / signalCount);
        unsigned long volume = map(abs(signalRMS - silentValue), 0, 511, 0, 100);

        Serial.print("Samples: " + String(signalCount));
        Serial.print("| Min (Samples, Overall): " + String(signalMin) + ", " + String(signalMinOverall));
        Serial.print("| Max (Samples, Overall): " + String(signalMax) + ", " + String(signalMaxOverall));
        Serial.print("| Root Mean Square: " + String(signalRMS));
        Serial.print("| Silent: " + String(silentValue));
        Serial.print("| Volume: " + String(volume));
        Serial.println("");

        /*float silentValue = (maxValue + minValue) / 2.0;
        float totalTicks = (maxValue - minValue) / 2.0;

        // Volume 0.0 - 1
        float volume = fabs(currentValue - silentValue) / totalTicks;

        if(volume > lastVolume && volume > 0.1)
        {
            Serial.print("Volume: ");
            Serial.println(volume);
            Serial.print("MinB: ");
            Serial.println(minBrightness);
            Serial.print("MaxB: ");
            Serial.println(maxBrightness);
            Serial.print("MinV: ");
            Serial.println(minValue);
            Serial.print("MaxV: ");
            Serial.println(maxValue);

            uint8_t newBrightness = ((maxBrightness - minBrightness) * volume) + minBrightness;        
            Serial.print("Brightness: ");
            Serial.println(newBrightness);

            led.setBrightness(newBrightness);
        }
        lastVolume = volume;  */
        FastLED.delay(30); 
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