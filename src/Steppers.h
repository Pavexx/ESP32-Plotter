#pragma once

#include <AccelStepper.h>

class Steppers {
public:
    Steppers();
    void iniciar();
    void controlManual(int8_t x, int8_t y, uint8_t dirx, int8_t diry);
    //bool controlManual(const GcodeCommand& command);

private: 
    AccelStepper stepperL;
    AccelStepper stepperR;
};