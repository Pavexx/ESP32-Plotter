#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

class DisplayTFT {
public:
    DisplayTFT();
    void iniciar();
    void dibujarUI();
    void dibujarPreview();
    const uint8_t alto = 160;
    const uint8_t ancho = 128;
private:
    void boton(String texto, uint8_t x, uint8_t y);
    const uint8_t ancho_boton = 20;
    const uint8_t largo_boton = 30;
    Adafruit_ST7735 tft;
};