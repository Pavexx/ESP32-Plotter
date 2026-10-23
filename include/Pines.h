#pragma once

#include <Arduino.h>
//no probé si funciona ninguno de estos
//para el tft van clk 18, mosi 23 y miso 19? no me fijé
constexpr uint8_t TFT_CS  = 5;
constexpr uint8_t TFT_RST = 4;
constexpr uint8_t TFT_DC  = 2;

constexpr uint8_t SD_DC  = 21;  

constexpr uint8_t PIN_BTN  = 27;
constexpr uint8_t PIN_BTN2  = 16;
constexpr uint8_t PIN_X  = 32;
constexpr uint8_t PIN_Y  = 33;

constexpr uint8_t PIN_LEFT_STEP = 13;
constexpr uint8_t PIN_LEFT_DIR  = 12;
constexpr uint8_t PIN_LEFT_EN   = 14;

constexpr uint8_t PIN_RIGHT_STEP = 26;
constexpr uint8_t PIN_RIGHT_DIR  = 25;
constexpr uint8_t PIN_RIGHT_EN   = 22;

// Servo
constexpr uint8_t SERVO_PIN = 17;