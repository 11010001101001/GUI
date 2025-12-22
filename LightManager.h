#pragma once
#include <stdint.h>
#include <Adafruit_NeoPixel.h>

class LightManager
{
public:
    struct Color
    {
        uint32_t r;
        uint32_t g;
        uint32_t b;

        bool operator==(const Color &other) const
        {
            return r == other.r && g == other.g && b == other.b;
        }

        bool operator!=(const Color &other) const
        {
            return !(*this == other);
        }
    };

    LightManager();
    void setup();
    void setColorWithAnimation(Color color);
    void blink();
    void turnOnCyan();
    void turnOnGreen();
    void turnOnMagenta();
    void turnOnRed();
    void turnOnBlack();
    void turnOnOrange();

private:
    Adafruit_NeoPixel pixels;
    Color black = {.r = 0, .g = 0, .b = 0};
    Color magenta = {.r = 255, .g = 0, .b = 255};
    Color cyan = {.r = 0, .g = 255, .b = 255};
    Color red = {.r = 255, .g = 0, .b = 0};
    Color green = {.r = 0, .g = 128, .b = 0};
    Color orange = {.r = 255, .g = 120, .b = 20};
    Color currentColor = {.r = 0, .g = 0, .b = 0};
};