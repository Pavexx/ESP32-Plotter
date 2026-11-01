#pragma once

#include <Arduino.h>
#include <FastAccelStepper.h>

class Steppers {
public:
    Steppers(); //aca se inicia una parte
    void iniciar();
    void controlManual(FastAccelStepper *stepper, int16_t valorJoystick);
    FastAccelStepper *stepperL;
    FastAccelStepper *stepperR;
private: 
    
};