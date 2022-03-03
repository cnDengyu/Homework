#ifndef __USART_H
#define __USART_H

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
#define USARTc_IRQn              USART2_IRQn
#define USARTc_IRQHandler        USART2_IRQHandler

void USARTc_IRQHandler(void);
void USART_Configuration(void);

#endif
