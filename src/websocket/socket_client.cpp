#include "socket_client.hpp"

namespace TableDisco
{
    SocketClient* SocketClientPointer = NULL;

    SocketClient::SocketClient(LED& led) : led(led)
    {
        TableDisco::SocketClientPointer = this;
    }

    void SocketClient::start(String socketIp)
    {        
        auto webSocketEvent = [](WStype_t type, uint8_t * payload, size_t length) 
        {
            switch(type) 
            {
                case WStype_DISCONNECTED:              
                    Serial.println("Disconnected from WebSocket!");  
                    TableDisco::SocketClientPointer->led.blink(TableDisco::Red, 5);
                    break;
                case WStype_CONNECTED:            
                    Serial.println("Connected to WebSocket!");
                    TableDisco::SocketClientPointer->led.blink(TableDisco::Blue, 2);
                    break;
                case WStype_TEXT:
                    TableDisco::SocketClientPointer->lastLoopReceivedText = String((char*)payload);
                    break;
                default:
                    // Not interested in other cases
                    break;
            }
        };

        Serial.println("Connecting to socket '" + socketIp + "' ...");
        webSocket.begin(socketIp, 81, "/");
        webSocket.onEvent(webSocketEvent);
        webSocket.setReconnectInterval(5000);
        webSocket.enableHeartbeat(15000, 3000, 2);
    }

    void SocketClient::loop()
    {
        lastLoopReceivedText = String("");
        webSocket.loop();
    }
    
    String SocketClient::getReceivedText() const
    {
        return lastLoopReceivedText;
    }
}