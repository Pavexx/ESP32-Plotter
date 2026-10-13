#include <Arduino.h>
//#include "ServidorWeb.h"
#include "DisplayTFT.h"

//ServidorWeb web;
DisplayTFT tft;

void setup() {
    Serial.begin(115200);
    // web.iniciarAP();
    // web.iniciarSV();
    tft.iniciar();
    tft.dibujarPreview();
    Serial.println("SETUP TERMINADO");
}

void loop() {
    //web.actualizar();
}