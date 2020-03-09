#include "socket_server.hpp"

namespace TableDisco
{
    SocketServer::SocketServer()
    {
        webSocket.begin();
        webSocket.enableHeartbeat(1000, 500, 1);
    }

    void SocketServer::loop()
    {
        webSocket.loop();
    }

    void SocketServer::broadcast(String data)
    {
        webSocket.broadcastTXT(data);
    }
}