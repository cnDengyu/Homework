
#ifndef __CORE_H
#define __CORE_H

#include <stdbool.h>

#define USARTc                   USART1

void CORE_Configuration(void);
void CORE_Loop(void);

extern bool g_secondFlag;

#endif
