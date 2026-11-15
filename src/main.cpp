#include <Arduino.h>
#include "ServidorWeb.h"
#include "DisplayTFT.h"
#include "Joystick.h"
#include "Steppers.h"
#include "Servomotor.h"
#include "TarjetaSD.h"

ServidorWeb web;
DisplayTFT tft;
Joystick jstk;
Steppers steppers;
Servomotor servo;
TarjetaSD sd;

void setup() {
    Serial.begin(115200);
    sd.iniciar();
    //web.iniciar();
    tft.iniciar();
    //tft.dibujarPreview();
    //jstk.iniciar();
    //servo.iniciar();
    //steppers.iniciar();
    Serial.println("SETUP TERMINADO");
    sd.listarGcodes(Serial);
}

void loop() {

}