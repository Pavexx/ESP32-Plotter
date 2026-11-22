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
    stepperL->setSpeedInHz(VelocidadMaximaPasoPSeg);
    stepperL->setAcceleration(AceleracionMaxima);
    stepperR->setSpeedInHz(VelocidadMaximaPasoPSeg);
    stepperR->setAcceleration(AceleracionMaxima);

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
    pasosCero[0] = stepperL->getPositionAfterCommandsCompleted();
    pasosCero[1] = stepperR->getPositionAfterCommandsCompleted();
    planner.setCurrentPosition(pasosCero);
    Serial.println("cero = l:"+String(pasosCero[0])+" r:"+String(pasosCero[1]));
}

//https://github.com/gin66/FastAccelStepper/blob/master/examples/NaxesAFAP/NaxesAFAP.ino
bool Steppers::sumarPlaner(int32_t* objetivo, uint16_t& in, uint16_t total) {
    if (in < total) {
        if (planner.addWaypoint(objetivo)) {
            Serial.println("yendo a l:"+String(objetivo[0])+" r:"+String(objetivo[1])+" | paso "+String(in));
            in++;    //si el planner acepta nuevo punto pasa al siguiente
            if (in >= total) {
            planner.endPath();
            }
        }
    }
    planner.pump();
    return (!planner.isBusy() && in >= total);   //true si el planner terminó
}

bool Steppers::sumarPlaner(int32_t* objetivo) {
    return (planner.addWaypoint(objetivo));
}

void Steppers::pumpear() {
    planner.pump();
}

void Steppers::terminarTrazo() {
    if (!planner.isBusy()) return;

    planner.endPath();
    while (planner.isBusy()) {
        planner.pump();
    }  
}


void Steppers::dibujarPrueba() {
    int32_t xy[2] = {0, 0};
    int32_t lr[2] = {0};
    XYaPasos(xy[0], xy[1], lr[0], lr[1]);
    uint16_t i = 0;
    while (!sumarPlaner(lr, i, 6)){
            xy[0] = (i==1||i==2) ? -100 : 100;
            xy[1] = (i==1||i==3) ? 200 : 0;
            if (i == 5) xy[0] = 0;
            XYaPasos(xy[0], xy[1], lr[0], lr[1]);
    }
}