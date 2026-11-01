#pragma once

#include <FastAccelStepper.h>

class Steppers {
public:
    Steppers(); //aca se inicia una parte

    void iniciar();
    void controlManual(int8_t x, int8_t y, uint8_t dirx, int8_t diry);
    //bool controlManual(const GcodeCommand& command);

private: 
    FastAccelStepper *stepperL;
    FastAccelStepper *stepperR;
};