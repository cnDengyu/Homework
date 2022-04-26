#pragma once
#ifndef __TIMER_H
#define __TIMER_H

#include <stdbool.h>
#include <stm32f10x.h>

void TIMER_BASE_Configuration(void);
uint32_t GetBootTimeMs(void);
bool updateSecond(void);
void updateSecondClear(void);

#endif
