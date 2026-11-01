#include "Steppers.h"
#include "ConfigMovimiento.h"
#include "Cinematica.h"
#include "Pines.h"

FastAccelStepperEngine engine = FastAccelStepperEngine();

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
    FasNAxis<2, 32> planner(FasNAxisConfig{}, engine);
    planner.addAxis(0, stepperL);
    planner.addAxis(1, stepperR);
    planner.setLimitsFromSteppers();
    Serial.println("Steppers y Planner iniciados");
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
    Serial.println("calibracion terminada");
}