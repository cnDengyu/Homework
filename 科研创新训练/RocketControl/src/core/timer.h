#ifndef __TIMER_H
#define __TIMER_H

#include <stdbool.h>

extern bool g_secondFlag;

void TIMER_BASE_Configuration(void);

void TIM2_IRQHandler(void);

#endif
