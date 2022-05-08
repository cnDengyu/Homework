#pragma once
#ifndef __CORE_H
#define __CORE_H

#include <stdbool.h>
#include <stm32f10x.h>

void Core_Init(void);
void Core_Run(void);

bool updateHeartbeatSend(void);

#endif
