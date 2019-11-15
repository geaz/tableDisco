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
    }

    void LED::setColor(const Color newColor)
    {
        currentColor = newColor;
        setAllLeds(currentColor); 
    }

    void LED::fade(const char value)
    {
        for(uint16_t index = 0; index < LedCount; index++)
            leds[index].fadeToBlackBy(value);     
        FastLED.show();
    }

    void LED::blink(const Color blinkColor, const char times)
    {
        for(uint16_t blinkCount = 0; blinkCount < times; blinkCount++)
        {        
            setAllLeds(blinkColor);      
            delay(500);

            setAllLeds(TableDisco::Black);    
            delay(500);
        }
        setAllLeds(currentColor);
    }

    void LED::setAllLeds(const Color color)
    {
        for(uint16_t index = 0; index < LedCount; index++)
            leds[index] = CRGB(color.Red, color.Green, color.Blue);     
        FastLED.show();
    }
}