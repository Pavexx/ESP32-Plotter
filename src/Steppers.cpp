#include "Steppers.h"
#include "ConfigMovimiento.h"
#include "Cinematica.h"
#include "Pines.h"

FastAccelStepperEngine engine = FastAccelStepperEngine();
FastAccelStepper* NaxesAFAP_s[2] = {NULL};
FasNAxis<2, 32> planner(FasNAxisConfig{}, engine);

Steppers::Steppers() : stepperL(nullptr), stepperR(nullptr) {}

void Steppers::iniciar() {
    engine.init();

    stepperL = engine.stepperConnectToPin(PIN_LEFT_STEP);
    stepperR = engine.stepperConnectToPin(PIN_RIGHT_STEP);
    if (!stepperL || !stepperR) {
        Serial.println("Error connecting steppers");
        return;
    }
    stepperL->setDirectionPin(PIN_LEFT_DIR);
    stepperR->setDirectionPin(PIN_RIGHT_DIR);
    stepperL->setSpeedInHz(800);
    stepperL->setAcceleration(1200);
    stepperR->setSpeedInHz(800);
    stepperR->setAcceleration(1200);

    planner.addAxis(0, stepperL);
    planner.addAxis(1, stepperR);
    planner.setLimitsFromSteppers();

    Serial.println("Steppers and planner initialized");
}

void Steppers::controlManual(FastAccelStepper *stepper, int16_t valorJoystick) {
    int velocidad = abs(map(valorJoystick, -254, 254, -800, 800));
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
    int32_t origen[2] = {0, 0};
    planner.setCurrentPosition(origen);
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

void Steppers::dibujarPrueba() {
    int32_t xy[2] = {0};
    switch (a) {
    case 1:
        xy[0] = 2000;
        break;
    case 2:
        xy[1] = 2000;
        xy[0] = 2000;
        break;
    case 3:
        xy[1] = 2000;
        break;
    }
    bool ok = planner.addWaypoint(xy);
    planner.pump();
    //Serial.println("yendo a x:"+String(xy[0])+" y:"+String(xy[1])+" | paso "+String(a));
    if (ok) {
        a = (a + 1) % 4;
    }
}