#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

class DisplayTFT {
public:
    DisplayTFT();
    void iniciar();
    void dibujarUI(int8_t estado, int8_t i = 0);
    //0 inicio, 1 lista de gcodes, 2 preview,
    //3 calibrar A, 4 calibrar B, 5 calibrar C
    void dibujarPreview();
    const uint8_t alto = 160;
    const uint8_t ancho = 128;
private:
    void boton(bool selecc, uint8_t i);
    Adafruit_ST7735 tft;
};