#ifndef TABLEDISCO_H
#define TABLEDISCO_H

#include "../led/led.hpp"
#include "../wifi/disco_wifi.hpp"
#include "../websocket/socket_server.hpp"
#include "../websocket/socket_client.hpp"
#include "../visualization/sound_visualization.hpp"

namespace TableDisco 
{
    class Disco 
    {
        public:
            Disco(LED& led, DiscoWifi& wifi);

            void setup();
            void loop();
            void switchMode();

        private:            
            void handleReceivedText(String receivedText);

            LED& led;
            DiscoWifi& wifi;
            SocketServer socketServer;
            SocketClient socketClient;
            SoundVisualization soundVisualzation;

            bool userSwitched = false;
            bool isDiscoMode = false;
            bool isRootDiscoMode = false;

            Color lastColor;
            unsigned long lastColorUpdate = 0;
    };
}

#endif // TABLEDISCO_H