#pragma once
#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H

#include <WebSocketsServer.h>

namespace TableDisco
{
    class SocketServer
    {
        public:
            SocketServer();
            
            void broadcast(String data);
            void loop();
        
        private:
            WebSocketsServer webSocket = WebSocketsServer(81);
    };

    // SocketServer Pointer for Socket callbacks
    extern SocketServer* SocketServerPointer;
}

#endif // SOCKETSERVER_H