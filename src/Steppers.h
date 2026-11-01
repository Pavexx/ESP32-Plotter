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
    bool sumarPlaner(int32_t* objetivo, uint16_t& i, uint16_t total);
private:
    FastAccelStepper *stepperL;
    FastAccelStepper *stepperR;
    int32_t _PasosInicio[2];
    int32_t _Pasos0L, _Pasos0R;
};