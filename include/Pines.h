#pragma once

#include <Arduino.h>

constexpr uint8_t TFT_CS  = 4;
constexpr uint8_t TFT_RST = 16;
constexpr uint8_t TFT_DC  = 17;

constexpr uint8_t SD_DC  = 19;  //no probé si funciona

// PLACEHOLDER: example pins only; adjust for your ESP32 board.
constexpr int PIN_LEFT_STEP = 25;
constexpr int PIN_LEFT_DIR  = 26;
constexpr int PIN_LEFT_EN   = 27;

constexpr int PIN_RIGHT_STEP = 32;
constexpr int PIN_RIGHT_DIR  = 33;
constexpr int PIN_RIGHT_EN   = 14;
/*
// Stepper 1
constexpr uint8_t STEP1_PIN = 26;
constexpr uint8_t DIR1_PIN  = 27;
constexpr uint8_t EN1_PIN   = 25;

// Servo
constexpr uint8_t SERVO_PIN = 13;
*/