#include <Arduino.h>
#include "ServidorWeb.h"

ServidorWeb web;

void setup() {
    Serial.begin(115200);
    web.iniciarAP();
    web.iniciarSV();
    Serial.println("Funcionó");
}

void loop() {
    web.actualizar();
}