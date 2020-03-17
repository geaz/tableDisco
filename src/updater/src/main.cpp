#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>

AsyncWebServer server(80);

void setup()
{
    Serial.begin(9600);
    Serial.println("Starting Update Device ...");
    if(!SPIFFS.begin()){
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }

    Serial.println("Starting Access Point ...");
    WiFi.disconnect();
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(
        IPAddress(192, 168, 255, 1), 
        IPAddress(0, 0, 0, 0), 
        IPAddress(255, 255, 255, 0));
    WiFi.softAP("Table Disco Updater", "FunkyUpdates", 1, false, 8);

    Serial.println("Setting up web server ...");
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/index.html", String(), false);
    });
    server.on("/update", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/firmware.bin", "application/octet-stream", true);
    });
    server.begin();

    Serial.println("Device ready!");
}

void loop() { }