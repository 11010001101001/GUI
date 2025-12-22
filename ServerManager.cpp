#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <ctime>
#include <esp_system.h>
#include "ServerManager.h"
#include "DisplayManager.h"
#include "LightManager.h"

ServerManager::ServerManager(DisplayManager &displayManager, LightManager &lightManager)
    : server(80), displayManager(displayManager), lightManager(lightManager) {}

void ServerManager::setup()
{
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        displayManager.displayText("Connecting...");
        lightManager.turnOnRed();
        delay(500);
    }

    handleRequests();

    String ip = WiFi.localIP().toString();
    displayManager.displayText("Connected " + ip);
    lightManager.turnOnGreen();

    configTime(3 * 3600, 0, "pool.ntp.org", "time.nist.gov");

    handleStandby();
}

void ServerManager::handleRequests()
{
    server.on("/load", [this]()
              { handleLoading(); });
    server.on("/speak", [this]()
              { handleSpeaking(); });
    server.on("/listen", [this]()
              { handleListening(); });
    server.on("/error", [this]()
              { handleError(); });
    server.on("/standby", [this]()
              { handleStandby(); });

    server.begin();
}

void ServerManager::serveClient()
{
    server.handleClient();

    if (isLoading)
    {
        lightManager.blink();
    }

    scheduleReboot();
    vTaskDelay(1);
}

void ServerManager::scheduleReboot()
{
    unsigned long currentMillis = millis();
    bool isHourGone = currentMillis - previousMillis >= hour;

    if (isHourGone)
    {
        previousMillis = currentMillis;

        time_t now = time(0);
        struct tm *lt = localtime(&now);
        int hour = lt->tm_hour;
        bool isRebootTime = hour == 4;

        if (isRebootTime && !isRebooting)
        {
            isRebooting = true;
            isLoading = false;

            lightManager.turnOnBlack();
            displayManager.displayText("Rebooting...");

            ESP.restart();
        }
    }
}

void ServerManager::handleLoading()
{
    server.send(200, "text/plain", "loading");
    if (!isLoading)
    {
        isLoading = true;
        displayManager.displayImage(DisplayManager::ImagesCategory::Listen);
    }
}

void ServerManager::handleSpeaking()
{
    server.send(200, "text/plain", "error");
    isLoading = false;
    displayManager.displayImage(DisplayManager::ImagesCategory::Speak);
    lightManager.turnOnCyan();
}

void ServerManager::handleError()
{
    server.send(200, "text/plain", "error");
    isLoading = false;
    displayManager.displayImage(DisplayManager::ImagesCategory::Error);
    lightManager.turnOnRed();
}

void ServerManager::handleListening()
{
    server.send(200, "text/plain", "listening");
    isLoading = false;
    displayManager.displayImage(DisplayManager::ImagesCategory::Listen);
    lightManager.turnOnMagenta();
}

void ServerManager::handleStandby()
{
    server.send(200, "text/plain", "standby");
    isLoading = false;
    lightManager.turnOnBlack();
    displayManager.displayOff();
}
