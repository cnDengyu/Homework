// 在 Arduino 上使用，取消下一行的注释
// #define TARGET_ARDUINO

// 在 51 单片机上使用，取消下一行的注释
#define TARGET_51MCU

#include <reg52.h>
#include <intrins.h>

void digitalWrite(int,int);
int digitalRead(int);

#define HIGH 1
#define LOW 0

void pinMode(int,int);

#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2

void timer_start_51();

void setup();
void loop();

#define QUARTZ 11059200

void EEPROM_write(int,int);
int EEPROM_read(int);

void delay(uint);