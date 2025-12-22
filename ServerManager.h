#pragma once
#include <WebServer.h>
#include "DisplayManager.h"
#include "LightManager.h"

class ServerManager
{
public:
    ServerManager(DisplayManager &displayManager, LightManager &lightManager);
    void setup();
    void serveClient();

private:
    DisplayManager displayManager;
    LightManager lightManager;
    WebServer server;

    const char *ssid = "TP-Link_27D4";
    const char *password = "78877467";
    bool isLoading = false;
    bool isRebooting = false;
    unsigned long previousMillis = 0;
    const unsigned long hour = 3600000;

    void handleRequests();
    void scheduleReboot();
    void handleLoading();
    void handleSpeaking();
    void handleError();
    void handleListening();
    void handleStandby();
};