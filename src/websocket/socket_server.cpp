#include "socket_server.hpp"

namespace TableDisco
{
    SocketServer* SocketServerPointer = NULL;

    SocketServer::SocketServer()
    {
        TableDisco::SocketServerPointer = this;
        auto webSocketEvent = [](uint8_t num, WStype_t type, uint8_t * payload, size_t length) 
        {
            switch(type) {
                case WStype_DISCONNECTED:
                    Serial.printf("[%u] Disconnected!\n", num);
                    break;
                case WStype_CONNECTED:
                    IPAddress ip = SocketServerPointer->webSocket.remoteIP(num);
                    Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
                    break;
            }
        };

        webSocket.begin();
        webSocket.onEvent(webSocketEvent);
    }

    void SocketServer::broadcast(String data)
    {
        webSocket.broadcastTXT(data);
    }

    void SocketServer::loop()
    {
        webSocket.loop();
    }
}