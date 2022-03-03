#ifndef __USART_H
#define __USART_H

#include <stm32f10x.h>

typedef enum { FAILED = 0, PASSED = !FAILED} TestStatus;

#define TxBufferSize1   (countof(TxBuffer1) - 1)
#define TxBufferSize2   (countof(TxBuffer2) - 1)
#define RxBufferSize1   TxBufferSize2
#define RxBufferSize2   TxBufferSize1


#define countof(a)   (sizeof(a) / sizeof(*(a)))

/*
* USART GPIO Definition
* �������Ŷ���
*/

// USARTc Definition, where 'c' means communication
// USARTc ���Ŷ��壬����c����ͨѶ��
#define USARTc                   USART1
#define USARTc_GPIO              GPIOB
#define USARTc_CLK               RCC_APB2Periph_USART1
#define USARTc_GPIO_CLK          RCC_APB2Periph_GPIOB
#define USARTc_RxPin             GPIO_Pin_7
#define USARTc_TxPin             GPIO_Pin_6
#define USARTc_IRQn              USART1_IRQn
#define USARTc_IRQHandler        USART1_IRQHandler

extern const uint8_t c_usart_max_buffer;

void USARTc_IRQHandler(void);
void USART_Configuration(void);
void USARTc_SendBuffer(uint8_t* buffer, uint16_t length);

#endif
