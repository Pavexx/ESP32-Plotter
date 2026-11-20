#pragma once

#include <Arduino.h>
#include <FastAccelStepper.h>
#include <FasNAxis.h>
#include "Joystick.h"
#include "DisplayTFT.h"

class Steppers {
public:
    Steppers(); //aca se inicia una parte
    void iniciar();
    void controlManual(FastAccelStepper *stepper, int16_t valorJoystick);
    void cero();
    bool sumarPlaner(int32_t* objetivo, uint16_t& i, uint16_t total);
    void dibujarPrueba();
    FastAccelStepper *stepperL;
    FastAccelStepper *stepperR;
private:
    uint16_t i = 0;
};