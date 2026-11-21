#include "app.h"
#include "ServidorWeb.h"
#include "DisplayTFT.h"
#include "Joystick.h"
#include "Steppers.h"
#include "Servomotor.h"
#include "TarjetaSD.h"
#include "GCodes.h"

ServidorWeb web;
DisplayTFT tft;
Joystick jstk;
Steppers steppers;
Servomotor servo;
TarjetaSD sd;
GCodes gcode;

void App::iniciar() {
    Serial.begin(115200);
    web.iniciar();
    tft.iniciar();
    jstk.iniciar();
    servo.iniciar();
    steppers.iniciar();
    //sd.iniciar();
    Serial.println("SETUP TERMINADO");
    _estado = 1;
    steppers.cero();
    //calibrar();
    //sd.listarGcodes(Serial);
    //sd.dryRun("/squiggleCam.gcode");
}

void App::ciclo() {
    steppers.dibujarPrueba();
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

void App::ejecutarComando(char* linea) {
    int32_t h[2] = {0}; 
    uint16_t i = 0;
    switch (gcode.obtenerComando(linea)) {
        case CMD_G0_G1:
        /* code */
        break;

        case CMD_G28:
        Serial.println("Yendo a home");
        
        steppers.sumarPlaner(h, i, 1);
        break;

        case CMD_M0:
        /* code */
        break;

        case CMD_Subir:
        Serial.println("Subiendo Lapiz");
        servo.subirLapiz();
        break;

        case CMD_Bajar:
        Serial.println("Bajando Lapiz");
        servo.bajarLapiz();
        break;
    
    default:
        break;
    }
}