#include "Joystick.h"
#include "Pines.h"

void Joystick::iniciar() {
    pinMode(PIN_BTN, INPUT_PULLUP);
    analogSetAttenuation(ADC_11db);
    _btnLastState = false;
}

bool Joystick::valoresXY(int& x, int& y) {
    int jx = analogRead(PIN_X);
    int jy = analogRead(PIN_Y);
    
    x = mapearADC(jx, ValorCentralX - Tolerancia, ValorCentralX + Tolerancia);
    y = mapearADC(jy, ValorCentralY - Tolerancia, ValorCentralY + Tolerancia);
    return !(x == 0 && y == 0);
}

inline int8_t Joystick::mapearADC(int value, int v1, int v2) {
    if (value < v1) {
        return -127 + (value * 127) / v1;
    } else if (value < v2) {
        return 0;
    } else {
        return (value - v2) * 127 / (4095 - v2);
    }
}

bool Joystick::direccion(bool& lr, bool& ud) {
    int jx = analogRead(PIN_X);
    int jy = analogRead(PIN_Y);
    
    lr = bool(jx);
    ud = bool(jy);
    return (jx == 4095 || jx == 0) || (jy == 4095 || jy == 0);
}

bool Joystick::botonPresionado() {
    bool btnState = !digitalRead(PIN_BTN);
    bool pressed = btnState && !_btnLastState;
    _btnLastState = btnState;
    return pressed;
}
void Joystick::monitorear() {
    bool UD, LR;
    int X, Y;
    int Xr = analogRead(PIN_X);
    int Yr = analogRead(PIN_Y);
    bool dir = direccion(LR, UD);
    valoresXY(X, Y);
    String direcc = String(X)+String(Y);
    Serial.println("Joystick | X: " + String(X) + "  Y: " + String(Y) + "  REAL | X: " + String(Xr) + "  Y: " + String(Yr) + " | Direccion:" + String(dir ? direcc : "CENTRO"));
}