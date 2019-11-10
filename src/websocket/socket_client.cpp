#include "socket_client.hpp"

namespace TableDisco
{
    SocketClient* SocketClientPointer = NULL;

    SocketClient::SocketClient()
    {
        TableDisco::SocketClientPointer = this;
    }

    void SocketClient::start(String socketIp)
    {        
        auto webSocketEvent = [](WStype_t type, uint8_t * payload, size_t length) 
        {
            switch(type) {
                case WStype_DISCONNECTED:
                    Serial.printf("[WSC] Disconnected!\n");
                    break;
                case WStype_CONNECTED:
                    Serial.printf("[WSC] Connected to url: %s\n", payload);
                    break;
                case WStype_TEXT:
                    Serial.printf("[WSC] get text: %s\n", payload);
                    break;
            }
        };

        webSocket.begin(socketIp, 81, "/");
        webSocket.onEvent(webSocketEvent);
        webSocket.setReconnectInterval(5000);
        webSocket.enableHeartbeat(15000, 3000, 2);
    }
}