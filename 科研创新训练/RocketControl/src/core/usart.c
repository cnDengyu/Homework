#include <stm32f10x.h>
#include "core/usart.h"
#include "core/core_type.h"


static uint8_t TxBuffer1[USART_MAX_BUFFER] = "USART Interrupt Example: USARTy -> USARTz using Interrupt";
static uint8_t TxBuffer2[USART_MAX_BUFFER] = "USART Interrupt Example: USARTz -> USARTy using Interrupt";
static uint8_t RxBuffer1[RxBufferSize1];
static uint8_t RxBuffer2[RxBufferSize2];
static __IO uint8_t TxCounter1 = 0x00;
static __IO uint8_t TxCounter2 = 0x00;
static __IO uint8_t RxCounter1 = 0x00; 
static __IO uint8_t RxCounter2 = 0x00;
static uint8_t NbrOfDataToTransfer1 = TxBufferSize1;
static uint8_t NbrOfDataToTransfer2 = TxBufferSize2;
static uint8_t NbrOfDataToRead1 = RxBufferSize1;
static uint8_t NbrOfDataToRead2 = RxBufferSize2;
static __IO TestStatus TransferStatus1 = FAILED; 
static __IO TestStatus TransferStatus2 = FAILED;

/**
  * @brief  This function handles USARTy global interrupt request.
  * @param  None
  * @retval None
  */
void USARTc_IRQHandler(void)
{
  if(USART_GetITStatus(USARTc, USART_IT_RXNE) != RESET)
  {
    /* Read one byte from the receive data register */
    RxBuffer1[RxCounter1++] = (uint8_t)USART_ReceiveData(USARTc);

    if(RxCounter1 == NbrOfDataToRead1)
    {
      /* Disable the USARTc Receive interrupt */
      USART_ITConfig(USARTc, USART_IT_RXNE, DISABLE);
    }
  }
  
  if(USART_GetITStatus(USARTc, USART_IT_TXE) != RESET)
  {   
    /* Write one byte to the transmit data register */
    USART_SendData(USARTc, TxBuffer1[TxCounter1++]);

    if(TxCounter1 == NbrOfDataToTransfer1)
    {
      /* Disable the USARTc Transmit interrupt */
      USART_ITConfig(USARTc, USART_IT_TXE, DISABLE);
    }    
  }
}

void USART_Configuration(void)
{
	USART_InitTypeDef USART_InitStructure;
	/* USARTy and USARTz configuration ------------------------------------------------------*/
  /* USARTy and USARTz configured as follow:
        - BaudRate = 9600 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  /* Configure USARTy */
  USART_Init(USARTc, &USART_InitStructure);
  
  /* Enable USARTy Receive and Transmit interrupts */
  USART_ITConfig(USARTc, USART_IT_RXNE, ENABLE);
  USART_ITConfig(USARTc, USART_IT_TXE, ENABLE);
  

  /* Enable the USARTy */
  USART_Cmd(USARTc, ENABLE);

}

void USARTc_SendBuffer(uint8_t* buffer, uint16_t length)
{
	uint8_t* p = buffer;
	uint16_t n = length;
	while(n > 0x00)
	{		
		TxBuffer1[NbrOfDataToTransfer1++] = *p++;
		n--;
	}
	USART_ITConfig(USARTc, USART_IT_TXE, ENABLE);
}
