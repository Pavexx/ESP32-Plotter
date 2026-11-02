#pragma once

#include <Arduino.h>

class App {
public:
    void iniciar();
    void ciclo();
    void calibrar();
private:
    int8_t _estado = 0;
};