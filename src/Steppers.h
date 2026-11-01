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
    void calibrar(Joystick jstk, DisplayTFT tft);
private:
    FastAccelStepper *stepperL;
    FastAccelStepper *stepperR;
    int32_t _PasosL, _PasosR;
    int32_t _Pasos0L, _Pasos0R;
};