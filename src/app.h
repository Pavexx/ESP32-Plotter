#pragma once

#include <Arduino.h>

class App {
public:
    void iniciar();
    void ciclo();
    void calibrar();
private:
    int32_t _PasosL, _PasosR;
    int32_t _Pasos0L, _Pasos0R;
};