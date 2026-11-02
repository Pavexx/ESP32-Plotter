#include "Steppers.h"
#include "ConfigMovimiento.h"
#include "Cinematica.h"
#include "Pines.h"

FastAccelStepperEngine engine = FastAccelStepperEngine();
FasNAxis<2, 32> planner(FasNAxisConfig{}, engine);

Steppers::Steppers() {
    stepperL = engine.stepperConnectToPin(PIN_LEFT_STEP);
    stepperR = engine.stepperConnectToPin(PIN_RIGHT_STEP);
    if (!stepperL || !stepperR) {
        while (true) {
            Serial.println("error declarando steppers");
        }
    }
}

void Steppers::iniciar() {
    engine.init();
    stepperL->setDirectionPin(PIN_LEFT_DIR);
    stepperR->setDirectionPin(PIN_RIGHT_DIR);
    stepperL->setSpeedInHz(800);
    stepperL->setAcceleration(1000);
    stepperR->setSpeedInHz(800);
    stepperR->setAcceleration(1000);
    // inicia el planner con dos ejes y 32 lugares
    planner.addAxis(0, stepperL);
    planner.addAxis(1, stepperR);
    planner.setLimitsFromSteppers();
    Serial.println("Steppers y Planner iniciados");
}

void Steppers::controlManual(FastAccelStepper *stepper, int16_t valorJoystick) {
    int velocidad = abs(valorJoystick) * 5 / 127;
    stepper->setSpeedInHz(velocidad);
    if (valorJoystick > 0) {
    stepper->runForward();   // Positive = forward
    } else if (valorJoystick < 0) {
    stepper->runBackward();   // Negative = backward
    } else {
    stepper->forceStop();     // Zero = stop
    }
}

void Steppers::cero() {
    _pasosInicio[0] = stepperL->getPositionAfterCommandsCompleted();
    _pasosInicio[1] = stepperR->getPositionAfterCommandsCompleted();
    planner.setCurrentPosition(_pasosInicio);
}

//https://github.com/gin66/FastAccelStepper/blob/master/examples/NaxesAFAP/NaxesAFAP.ino
bool Steppers::sumarPlaner(int32_t* objetivo, uint16_t& i, uint16_t total) {
    if (i < total) {
        if (planner.addWaypoint(objetivo)) {
            i++;    //si el planner acepta nuevo punto pasa al siguiente
            if (i >= total) {
            planner.endPath();
            }
        }
    }
    planner.pump();
    return (!planner.isBusy() && i >= total);   //true si el planner terminó
}