#pragma once
#include "DisplayManager.h"
#include "LightManager.h"
#include "ServerManager.h"

class Coordinator
{
public:
    Coordinator();
    void setup();
    void loop();

private:
    DisplayManager displayManager;
    LightManager lightManager;
    ServerManager serverManager;
};