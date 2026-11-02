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
    _estado = 1;
}

void App::ciclo() {
    sleep(1);
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
    steppers.cero();
    Serial.println("Cereado finalizado");
    // Serial.println("Iniciando calibracion esquina sup-der");
    // tft.dibujarUI(4);
    // while (!jstk.boton1Presionado()) {
    //     int16_t velL, velR;
    //     jstk.valoresXY(velL, velR);
    //     controlManual(stepperL, velL);
    //     controlManual(stepperR, velR);
    // }
    // _PasosInicio[0] = stepperL->getPositionAfterCommandsCompleted();
    // _PasosInicio[1] = stepperR->getPositionAfterCommandsCompleted();
    Serial.println("calibracion terminada, activando planner");
}