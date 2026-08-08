#include "Coordinator.h"
#include "DisplayManager.h"
#include "LightManager.h"
#include "ServerManager.h"

Coordinator::Coordinator()
    : serverManager(displayManager, lightManager) {}

void Coordinator::setup()
{
    displayManager.setup();
    lightManager.setup();
    serverManager.setup();
}

void Coordinator::loop()
{
    serverManager.serveClient();
}
