#include "app.h"
#include "ServidorWeb.h"
#include "DisplayTFT.h"
#include "Joystick.h"
#include "Steppers.h"
#include "Servomotor.h"
#include "TarjetaSD.h"
#include "GCodes.h"
#include "Cinematica.h"

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
    sd.iniciar();
    Serial.println("SETUP TERMINADO");
    _estado = 1;
    steppers.cero();
    //calibrar();
    //sd.listarGcodes(Serial);
    //sd.dryRun("/squiggleCam.gcode");
    dibujarGcode("/Plotter.gcode");
}

void App::ciclo() {

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

void App::dibujarGcode(const char* direccion) {
    if (!sd.abrir(direccion)) {
        return;
    }
    Serial.print("Empezando a dibujar: ");
    Serial.println(direccion);

    char linea[128];
    int i = 0;
    while (sd.leerSiguienteLinea(linea, sizeof(linea))) {
        Serial.print(i++);
        Serial.print(": ");
        Serial.println(linea);
        ejecutarComando(linea);

    }
    
}

void App::ejecutarComando(char* linea) {
    float xy[2] = {0};
    int32_t lr[2] = {0};
    bool ok = false;
    int16_t segmentos;

    uint8_t cmd = gcode.obtenerComando(linea);

    if (cmd>2) {    //si no es un comando de movimiento espera a que termine
        steppers.terminarTrazo();
    }
    
    switch (cmd) {
        case CMD_G0_G1:
            gcode.obtenerXY(linea, xy[0], xy[1]);

            Serial.print("Yendo a X:");
            Serial.print(xy[0]);
            Serial.print(" | Y:");
            Serial.println(xy[1]);

            segmentos = CantSegmentos(xy[0], xy[1]);

            for (int a = 1; a <= segmentos; a++) {

                PasosIntermedio(a, lr[0], lr[1]);
                while (ok) {
                    ok = steppers.sumarPlaner(lr);
                    steppers.pumpear();
                }
                steppers.pumpear();
            }
        break;

        case CMD_G28:
            Serial.println("Yendo a home");
            while (ok) {
                ok = steppers.sumarPlaner(lr);
                steppers.pumpear();
            }
        break;

        case CMD_M0:
            Serial.println("Esperando a presionar B1");
            jstk.boton1Presionado();
            while (!jstk.boton1Presionado()) {
                Serial.print(".");
                sleep(1);
            }
        break;

        case CMD_Subir:
            Serial.println("Subiendo Lapiz");
            servo.subirLapiz();
        break;

        case CMD_Bajar:
            Serial.println("Bajando Lapiz");
            servo.bajarLapiz();
        break;
    }
}