#pragma once
#ifndef SOCKETCLIENT_H
#define SOCKETCLIENT_H

#include <WebSocketsClient.h>

namespace TableDisco
{
    class SocketClient
    {
        public:
            SocketClient();

            void start(String socketIp);
        
        private:
            WebSocketsClient webSocket;;
    };

    // SocketClient Pointer for Socket callbacks
    extern SocketClient* SocketClientPointer;
}

#endif // SOCKETCLIENT_H