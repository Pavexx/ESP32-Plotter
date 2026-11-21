#pragma once

#include <Arduino.h>

constexpr int VelocidadMaximaPasoPSeg = 2000;
constexpr int AceleracionMaxima = 2000;

constexpr float Distancia_Motores = 700.0f;
constexpr float Radio_Polea = 9.55f;
constexpr float Desfase_Gondola_X = 0.0f;
constexpr float Desfase_Gondola_Y = 0.0f;

constexpr float Yinicio = 210.0f;
constexpr float Xinicio = 350.0f;

// PLACEHOLDER: motor/pulley values
constexpr int PasosPorVuelta = 200;
constexpr int MICROSTEPS = 8;        // choose to match driver configuration
constexpr int GT2_Dientes = 30;
constexpr float GT2_PasoMM = 2.0f;

// Valores de cinematica precalculados
constexpr float PasosPorMM = (PasosPorVuelta * MICROSTEPS) / (GT2_Dientes * GT2_PasoMM);
constexpr float Radio_Polea_sq = Radio_Polea * Radio_Polea;
const float Izq0 = sqrtf(Xinicio*Xinicio+Yinicio*Yinicio);
const float Der0 = sqrtf((Xinicio-Distancia_Motores)*(Xinicio-Distancia_Motores)+Yinicio*Yinicio);

// G-code coordinate transform:
// canvas = gcode * scale + offset
constexpr float GCODE_SCALE_X = 1.0f;
constexpr float GCODE_SCALE_Y = 1.0f;
constexpr float GCODE_OFFSET_X_MM = 0.0f;
constexpr float GCODE_OFFSET_Y_MM = 0.0f;

// PLACEHOLDER: maximum length of each straight XY planner segment.
constexpr float MAX_SEGMENT_LENGTH_MM = 2.0f;