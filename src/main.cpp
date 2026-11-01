#include <Arduino.h>
#include <app.h>

App plotter;

void setup() {
    plotter.iniciar();
}

void loop() {
    plotter.ciclo();
}