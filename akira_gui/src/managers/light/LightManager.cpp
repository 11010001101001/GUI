#include "LightManager.h"
#include <Arduino.h>

LightManager::LightManager() noexcept
    : pixels_(kPixelCount, kLedPin, NEO_GRB + NEO_KHZ800) {}

void LightManager::setup() noexcept {
    pixels_.begin();
    applyCurrentColor();
}

void LightManager::update() noexcept {
    if (current_ == target_) {
        if (!isLoading_) {
            return;
        }
        loadingToCyan_ = !loadingToCyan_;
        target_ = loadingToCyan_ ? kCyan : kMagenta;
        lastStepUs_ = micros();
    }

    const uint32_t nowUs = micros();
    if (nowUs - lastStepUs_ < stepIntervalUs_) {
        return;
    }
    lastStepUs_ = nowUs;

    current_.r = stepChannel(current_.r, target_.r);
    current_.g = stepChannel(current_.g, target_.g);
    current_.b = stepChannel(current_.b, target_.b);
    applyCurrentColor();
}

void LightManager::startLoading() noexcept {
    if (isLoading_) {
        return;
    }
    isLoading_ = true;
    loadingToCyan_ = false;
    target_ = kMagenta;
    stepIntervalUs_ = kLoadingStepUs;
    lastStepUs_ = micros();
}

void LightManager::turnOnCyan() noexcept {
    setTarget(kCyan);
}

void LightManager::turnOnMagenta() noexcept {
    setTarget(kMagenta);
}

void LightManager::turnOnRed() noexcept {
    setTarget(kRed);
}

void LightManager::turnOnBlack() noexcept {
    setTarget(kBlack);
}

void LightManager::setTarget(Color color, uint32_t stepIntervalUs) noexcept {
    isLoading_ = false;
    target_ = color;
    stepIntervalUs_ = stepIntervalUs;
    lastStepUs_ = micros();
}

void LightManager::applyCurrentColor() noexcept {
    pixels_.setPixelColor(0, pixels_.Color(current_.r, current_.g, current_.b));
    pixels_.show();
}

uint8_t LightManager::stepChannel(uint8_t current, uint8_t target) noexcept {
    if (current < target) {
        return current + 1;
    }
    if (current > target) {
        return current - 1;
    }
    return current;
}
