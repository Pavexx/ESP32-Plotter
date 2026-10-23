#pragma once

#include <Arduino.h>

class Joystick {
public:
    void iniciar();
    bool direccion(int8_t& lr, int8_t& ud);
    bool valoresXY(int16_t& x, int16_t& y);
    bool botonPresionado();
    void monitorear();
private:
    bool _btnLastState;
    inline int8_t mapearADC(int16_t value, int16_t v1, int16_t v2);
    static const int ValorCentralX = 1860;
    static const int ValorCentralY = 1875;
    static const int Tolerancia = 20;
};