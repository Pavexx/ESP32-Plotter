#include <Arduino.h>
#include "ServidorWeb.h"

ServidorWeb web;

void setup() {
    Serial.begin(115200);
    web.iniciar();
    Serial.println("Funcionó");
}

void loop() {
    web.actualizar();
}