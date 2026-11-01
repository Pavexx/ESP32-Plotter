#include "app.h"
#include "ServidorWeb.h"
#include "DisplayTFT.h"
#include "Joystick.h"
#include "Steppers.h"
#include "Servomotor.h"

ServidorWeb web;
DisplayTFT tft;
Joystick jstk;
Steppers steppers;
Servomotor servo;

void App::iniciar() {
    Serial.begin(115200);
    web.iniciar();
    tft.iniciar();
    jstk.iniciar();
    servo.iniciar();
    steppers.iniciar();
    Serial.println("SETUP TERMINADO");
}
void App::calibrar() {
    jstk.boton1Presionado();
    Serial.println("Iniciando cereado");
    tft.dibujarUI(3);
    while (!jstk.boton1Presionado()) {
        int16_t velL, velR;
        jstk.valoresXY(velL, velR);
        steppers.controlManual(steppers.stepperL, velL);
        steppers.controlManual(steppers.stepperR, velR);
    }
    _Pasos0L = steppers.stepperL->getPositionAfterCommandsCompleted();
    _Pasos0R = steppers.stepperR->getPositionAfterCommandsCompleted();

    Serial.println("Cereado finalizado");
    Serial.println("Iniciando calibracion esquina sup-der");
    tft.dibujarUI(4);
    while (!jstk.boton1Presionado()) {
        int16_t velL, velR;
        jstk.valoresXY(velL, velR);
        steppers.controlManual(steppers.stepperL, velL);
        steppers.controlManual(steppers.stepperR, velR);
    }
    Serial.println("calibracion terminada");
}

void App::ciclo() {
    sleep(1);
}