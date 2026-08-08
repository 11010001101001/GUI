#include "DisplayManager.h"
#include <Wire.h>

extern "C"
{
    uint8_t temprature_sens_read();
}

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void DisplayManager::setup()
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
}

void DisplayManager::displayImage(DisplayManager::ImagesCategory category)
{
    if (currentCategory != category)
    {
        isOn = true;
        display.invertDisplay(true);
        display.clearDisplay();
        display.setCursor(0, 0);

        switch (category)
        {
        case ImagesCategory::Error:
        {
            int i = random(0, errorImagesCount);
            display.drawXBitmap(0, 0, errorImages[i], 128, 64, SSD1306_WHITE);
            break;
        }

        case ImagesCategory::Listen:
        {
            int i = random(0, listenImagesCount);
            display.drawXBitmap(0, 0, listenImages[i], 128, 64, SSD1306_WHITE);
            break;
        }

        case ImagesCategory::Speak:
        {
            int i = random(0, speakImagesCount);
            display.drawXBitmap(0, 0, speakImages[i], 128, 64, SSD1306_WHITE);
            break;
        }
        }

        display.display();
    }
}

void DisplayManager::displayText(String text)
{
    isOn = true;
    display.invertDisplay(false);
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print(text);
    display.display();
}

void DisplayManager::displayOff()
{
    if (isOn)
    {
        isOn = false;
        display.invertDisplay(false);
        display.setTextSize(3);

        for (int h = display.height(); h > 3; h -= 6)
        {
            display.clearDisplay();
            display.fillRect(0, (display.height() - h) / 2, display.width(), h, SSD1306_WHITE);
            display.display();
            delay(5);
        }
        delay(750);

        display.clearDisplay();
        display.setCursor(57, 15);
        display.print(".");
        display.display();
        delay(1500);

        display.clearDisplay();
        display.display();
    }
}

void DisplayManager::showChipTemp()
{
    uint8_t rawTemp = temprature_sens_read();
    float tempCelsius = (rawTemp - 32) / 1.8;
    float rounded = round(tempCelsius * 100) / 100;

    if (rounded != garbageTemp)
    {
        currentTemp = rounded;
    }

    String chipTemp = "Chip temp: " + String(currentTemp, 2);

    display.setTextSize(1);
    display.setCursor(0, 57);
    display.print(chipTemp);

    int x = display.getCursorX();
    int y = display.getCursorY();
    display.drawCircle(x + 2, y + 1, 1, SSD1306_WHITE);
    display.print(" C");
    display.display();
}
