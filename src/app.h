#pragma once

#include <Arduino.h>

class App {
public:
    void iniciar();
    void ciclo();
    void calibrar();
    void dibujarGcode(const char* direccion);
    void ejecutarComando(char* comando);
private:
    int8_t _estado = 0;
    uint16_t i = 0;
};