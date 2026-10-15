#pragma once
#include <stdint.h>

enum class GuiState : uint8_t {
    Standby,
    Load,
    Listen,
    Speak,
    Error
};
