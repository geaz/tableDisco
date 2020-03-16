#ifndef TABLEDISCO_H
#define TABLEDISCO_H

#include "../led/led.hpp"
#include "../mesh/mesh.hpp"
#include "../websocket/socket_server.hpp"
#include "../websocket/socket_client.hpp"
#include "../visualization/sound_visualization.hpp"

namespace TableDisco 
{
    class Disco 
    {
        public:
            void setup();
            void loop();
            void switchMode();

        private:            
            void handleReceivedText(String receivedText);

            LED led;
            Mesh mesh;
            SocketServer socketServer;
            SocketClient socketClient = SocketClient(led);
            SoundVisualization soundVisualzation;

            bool userSwitched = false;
            bool isDiscoMode = false;
            bool isRootDiscoMode = false;
            char lastButtonVal = LOW;

            Color lastColor;
            unsigned long lastColorUpdate, lastButtonUpdate = 0;
    };
}

#endif // TABLEDISCO_H