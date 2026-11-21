#pragma once

#include <Arduino.h>

class App {
public:
    void iniciar();
    void ciclo();
    void calibrar();
    void dibujarPrueba();
    void ejecutarComando(char* comando);
private:
    int8_t _estado = 0;
};