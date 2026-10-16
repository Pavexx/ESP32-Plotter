#pragma once

#include <Arduino.h>

// PLACEHOLDER: example pins only; adjust for your ESP32 board.
constexpr int PIN_LEFT_STEP = 25;
constexpr int PIN_LEFT_DIR  = 26;
constexpr int PIN_LEFT_EN   = 27;

constexpr int PIN_RIGHT_STEP = 32;
constexpr int PIN_RIGHT_DIR  = 33;
constexpr int PIN_RIGHT_EN   = 14;

// PLACEHOLDER: mechanical calibration
constexpr double Distancia_Motores = 500.0;
constexpr double Radio_Polea = 10.0;
constexpr double Desfase_Gondola_X = 0.0;
constexpr double Desfase_Gondola_Y = 0.0;

constexpr double Yinicio = 300.0;
constexpr double Xinicio = 250.0;

// PLACEHOLDER: motor/pulley values
constexpr int PasosPorVuelta = 200;
constexpr int MICROSTEPS = 16;        // choose to match driver configuration
constexpr int GT2_Dientes = 20;       // PLACEHOLDER
constexpr double GT2_PasoMM = 2.0;    // PLACEHOLDER

// Flip either sign if that motor runs the wrong way.
constexpr int LEFT_DIRECTION_SIGN = 1;
constexpr int RIGHT_DIRECTION_SIGN = 1;

// G-code coordinate transform:
// canvas = gcode * scale + offset
constexpr double GCODE_SCALE_X = 1.0;
constexpr double GCODE_SCALE_Y = 1.0;
constexpr double GCODE_OFFSET_X_MM = 0.0;
constexpr double GCODE_OFFSET_Y_MM = 0.0;

// PLACEHOLDER speeds, in canvas mm/s. G-code F is ignored.
constexpr double G0_MAX_SPEED_MM_S = 100.0;
constexpr double G1_MAX_SPEED_MM_S = 30.0;

// PLACEHOLDER: maximum length of each straight XY planner segment.
constexpr double MAX_SEGMENT_LENGTH_MM = 2.0;

// Driver enable polarity may vary by board/driver wiring.
constexpr uint8_t DRIVER_ENABLE_LEVEL = LOW;
constexpr uint8_t DRIVER_DISABLE_LEVEL = HIGH;