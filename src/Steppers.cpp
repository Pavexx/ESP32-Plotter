#include "Steppers.h"
#include "ConfigMovimiento.h"
#include "Cinematica.h"
#include "Pines.h"

// Steppers::Steppers() {
//     stepperL.begin(PIN_LEFT_STEP, PIN_LEFT_DIR);
//     stepperR.begin(PIN_RIGHT_STEP, PIN_RIGHT_DIR);
// }
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
    stepperL->setAcceleration(4000);
    stepperR->setSpeedInHz(800);
    stepperR->setAcceleration(4000);
}

void Steppers::controlManual(int8_t x, int8_t y, uint8_t dirx, int8_t diry) {
    stepperR->setSpeedInHz(800);
    stepperR->setSpeedInHz(800);
}