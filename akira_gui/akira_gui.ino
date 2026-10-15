#include "src/coordinator/Coordinator.h"
#include "src/managers/display/DisplayManager.h"
#include "src/managers/light/LightManager.h"
#include "src/managers/serial/SerialManager.h"

namespace {
DisplayManager displayManager;
LightManager lightManager;
SerialManager serialManager;
Coordinator coordinator(displayManager, lightManager, serialManager);
} // namespace

void setup() {
    coordinator.setup();
}

void loop() {
    coordinator.loop();
}
