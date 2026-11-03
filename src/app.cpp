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
    calibrar();
}

void App::ciclo() {
    sleep(1);
}

void App::calibrar() {
    Serial.println("Iniciando cereado");
    tft.dibujarUI(3);
    while (!jstk.boton1Presionado()) {
        jstk.monitorear();
        int16_t velL, velR;
        jstk.valoresXY(velL, velR);
        steppers.controlManual(steppers.stepperL, velL);
        steppers.controlManual(steppers.stepperR, velR);
        usleep(100000);
    }
    steppers.cero();
    Serial.println("calibracion terminada, activando planner");
}