#include "visualization.hpp"

namespace TableDisco
{
    Visualization::Visualization(LED& led) : led(led) { }

    void Visualization::loop()
    {
        if(!isDiscoMode) return;
        led.fade(0.75, minBrightness);

        uint32_t currentValue = analogRead(A0);
        minValue = currentValue < minValue ? currentValue : minValue;
        maxValue = currentValue > maxValue ? currentValue : maxValue;
        
        float silentValue = (maxValue + minValue) / 2.0;
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
        lastVolume = volume;  
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

    void Visualization::setBrightnessRange(const uint8_t newMinBrightness, const uint8_t newMaxBrightness)
    {
        minBrightness = newMinBrightness;
        maxBrightness = newMaxBrightness;
    }
}