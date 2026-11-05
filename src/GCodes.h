#pragma once

#include <Arduino.h>
#include <GCodeParser.h>

enum Comando {
    CMD_UNKNOWN = 0,
    CMD_G0_G1   = 1,    //mover
    CMD_G28     = 2,    //ir a 0, 0
    CMD_M0      = 3,    //pausar y mostrar texto
    CMD_Subir   = 4,    //subir servo
    CMD_Bajar   = 5     //bajar texto
};

class GCodes {
public:
    int obtenerComando(char* line);
    bool obtenerXY(char* line, float& x, float& y);
    const char* obtenerTexto(char* line);

private:
    GCodeParser parser;
};