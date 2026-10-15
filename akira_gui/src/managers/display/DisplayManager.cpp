#include "DisplayManager.h"
#include <Wire.h>
#include "../../images/error_1.h"
#include "../../images/listen.h"
#include "../../images/listen_1.h"
#include "../../images/listen_2.h"
#include "../../images/speak.h"
#include "../../images/speak_1.h"
#include "../../images/speak_2.h"

namespace {
constexpr const uint8_t* kErrorImages[] = {error_1_bits};
constexpr const uint8_t* kListenImages[] = {listen_bits, listen_1_bits, listen_2_bits};
constexpr const uint8_t* kSpeakImages[] = {speak_bits, speak_1_bits, speak_2_bits};

constexpr size_t kErrorCount = sizeof(kErrorImages) / sizeof(kErrorImages[0]);
constexpr size_t kListenCount = sizeof(kListenImages) / sizeof(kListenImages[0]);
constexpr size_t kSpeakCount = sizeof(kSpeakImages) / sizeof(kSpeakImages[0]);
} // namespace

DisplayManager::DisplayManager() noexcept
    : display_(kScreenWidth, kScreenHeight, &Wire, kOledReset) {}

void DisplayManager::setup() noexcept {
    display_.begin(SSD1306_SWITCHCAPVCC, kI2cAddress);
    display_.clearDisplay();
    display_.setTextSize(1);
    display_.setTextColor(SSD1306_WHITE);
    display_.setCursor(0, 0);
    display_.display();
}

void DisplayManager::showImage(ImageCategory category) noexcept {
    offPhase_ = OffPhase::Idle;
    if (currentCategory_ == category && isOn_) {
        return;
    }

    currentCategory_ = category;
    isOn_ = true;

    switch (category) {
    case ImageCategory::Error:
        renderBitmap(kErrorImages[random(0, kErrorCount)]);
        break;
    case ImageCategory::Listen:
        renderBitmap(kListenImages[random(0, kListenCount)]);
        break;
    case ImageCategory::Speak:
        renderBitmap(kSpeakImages[random(0, kSpeakCount)]);
        break;
    case ImageCategory::None:
        break;
    }
}

void DisplayManager::turnOff() noexcept {
    if (!isOn_) {
        return;
    }
    isOn_ = false;
    currentCategory_ = ImageCategory::None;
    offPhase_ = OffPhase::Shrinking;
    shrinkHeight_ = kScreenHeight;
    phaseTimestampMs_ = millis();

    display_.invertDisplay(false);
    display_.setTextSize(3);
}

void DisplayManager::update() noexcept {
    if (offPhase_ == OffPhase::Idle) {
        return;
    }

    const uint32_t nowMs = millis();

    switch (offPhase_) {
    case OffPhase::Shrinking:
        stepShrinkAnimation(nowMs);
        break;
    case OffPhase::HoldLine:
        if (nowMs - phaseTimestampMs_ >= kHoldLineMs) {
            display_.clearDisplay();
            display_.setCursor(57, 15);
            display_.print(".");
            display_.display();
            offPhase_ = OffPhase::HoldDot;
            phaseTimestampMs_ = nowMs;
        }
        break;
    case OffPhase::HoldDot:
        if (nowMs - phaseTimestampMs_ >= kHoldDotMs) {
            display_.clearDisplay();
            display_.display();
            offPhase_ = OffPhase::Idle;
        }
        break;
    case OffPhase::Idle:
        break;
    }
}

void DisplayManager::stepShrinkAnimation(uint32_t nowMs) noexcept {
    if (nowMs - phaseTimestampMs_ < kShrinkStepMs) {
        return;
    }
    phaseTimestampMs_ = nowMs;

    display_.clearDisplay();
    display_.fillRect(0, (kScreenHeight - shrinkHeight_) / 2, kScreenWidth, shrinkHeight_, SSD1306_WHITE);
    display_.display();

    shrinkHeight_ -= 6;
    if (shrinkHeight_ <= 3) {
        offPhase_ = OffPhase::HoldLine;
    }
}

void DisplayManager::renderBitmap(const uint8_t* bitmap) noexcept {
    display_.invertDisplay(true);
    display_.clearDisplay();
    display_.setCursor(0, 0);
    display_.drawXBitmap(0, 0, bitmap, kScreenWidth, kScreenHeight, SSD1306_WHITE);
    display_.display();
}
