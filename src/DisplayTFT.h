#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

class TFT {
public:
    TFT();
    void iniciar();
    void dibujarPreview();
    const uint8_t alto = 160;
    const uint8_t ancho = 128;
private:
    Adafruit_ST7735 tft;
};