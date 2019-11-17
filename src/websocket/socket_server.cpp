#include "socket_server.hpp"

namespace TableDisco
{
    SocketServer::SocketServer()
    {
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