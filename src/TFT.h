#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

class TFT {
public:
    TFT();
    void iniciar();
private:
    Adafruit_ST7735 tft;
};