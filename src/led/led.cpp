#include "led.hpp"

namespace TableDisco
{
    LED::LED()
    {
        for(int index = 0; index < LedCount; index++)
            leds.push_back(CRGB::Black);

        FastLED
            .addLeds<WS2812B, DataPin, GRB>(&leds[0], LedCount)
            .setCorrection(TypicalLEDStrip);
        FastLED.setBrightness(90);
    }

    void LED::setColor(const CRGB newColor)
    {
        currentColor = newColor;
        setAllLeds(currentColor); 
    }

    void LED::setBrightness(const short brightness)
    {
        FastLED.setBrightness(brightness);
        FastLED.show();
    }

    void LED::fade(const float factor, const short stopBrightness)
    {
        uint8_t newBrightness = FastLED.getBrightness() * factor;
        if(factor > 1)
        {
            newBrightness = newBrightness > stopBrightness
                ? stopBrightness
                : newBrightness;
        }
        else
        {
            newBrightness = newBrightness < stopBrightness
                ? stopBrightness
                : newBrightness;
        }
        
        FastLED.setBrightness(newBrightness);
        FastLED.show();
    }

    void LED::blink(const CRGB blinkColor, const short times)
    {
        for(uint16_t blinkCount = 0; blinkCount < times; blinkCount++)
        {        
            setAllLeds(blinkColor);      
            delay(500);

            setAllLeds(CRGB::Black);    
            delay(500);
        }
        setAllLeds(currentColor);
    }

    void LED::setAllLeds(const CRGB color)
    {
        for(uint16_t index = 0; index < LedCount; index++)
            leds[index] = color;     
        FastLED.show();
    }
}