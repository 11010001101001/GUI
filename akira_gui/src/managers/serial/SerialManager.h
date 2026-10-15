#pragma once
#include <Arduino.h>
#include <stddef.h>
#include <stdint.h>
#include <string_view>
#include "../../core/GuiState.h"

class SerialManager {
public:
    static constexpr uint32_t kBaudRate = 115200;

    void setup() noexcept;
    bool pollState(GuiState& outState) noexcept;

private:
    static constexpr size_t kBufferSize = 32;
    char buffer_[kBufferSize]{};
    size_t length_{0};

    static bool parseCommand(std::string_view cmd, GuiState& outState) noexcept;
};
