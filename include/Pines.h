#pragma once

#include <Arduino.h>

constexpr uint8_t TFT_CS  = 21; 
constexpr uint8_t TFT_RST = 14; 
constexpr uint8_t TFT_DC  = 13; //A0
//GPIO18 → TFT SCK + SD SCK
//GPIO23 → TFT SDA + SD MOSI
//GPIO19 → SD MISO
constexpr uint8_t SD_CS  = 21;

constexpr uint8_t PIN_BTN  = 4; //[NO PROBADO]
constexpr uint8_t PIN_X  = 34;  //[NO PROBADO]
constexpr uint8_t PIN_Y  = 35;  //[NO PROBADO]

constexpr uint8_t PIN_LEFT_STEP = 32;
constexpr uint8_t PIN_LEFT_DIR  = 33;

constexpr uint8_t PIN_RIGHT_STEP = 16;
constexpr uint8_t PIN_RIGHT_DIR  = 17;

constexpr uint8_t SERVO_PIN = 25;  //[NO PROBADO]


//                     ILUSTRACIÓN DE CONEXIONES
//
//                             ┌───────┐
//                   ╭━━━━━━━━━┤       ├━━━━━━━━━╮
//                   ┃ ( )  ◘  │  USB  │  ◘  ( ) ┃
//                   ┃    boot │       │ en      ┃
//                   ┃         └───────┘         ┃
//                   ┃ [ ] 3V3            5V [ ] ┃
//                   ┃ [ ] GND           GND [ ] ┃
//                   ┃ [!] D15           D13 [ ] ┃ TFT_DC (A0)
//                   ┃ [!] D2 ○          D12 [!] ┃             
//       Joystick SW ┃ [ ] D4            D14 [ ] ┃ TFT_RST
//      Motor L STEP ┃ [ ] RX2 (16)      D27 [ ] ┃
//       Motor L DIR ┃ [ ] TX2 (17)      D26 [ ] ┃
//                   ┃ [!] D5            D25 [ ] ┃ SERVO
//    TFT_SCK+SD_SCK ┃ [ ] D18╶─────────╴D33 [ ] ┃ Motor R DIR
//           SD_MISO ┃ [ ] D19           D32 [ ] ┃ Motor R STEP
//            TFT_CS ┃ [ ] D21           D35 [!] ┃ Joystick Y
//                   ┃ [X] RX0 (3)       D34 [!] ┃ Joystick X
//                   ┃ [X] TX0 (1)        VN [!] ┃
//             SD_CS ┃ [ ] D22            VP [!] ┃
//   TFT_SDA+SD_MOSI ┃ [ ] D23            EN [X] ┃
//                   ┃      └─────────────┘      ┃
//                   ┃                           ┃
//                   ┃ ( )                   ( ) ┃
//                   ╰━━━━━━━━━━━━━━━━━━━━━━━━━━━╯