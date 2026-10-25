#pragma once

#include <AccelStepper.h>
#include <MultiStepper.h>

class Steppers {
public:
    Steppers();
    void iniciar();
    void controlManual(int8_t x, int8_t y);
    //bool controlManual(const GcodeCommand& command);

private: 
    AccelStepper stepperL;
    AccelStepper stepperR;
    MultiStepper multiStepper;
};