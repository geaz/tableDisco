#include <Arduino.h>
#include <FastLED.h>

#include "led/led.hpp"
#include "mesh/mesh.hpp"
#include "websocket/socket_server.hpp"
#include "websocket/socket_client.hpp"
#include "visualization/sound_visualization.hpp"

TableDisco::LED led;
TableDisco::Mesh mesh;
TableDisco::SocketServer socketServer;
TableDisco::SocketClient socketClient(led);
TableDisco::SoundVisualization soundVisualzation;

bool isDiscoMode = false;
bool isRootDiscoMode = false;
char lastButtonVal = LOW;

TableDisco::Color lastColor;
unsigned long lastColorUpdate = 0;

void checkModeButton();
void handleReceivedText(String receivedText);

void setup() 
{
    Serial.begin(9600);
    Serial.println("Starting TableDisco ...");
    pinMode(A0, INPUT); 
    pinMode(D2, INPUT); 
    pinMode(D3, OUTPUT); 

    led.setColor(TableDisco::Ivory);
    mesh.setup();
    if(!mesh.isRoot())
    {
        Serial.println("Starting as client ...");
        socketClient.start(mesh.getParentIp().toString());
        led.blink(TableDisco::Blue);
    }
    else 
    {
        Serial.println("Starting as server ...");        
        led.blink(TableDisco::Green);
    }
}

void loop() 
{    
    checkModeButton();

    // Handle button press commands & WebSocket connections
    socketServer.loop();

    // If in DiscoMode, add a delay of 50ms (Lower would be possible too maybe). Otherwise the WiFi connection will be unstable!
    if(mesh.isRoot() && isDiscoMode && lastColorUpdate + 50 < millis())
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
    else if(!mesh.isRoot()) 
    {
        socketClient.loop();
        String receivedText = socketClient.getReceivedText();
        socketServer.broadcast(receivedText);
        socketServer.loop();
        handleReceivedText(receivedText);
    }
}

// Check, if the switch mode button was pressed
void checkModeButton()
{
    char buttonVal = digitalRead(D2);
    if(buttonVal == HIGH && lastButtonVal == LOW && mesh.isRoot())
    {
        isRootDiscoMode = !isRootDiscoMode;
        isDiscoMode = !isDiscoMode;
        socketServer.broadcast("disco");

        if(isDiscoMode) led.blink(TableDisco::Cyan);
        else led.setColor(TableDisco::Ivory);
    }
    else if(buttonVal == HIGH && lastButtonVal == LOW)
    {
        // A 'child' table disco is only allowed
        // to switch its mode, if the root table disco
        // is in disco mode. This way a table is able to
        // switch back to 'normal' mode, but not to switch to 
        // 'Disco Mode', if the root is not set to 'disco mode'.
        isDiscoMode = isRootDiscoMode
            ? !isDiscoMode
            : isRootDiscoMode;
        if(isDiscoMode) led.blink(TableDisco::Cyan);
        else led.setColor(TableDisco::Ivory);
    }
    lastButtonVal = buttonVal;
}

void handleReceivedText(String receivedText)
{
    if(receivedText.startsWith("set"))
    {
        // Handles the case: if connected after parent went into disco mode
        if(!isRootDiscoMode && !isDiscoMode)
        {
            isRootDiscoMode = true;
            isDiscoMode = true;
        }    
        
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
    else if(receivedText == "disco")
    {
        isRootDiscoMode = !isRootDiscoMode;
        isDiscoMode = !isDiscoMode;
        led.blink(TableDisco::Cyan);
    }
}