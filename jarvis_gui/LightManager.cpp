#include "LightManager.h"
#include <stdint.h>
#include <functional>

LightManager::LightManager()
    : pixels(1, 5, NEO_GRB + NEO_KHZ800) {}

void LightManager::setColorWithAnimation(Color color)
{
    bool isAnimating = currentColor != color;

    while (isAnimating)
    {
        if (currentColor.r < color.r)
        {
            currentColor.r += 1;
        }
        else if (currentColor.r > color.r)
        {
            currentColor.r -= 1;
        }

        if (currentColor.g < color.g)
        {
            currentColor.g += 1;
        }
        else if (currentColor.g > color.g)
        {
            currentColor.g -= 1;
        }

        if (currentColor.b < color.b)
        {
            currentColor.b += 1;
        }
        else if (currentColor.b > color.b)
        {
            currentColor.b -= 1;
        }

        pixels.setPixelColor(0, pixels.Color(currentColor.r, currentColor.g, currentColor.b));
        pixels.show();

        delay(1);

        isAnimating = currentColor != color;
    };
}

void LightManager::blink()
{
    pixels.setPixelColor(0, pixels.Color(cyan.r, cyan.g, cyan.b));
    pixels.show();
    delay(100);
    pixels.setPixelColor(0, pixels.Color(black.r, black.g, black.b));
    pixels.show();
    delay(1500);
}

void LightManager::turnOnCyan()
{
    setColorWithAnimation(cyan);
}

void LightManager::turnOnGreen()
{
    setColorWithAnimation(green);
}

void LightManager::turnOnMagenta()
{
    setColorWithAnimation(magenta);
}

void LightManager::turnOnRed()
{
    setColorWithAnimation(red);
}

void LightManager::turnOnBlack()
{
    setColorWithAnimation(black);
}

void LightManager::turnOnOrange()
{
    setColorWithAnimation(orange);
}

void LightManager::setup()
{
    pixels.begin();
}