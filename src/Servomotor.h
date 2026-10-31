#pragma once

#include <ESP32Servo.h>

class Servomotor {
public:
    void iniciar();
    void probar();
    void bajarLapiz();
    void subirLapiz();

private:
    Servo servo;
    //int Posicion;
    
    bool Arriba90 = true;   
    //true = 90° arriba y 0° abajo
};