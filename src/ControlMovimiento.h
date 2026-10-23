#pragma once

//#include "GcodeParser.h"

class ControlMovimiento {
public:
    void iniciar();
    void controlManual(int8_t x, int8_t y);
    //bool controlManual(const GcodeCommand& command);

};