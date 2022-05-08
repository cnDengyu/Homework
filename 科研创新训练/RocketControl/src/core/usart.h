#pragma once
#ifndef __USART_H
#define __USART_H

#include <stm32f10x.h>
#include <stdbool.h>

#define USART_MAX_BUFFER 0xff

typedef enum { FAILED = 0, PASSED = !FAILED} TestStatus;

#define TxBufferSize1   (countof(TxBuffer1) - 1)
#define TxBufferSize2   (countof(TxBuffer2) - 1)
#define RxBufferSize1   TxBufferSize2
#define RxBufferSize2   TxBufferSize1


#define countof(a)   (sizeof(a) / sizeof(*(a)))

/*
* USART GPIO Definition
* 串口引脚定义
*/

// USARTc Definition, where 'c' means communication
// USARTc 引脚定义，其中c代表“通讯”
#define USARTc                   USART1
#define USARTc_GPIO              GPIOB
#define USARTc_CLK               RCC_APB2Periph_USART1
#define USARTc_GPIO_CLK          RCC_APB2Periph_GPIOB
#define USARTc_RxPin             GPIO_Pin_7
#define USARTc_TxPin             GPIO_Pin_6
#define USARTc_IRQn              USART1_IRQn
#define USARTc_IRQHandler        USART1_IRQHandler

// USARTs Definition, where 's' means sensor
// USARTs 引脚定义，其中s代表“传感器”
#define USARTs                   USART2
#define USARTs_GPIO              GPIOA
#define USARTs_CLK               RCC_APB1Periph_USART2
#define USARTs_GPIO_CLK          RCC_APB2Periph_GPIOA
#define USARTs_RxPin             GPIO_Pin_3
#define USARTs_TxPin             GPIO_Pin_2
#define USARTs_IRQn              USART2_IRQn
#define USARTs_IRQHandler        USART2_IRQHandler

void USARTc_IRQHandler(void);
void USARTc_SendBuffer(uint8_t* buffer, uint16_t length);
bool USARTc_Available(void);
uint8_t USARTc_ReadByte(void);

void USARTs_IRQHandler(void);
void USARTs_SendBuffer(uint8_t* buffer, uint16_t length);
bool USARTs_Available(void);
uint8_t USARTs_ReadByte(void);

void USART_Configuration(void);

#endif
