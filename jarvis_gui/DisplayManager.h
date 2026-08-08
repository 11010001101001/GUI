#pragma once
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "error_1.xbm"
#include "listen.xbm"
#include "listen_1.xbm"
#include "listen_2.xbm"
#include "speak.xbm"
#include "speak_1.xbm"
#include "speak_2.xbm"

class DisplayManager
{
public:
    enum ImagesCategory
    {
        Error,
        Listen,
        Speak,
        None
    };

    void setup();
    void displayImage(ImagesCategory category);
    void displayText(String text);
    void displayOff();

private:
    ImagesCategory currentCategory = None;    
    float garbageTemp = 53.33;
    float currentTemp = 0.0;
    bool isOn = false;
    const uint8_t *errorImages[1] = {error_1_bits};
    const uint8_t *listenImages[3] = {listen_bits, listen_1_bits, listen_2_bits};
    const uint8_t *speakImages[3] = {speak_bits, speak_1_bits, speak_2_bits};

    const int errorImagesCount = sizeof(errorImages) / sizeof(errorImages[0]);
    const int listenImagesCount = sizeof(listenImages) / sizeof(listenImages[0]);
    const int speakImagesCount = sizeof(speakImages) / sizeof(speakImages[0]);

    void showChipTemp();
};