#include "GCodes.h"

int GCodes::obtenerComando(char* line) {
    parser.ParseLine(line);

    if (parser.HasWord('G')) {
        int g = (int)parser.GetWordValue('G');

        if (g == 0 || g == 1) return CMD_G0_G1;
        if (g == 28) return CMD_G28;
    }

    if (parser.HasWord('M')) {
        int m = (int)parser.GetWordValue('M');

        if (m == 0) return CMD_M0;

        if (m == 280 &&
            parser.HasWord('P') && (int)parser.GetWordValue('P') == 0 &&
            parser.HasWord('S')) {
        float s = parser.GetWordValue('S');
        if (s == 90.0f) return CMD_Subir;
        if (s == 25.0f) return CMD_Bajar;
        }
    }
    return CMD_UNKNOWN;
}

bool GCodes::obtenerXY(char* line, float& x, float& y) {
    parser.ParseLine(line);

    if (!(parser.HasWord('G'))) return false;

    int g = (int)parser.GetWordValue('G');
    if (!(g == 0 || g == 1)) return false;

    if (!parser.HasWord('X') || !parser.HasWord('Y')) return false;

    x = parser.GetWordValue('X');
    y = parser.GetWordValue('Y');
    return true;
}

const char* GCodes::obtenerTexto(char* line) {
  return line + 3;
}