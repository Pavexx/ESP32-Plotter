#include "Steppers.h"
#include "ConfigMovimiento.h"
#include "Cinematica.h"
#include "Pines.h"

FastAccelStepperEngine engine = FastAccelStepperEngine();

Steppers::Steppers() {
    engine.init();

    stepperL = engine.stepperConnectToPin(PIN_LEFT_STEP);
    stepperR = engine.stepperConnectToPin(PIN_RIGHT_STEP);
    if (!stepperL || !stepperR) {
        while (true) {
            Serial.println("Cannot initialize steppers");
        }
    }
}

void Steppers::iniciar() {
    stepperL->setDirectionPin(PIN_LEFT_DIR);
    stepperR->setDirectionPin(PIN_RIGHT_DIR);

    stepperL->setSpeedInHz(800);
    stepperL->setAcceleration(1000);

    stepperR->setSpeedInHz(800);
    stepperR->setAcceleration(1000);
}

void Steppers::controlManual(FastAccelStepper *stepper, int16_t valorJoystick) {
    int velocidad = abs(valorJoystick) * 50 / 127;
    stepper->setSpeedInHz(velocidad);

    if (valorJoystick > 0) {
    stepper->runForward();   // Positive = forward
    } else if (valorJoystick < 0) {
    stepper->runBackward();   // Negative = backward
    } else {
    stepper->forceStop();     // Zero = stop
    }
}