#pragma once
#include "../core/GuiState.h"
#include "../managers/display/DisplayManager.h"
#include "../managers/light/LightManager.h"
#include "../managers/serial/SerialManager.h"

class Coordinator {
public:
    Coordinator(
        DisplayManager& display,
        LightManager& light,
        SerialManager& serial
    ) noexcept;

    void setup() noexcept;
    void loop() noexcept;

private:
    DisplayManager& display_;
    LightManager& light_;
    SerialManager& serial_;

    void applyState(GuiState state) noexcept;
};
