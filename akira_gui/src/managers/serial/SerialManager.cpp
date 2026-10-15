#include "SerialManager.h"

void SerialManager::setup() noexcept {
    Serial.begin(kBaudRate);
    Serial.setRxBufferSize(256);
    length_ = 0;
}

bool SerialManager::pollState(GuiState& outState) noexcept {
    bool hasNewState = false;

    while (Serial.available() > 0) {
        const char ch = static_cast<char>(Serial.read());
        if (ch == '\r') {
            continue;
        }
        if (ch == '\n') {
            buffer_[length_] = '\0';
            const std::string_view cmd{buffer_, length_};
            length_ = 0;
            if (parseCommand(cmd, outState)) {
                hasNewState = true;
            }
            continue;
        }
        if (length_ < kBufferSize - 1) {
            buffer_[length_++] = ch;
        } else {
            length_ = 0;
        }
    }

    return hasNewState;
}

bool SerialManager::parseCommand(std::string_view cmd, GuiState& outState) noexcept {
    if (cmd == "load") {
        outState = GuiState::Load;
        return true;
    }
    if (cmd == "speak") {
        outState = GuiState::Speak;
        return true;
    }
    if (cmd == "listen") {
        outState = GuiState::Listen;
        return true;
    }
    if (cmd == "error") {
        outState = GuiState::Error;
        return true;
    }
    if (cmd == "standby") {
        outState = GuiState::Standby;
        return true;
    }
    return false;
}
