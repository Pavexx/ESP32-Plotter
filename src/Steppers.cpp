#include "Steppers.h"
#include "ConfigMovimiento.h"
#include "Cinematica.h"


Steppers::Steppers() 
    : stepperL(AccelStepper::DRIVER, PIN_LEFT_STEP, PIN_LEFT_DIR),
    stepperR(AccelStepper::DRIVER, PIN_RIGHT_STEP, PIN_RIGHT_DIR) {
}

void Steppers::iniciar() {
    stepperL.setMaxSpeed(100);
    stepperR.setMaxSpeed(100);
    multiStepper.addStepper(stepperL); 
    multiStepper.addStepper(stepperR);
}

void Steppers::controlManual(int8_t x, int8_t y) {
    
}