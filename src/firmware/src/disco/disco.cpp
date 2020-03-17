#include "disco.hpp"

namespace TableDisco
{
    Disco::Disco(LED& led, DiscoWifi& wifi) : 
        led(led), 
        wifi(wifi), 
        socketClient(SocketClient(led))
    {
        led.setColor(TableDisco::White);
    }

    void Disco::setup()
    {
        if(!wifi.isRootNode())
        {
            Serial.println("Starting as client ...");
            socketClient.start(wifi.getParentIp().toString());
            led.blink(TableDisco::Blue);
        }
        else 
        {
            Serial.println("Starting as server ...");        
            led.blink(TableDisco::Green);
        }
    }

    void Disco::loop()
    {
        // Handle button press commands & WebSocket connections
        socketServer.loop();

        // If in DiscoMode, add a delay of 50ms (Lower would be possible too maybe). Otherwise the WiFi connection will be unstable!
        if(wifi.isRootNode() && isDiscoMode && lastColorUpdate + 50 < millis())
        {
            // Fading done by server to overcome timing issues, because of heavy server work and light weight client work. 
            // If the client handles the fading by itself, it will loop faster which results in faster fading.
            // By communicating every color change over the websocket the server and the clients will stay in sync.
            TableDisco::Color currentFaded = led.getColor().getFaded(64);
            
            TableDisco::Color newColor = soundVisualzation.getSoundColor();
            newColor = newColor.isBlack()
                ? currentFaded
                : newColor;

            if(newColor != lastColor)
            {
                // After getting a new color we want to broadcast it directly to 
                // all mesh nodes, before setting the leds (for better timing)
                socketServer.broadcast("set " + String(newColor.Red) + "," + String(newColor.Green) + "," + String(newColor.Blue));
                socketServer.loop();
                led.setColor(newColor);

                lastColor = newColor;
            }
            lastColorUpdate = millis();
        }        
        else if(!wifi.isRootNode()) 
        {
            socketClient.loop();
            String receivedText = socketClient.getReceivedText();
            if(receivedText != "")
            {
                socketServer.broadcast(receivedText);
                handleReceivedText(receivedText);
            }        
            socketServer.loop();
        }
    }

    void Disco::switchMode()
    {
        if(wifi.isRootNode())
        {
            isRootDiscoMode = !isRootDiscoMode;
            isDiscoMode = !isDiscoMode;
            socketServer.broadcast("disco");

            if(isDiscoMode)
            {
                led.blink(TableDisco::Cyan);
                led.setColor(TableDisco::Black);
            }
            else led.setColor(TableDisco::White);
        }
        else
        {
            // A 'child' table disco is only allowed
            // to switch its mode, if the root table disco
            // is in disco mode. This way a table is able to
            // switch back to 'normal' mode, but not to switch to 
            // 'Disco Mode', if the root is not set to 'disco mode'.
            isDiscoMode = isRootDiscoMode
                ? !isDiscoMode
                : isRootDiscoMode;
                
            // the user switched variable gets set the first time
            // the 'child' table disco gets switched back to 'normal' mode.
            // This is necessary to auto switch new disco modes (see handleReceivedText method)
            userSwitched = true;

            if(isDiscoMode) 
            {
                led.blink(TableDisco::Cyan);
                led.setColor(TableDisco::Black);
            }
            else led.setColor(TableDisco::White);
        }
    }

    void Disco::handleReceivedText(String receivedText)
    {
        if(receivedText.startsWith("set"))
        {
            // Handles the case: if connected after parent went into disco mode
            isRootDiscoMode = true;
            if(!userSwitched) isDiscoMode = true;

            if(isDiscoMode)
            {
                String rgbText = receivedText.substring(4);
                short delimiterPos = rgbText.indexOf(',');

                TableDisco::Color newColor;
                newColor.Red = rgbText.substring(0, delimiterPos).toInt();

                rgbText = rgbText.substring(delimiterPos + 1);
                delimiterPos = rgbText.indexOf(',');
                newColor.Green = rgbText.substring(0, delimiterPos).toInt();

                rgbText = rgbText.substring(delimiterPos + 1);
                delimiterPos = rgbText.indexOf(',');
                newColor.Blue = rgbText.substring(0, delimiterPos).toInt();
                
                Serial.println(String(newColor.Red) + " " + String(newColor.Green) + " " + String(newColor.Blue));
                led.setColor(newColor);
            }        
        }
        else if(receivedText == "disco")
        {
            isRootDiscoMode = !isRootDiscoMode;
            isDiscoMode = isRootDiscoMode;
            
            if(isDiscoMode)
            {
                led.blink(TableDisco::Cyan);
                led.setColor(TableDisco::Black);
            }
            else led.setColor(TableDisco::White);
        }
    }
}