#include <Arduino.h>
#include "ServidorWeb.h"
#include "DisplayTFT.h"
#include "Joystick.h"
#include "Steppers.h"

ServidorWeb web;
DisplayTFT tft;
Joystick jstk;
Steppers steppers;

void setup() {
    Serial.begin(115200);
    web.iniciar();
    //tft.iniciar();
    //tft.dibujarPreview();
    jstk.iniciar();
    Serial.println("SETUP TERMINADO");
}

void loop() {
    //tft.dibujarUI();
    web.actualizar();
    jstk.monitorear();
    usleep(500000);
}