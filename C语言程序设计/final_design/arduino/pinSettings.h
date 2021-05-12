#pragma once
/*
 * This file defines the pins linked to the buttons
 */

// 为 Arduino 设置引脚

#ifdef TARGET_ARDUINO

#include <Arduino.h>

#define PIN_PAUSE A1

#define PIN_RESUME A1

#define PIN_STOP A2

#define PIN_START A2

#define PIN_CLEAR A3

#define PIN_SAVE A4

#define PIN_LOAD A5

#define PIN_DOUBLE_DOT 1

#define PIN_DIG4 2

#define PIN_DIG3 3

#define PIN_DIG2 4

#define PIN_DIG1 5

#define PIN_DP 6

#define PIN_G 7

#define PIN_F 8

#define PIN_E 9

#define PIN_D 10

#define PIN_C 11

#define PIN_B 12

#define PIN_A 13

#define BUTTON_DOWN 1

#endif

// 为 51 单片机设置引脚

#ifdef TARGET_51MCU

#define PIN_PAUSE 101
#define PIN_RESUME 102
#define PIN_STOP 201
#define PIN_START 202
#define PIN_CLEAR 301
#define PIN_SAVE 401
#define PIN_LOAD 501
#define PIN_DOUBLE_DOT 1
#define PIN_DIG4 2
#define PIN_DIG3 3
#define PIN_DIG2 4
#define PIN_DIG1 5
#define PIN_DP 6
#define PIN_G 7
#define PIN_F 8
#define PIN_E 9
#define PIN_D 10
#define PIN_C 11
#define PIN_B 12
#define PIN_A 13

#define BUTTON_DOWN 0

#endif