#pragma once
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <stdint.h>

class DisplayManager {
public:
    enum class ImageCategory : uint8_t {
        None,
        Error,
        Listen,
        Speak
    };

    DisplayManager() noexcept;

    void setup() noexcept;
    void update() noexcept;
    void showImage(ImageCategory category) noexcept;
    void turnOff() noexcept;

private:
    enum class OffPhase : uint8_t {
        Idle,
        Shrinking,
        HoldLine,
        HoldDot
    };

    static constexpr int16_t kScreenWidth = 128;
    static constexpr int16_t kScreenHeight = 64;
    static constexpr int8_t kOledReset = -1;
    static constexpr uint8_t kI2cAddress = 0x3C;

    static constexpr uint32_t kShrinkStepMs = 5;
    static constexpr uint32_t kHoldLineMs = 750;
    static constexpr uint32_t kHoldDotMs = 1500;

    Adafruit_SSD1306 display_;
    ImageCategory currentCategory_{ImageCategory::None};
    OffPhase offPhase_{OffPhase::Idle};
    uint32_t phaseTimestampMs_{0};
    int16_t shrinkHeight_{kScreenHeight};
    bool isOn_{false};

    void stepShrinkAnimation(uint32_t nowMs) noexcept;
    void renderBitmap(const uint8_t* bitmap) noexcept;
};
