#include <Arduino.h>
#include <FastLED.h>

#include "led/led.hpp"
#include "mesh/mesh.hpp"
#include "websocket/socket_server.hpp"
#include "websocket/socket_client.hpp"
#include "visualization/visualization.hpp"

TableDisco::LED led;
TableDisco::Mesh mesh(led);
TableDisco::Visualization visualization(led);
TableDisco::SocketServer socketServer;
TableDisco::SocketClient socketClient;

char lastButtonVal = LOW;

void checkModeButton()
{
    char buttonVal = digitalRead(D2);
    if(buttonVal == HIGH && lastButtonVal == LOW)
        visualization.toogleDiscoMode();
    lastButtonVal = buttonVal;
}

void setup() 
{
    Serial.begin(9600);
    Serial.println("Starting TableDisco ...");
    pinMode(D2, INPUT); 

    mesh.setup();
    if(!mesh.isRoot())
    {
        socketClient.start(mesh.getParentIp());
    }
}

int count = 0;
void loop() 
{
    checkModeButton();
    if(mesh.isRoot())
    {
        visualization.loop();
        socketServer.broadcast("Test " + String(count++));
    }    
    socketServer.loop();
}