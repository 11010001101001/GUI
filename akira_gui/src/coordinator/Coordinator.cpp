#include "Coordinator.h"

Coordinator::Coordinator(
    DisplayManager& display,
    LightManager& light,
    SerialManager& serial
) noexcept
    : display_(display), light_(light), serial_(serial) {}

void Coordinator::setup() noexcept {
    serial_.setup();
    display_.setup();
    light_.setup();
    applyState(GuiState::Standby);
}

void Coordinator::loop() noexcept {
    GuiState nextState{};
    if (serial_.pollState(nextState)) {
        applyState(nextState);
    }

    display_.update();
    light_.update();
}

void Coordinator::applyState(GuiState state) noexcept {
    switch (state) {
    case GuiState::Load:
        light_.startLoading();
        display_.showImage(DisplayManager::ImageCategory::Listen);
        break;
    case GuiState::Speak:
        light_.turnOnCyan();
        display_.showImage(DisplayManager::ImageCategory::Speak);
        break;
    case GuiState::Listen:
        light_.turnOnMagenta();
        display_.showImage(DisplayManager::ImageCategory::Listen);
        break;
    case GuiState::Error:
        light_.turnOnRed();
        display_.showImage(DisplayManager::ImageCategory::Error);
        break;
    case GuiState::Standby:
        light_.turnOnBlack();
        display_.turnOff();
        break;
    }
}
