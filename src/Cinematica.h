#pragma once

#include <Arduino.h>

void XYaPasos(float X, float Y, int32_t& PasosIzq, int32_t& PasosDer);
int16_t CantSegmentos(float X, float Y);
void PasosIntermedio(int16_t i, int32_t& PasosIzq, int32_t& PasosDer);