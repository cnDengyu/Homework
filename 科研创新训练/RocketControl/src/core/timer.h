#pragma once
#ifndef __TIMER_H
#define __TIMER_H

#include <stdbool.h>
#include <stm32f10x.h>

void TIMER2_BASE_Configuration(void);
void TIMER3_BASE_Configuration(void);
uint32_t GetBootTimeMs(void);
bool updateSecond(void);
void updateSecondClear(void);

void TIM3Set(unsigned int id, double pulserate);

#endif
