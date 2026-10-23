#pragma once

#include <Arduino.h>

class Joystick {
public:
    void iniciar();
    bool direccion(bool& lr, bool& ud);
    bool valoresXY(int& x, int& y);
    bool botonPresionado();
    void monitorear();
private:
    bool _btnLastState;
    inline int8_t mapearADC(int value, int v1, int v2);
    static const int ValorCentralX = 1860;
    static const int ValorCentralY = 1875;
    static const int Tolerancia = 20;
};