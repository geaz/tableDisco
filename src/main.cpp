#include <Arduino.h>
#include <FastLED.h>

#include "led/led.hpp"
#include "mesh/mesh.hpp"
#include "websocket/socket_server.hpp"
#include "websocket/socket_client.hpp"
#include "visualization/sound_visualization.hpp"

// Activate ASYNC Websockets - With SYNC Websockets -> Frequent Disconnects
#define WEBSOCKETS_NETWORK_TYPE NETWORK_ESP8266_ASYNC

TableDisco::LED led;
TableDisco::Mesh mesh(led);
TableDisco::SocketServer socketServer;
TableDisco::SocketClient socketClient(led);
TableDisco::SoundVisualization soundVisualzation;

bool isRootDiscoMode = false;
bool isDiscoMode = false;
char lastButtonVal = LOW;

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

void setup() 
{
    Serial.begin(9600);
    Serial.println("Starting TableDisco ...");
    pinMode(A0, INPUT); 
    pinMode(D2, INPUT); 
    pinMode(D3, OUTPUT); 

    mesh.setup();
    if(!mesh.isRoot())
    {
        Serial.println("Starting as client ...");
        socketClient.start(mesh.getParentIp().toString());
    }
}

void loop() 
{    
    checkModeButton();

    // Handle button press commands
    // & WebSocket connections
    socketServer.loop();

    if(isDiscoMode) 
    {
        //led.fade(64);
        if(mesh.isRoot())
        {
            TableDisco::Color newColor = soundVisualzation.getSoundColor();
            if(newColor.Red != 0 || newColor.Green != 0 || newColor.Blue != 0)
            {
                // After getting a new color we want to broadcast it directly to 
                // all mesh nodes, before setting the leds (for better timing)
                socketServer.broadcast("set " + String(newColor.Red) + "," + String(newColor.Green) + "," + String(newColor.Blue));
                socketServer.loop();
                led.setColor(newColor);
            }        
        }
    }        
    
    if(!mesh.isRoot()) 
    {
        socketClient.loop();
        String receivedText = socketClient.getReceivedText();
        socketServer.broadcast(receivedText);
        socketServer.loop();
        handleReceivedText(receivedText);
    }
}