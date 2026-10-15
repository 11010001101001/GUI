#pragma once
#include <Adafruit_NeoPixel.h>
#include <stdint.h>

class LightManager {
public:
    struct Color {
        uint8_t r{0};
        uint8_t g{0};
        uint8_t b{0};

        constexpr bool operator==(const Color& other) const noexcept {
            return r == other.r && g == other.g && b == other.b;
        }

        constexpr bool operator!=(const Color& other) const noexcept {
            return !(*this == other);
        }
    };

    static constexpr Color kBlack{0, 0, 0};
    static constexpr Color kMagenta{255, 0, 255};
    static constexpr Color kCyan{0, 255, 255};
    static constexpr Color kRed{255, 0, 0};

    LightManager() noexcept;

    void setup() noexcept;
    void update() noexcept;

    void startLoading() noexcept;
    void turnOnCyan() noexcept;
    void turnOnMagenta() noexcept;
    void turnOnRed() noexcept;
    void turnOnBlack() noexcept;

private:
    static constexpr uint16_t kPixelCount = 1;
    static constexpr uint8_t kLedPin = 5;
    static constexpr uint32_t kDefaultStepUs = 500;
    static constexpr uint32_t kLoadingStepUs = 5000;

    Adafruit_NeoPixel pixels_;
    Color current_{kBlack};
    Color target_{kBlack};
    uint32_t lastStepUs_{0};
    uint32_t stepIntervalUs_{kDefaultStepUs};
    bool isLoading_{false};
    bool loadingToCyan_{false};

    void setTarget(Color color, uint32_t stepIntervalUs = kDefaultStepUs) noexcept;
    void applyCurrentColor() noexcept;
    static uint8_t stepChannel(uint8_t current, uint8_t target) noexcept;
};
