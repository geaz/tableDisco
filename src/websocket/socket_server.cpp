#include "socket_server.hpp"

namespace TableDisco
{
    SocketServer* SocketServerPointer = NULL;

    SocketServer::SocketServer()
    {
        TableDisco::SocketServerPointer = this;
        webSocket.begin();
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