#pragma once

#include <Arduino.h>

constexpr int VelocidadMaximaPasoPSeg = 1500;
constexpr int AceleracionMaxima = 3000;

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

// Escala y desplazamiento usado para los gcodes
constexpr float GCODE_EscalaX = 1.0f;
constexpr float GCODE_EscalaY = 1.0f;
constexpr float GCODE_DesplazamientoX = 0.0f;
constexpr float GCODE_DesplazamientoY = 0.0f;

// Largo maximo de segmentos para el planner
constexpr float SegmentoMaximo = 2.0f;