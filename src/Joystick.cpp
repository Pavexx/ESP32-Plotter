#include "Joystick.h"
#include "Pines.h"

void Joystick::iniciar() {
    pinMode(PIN_SW, INPUT_PULLUP);
    pinMode(PIN_BTN1, INPUT_PULLUP);
    pinMode(PIN_BTN2, INPUT_PULLUP);
    analogSetAttenuation(ADC_11db);
    _btnLastState = false;
}

bool Joystick::valoresXY(int16_t& x, int16_t& y) {
    int16_t jx = analogRead(PIN_X);
    int16_t jy = analogRead(PIN_Y);
    
    x = mapearADC(jx, ValorCentralX - Tolerancia, ValorCentralX + Tolerancia);
    y = mapearADC(jy, ValorCentralY - Tolerancia, ValorCentralY + Tolerancia);
    return !(x == 0 && y == 0);
}

inline int8_t Joystick::mapearADC(int16_t value, int16_t v1, int16_t v2) {
    if (value < v1) {
        return -127 + (value * 127) / v1;
    } else if (value < v2) {
        return 0;
    } else {
        return (value - v2) * 127 / (4095 - v2);
    }
}

bool Joystick::direccion(int8_t& lr, int8_t& ud) {
    int16_t jx = analogRead(PIN_X);
    int16_t jy = analogRead(PIN_Y);
    
    lr = jx == 0 ? -1 : (jx == 4095 ? 1 : 0);
    ud = jy  == 0 ? -1 : (jy == 4095 ? 1 : 0);
    return !(jx == 0 && jy == 0);
}

bool Joystick::switchPresionado() {
    bool swState = !digitalRead(PIN_SW);
    return swState;
}

bool Joystick::boton1Presionado() {
    bool btnState = !digitalRead(PIN_BTN1);
    bool pressed = btnState && !_btnLastState;
    _btnLastState = btnState;
    return pressed;
}
bool Joystick::boton2Presionado() {
    bool btnState = !digitalRead(PIN_BTN2);
    bool pressed = btnState && !_btnLastState;
    _btnLastState = btnState;
    return pressed;
}

void Joystick::monitorear() {
    int8_t UD, LR;
    int16_t X, Y;
    int16_t Xr = analogRead(PIN_X);
    int16_t Yr = analogRead(PIN_Y);
    direccion(LR, UD);
    valoresXY(X, Y);
    String direcc = String(UD)+", "+String(LR);
    Serial.println("Joystick | X: " + String(X) + "  Y: " + String(Y) + "  REAL | X: " + String(Xr) + "  Y: " + String(Yr) + " | Dir: " + String(direcc) + " | Switch: " + String(switchPresionado())+ " | Boton: " + String(boton1Presionado()));
}