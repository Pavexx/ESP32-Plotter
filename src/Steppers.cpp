#include "Steppers.h"
#include "ConfigMovimiento.h"
#include "Cinematica.h"
#include "Pines.h"

Steppers::Steppers() 
    : stepperL(AccelStepper::DRIVER, PIN_LEFT_STEP, PIN_LEFT_DIR),
    stepperR(AccelStepper::DRIVER, PIN_RIGHT_STEP, PIN_RIGHT_DIR) {
}

void Steppers::iniciar() {
    stepperL.setMaxSpeed(100);
    stepperR.setMaxSpeed(100);
    stepperL.setAcceleration(100.0);
    stepperR.setAcceleration(100.0);
}

void Steppers::controlManual(int8_t x, int8_t y, uint8_t dirx, int8_t diry) {
    long positions[2]; // Array of desired stepper positions
    positions[0] = dirx * 1000000;
    positions[1] = diry * 1000000;
    stepperL.setAcceleration(x);
    stepperR.setAcceleration(y);
}