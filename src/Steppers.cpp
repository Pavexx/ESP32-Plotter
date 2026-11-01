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

void Steppers::calibrar(Joystick jstk, DisplayTFT tft) {
    jstk.boton1Presionado();
    Serial.println("Iniciando cereado");
    tft.dibujarUI(3);
    while (!jstk.boton1Presionado()) {
        int16_t velL, velR;
        jstk.valoresXY(velL, velR);
        controlManual(stepperL, velL);
        controlManual(stepperR, velR);
    }
    _Pasos0L = stepperL->getPositionAfterCommandsCompleted();
    _Pasos0R = stepperR->getPositionAfterCommandsCompleted();
    Serial.println("Cereado finalizado");
    Serial.println("Iniciando calibracion esquina sup-der");
    tft.dibujarUI(4);
    while (!jstk.boton1Presionado()) {
        int16_t velL, velR;
        jstk.valoresXY(velL, velR);
        controlManual(stepperL, velL);
        controlManual(stepperR, velR);
    }
    _PasosInicio[0] = stepperL->getPositionAfterCommandsCompleted();
    _PasosInicio[1] = stepperR->getPositionAfterCommandsCompleted();
    Serial.println("calibracion terminada, activando planner");
    planner.setCurrentPosition(_PasosInicio);
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