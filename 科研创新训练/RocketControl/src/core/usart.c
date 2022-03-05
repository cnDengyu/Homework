#include <stm32f10x.h>
#include "./usart.h"

static uint8_t TxBuffer1[USART_MAX_BUFFER] = "USART Interrupt Example: USARTc  using Interrupt";
static uint8_t TxBuffer2[USART_MAX_BUFFER] = "USART Interrupt Example: USARTs  using Interrupt";
static uint8_t RxBuffer1[RxBufferSize1];
static uint8_t RxBuffer2[RxBufferSize2];
static __IO uint8_t TxCounter1 = 0x00;
static __IO uint8_t TxCounter2 = 0x00;
static __IO uint8_t RxCounter1 = 0x00; 
static __IO uint8_t RxCounter2 = 0x00;
static uint8_t NbrOfDataToTransfer1 = TxBufferSize1;
static uint8_t NbrOfDataToTransfer2 = TxBufferSize2;
static uint8_t NbrOfDataToRead1 = 0;
static uint8_t NbrOfDataToRead2 = 0;
// static __IO TestStatus TransferStatus1 = FAILED; 
// static __IO TestStatus TransferStatus2 = FAILED;

void USART_Configuration(void)
{
	USART_InitTypeDef USART_InitStructure;
	/* USARTc and USARTs configuration ------------------------------------------------------*/
  /* USARTc configured as follow:
        - BaudRate = 57600 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 57600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  /* Configure USARTc */
  USART_Init(USARTc, &USART_InitStructure);
  
  /* Enable USARTc Receive and Transmit interrupts */
  USART_ITConfig(USARTc, USART_IT_RXNE, ENABLE);
  USART_ITConfig(USARTc, USART_IT_TXE, ENABLE);
  

  /* Enable the USARTc */
  USART_Cmd(USARTc, ENABLE);
	
	/* USARTs configured as follow:
        - BaudRate = 9600 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 57600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  /* Configure USARTs */
  USART_Init(USARTs, &USART_InitStructure);
  
  /* Enable USARTs Receive and Transmit interrupts */
  USART_ITConfig(USARTs, USART_IT_RXNE, ENABLE);
  USART_ITConfig(USARTs, USART_IT_TXE, ENABLE);

  /* Enable the USARTs */
  USART_Cmd(USARTs, ENABLE);

}

/**
  * @brief  This function handles USARTc global interrupt request.
  * @param  None
  * @retval None
  */
void USARTc_IRQHandler(void)
{
  if(USART_GetITStatus(USARTc, USART_IT_RXNE) != RESET)
  {
    /* Read one byte from the receive data register */
    RxBuffer1[NbrOfDataToRead1++] = (uint8_t)USART_ReceiveData(USARTc);

    if(RxCounter1 == NbrOfDataToRead1)
    {
      /* Disable the USARTc Receive interrupt */
      // USART_ITConfig(USARTc, USART_IT_RXNE, DISABLE);
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



/**
  * @brief  Send a buffer to USARTc 向通讯串口发送一串数据
  * @param  buffer to send; length of buffer. 需要发送的数据和数据长度
  * @retval None
  */
void USARTc_SendBuffer(uint8_t* buffer, uint16_t length)
{
	uint8_t* p = buffer;
	uint16_t n = length;
	USART_ITConfig(USARTc, USART_IT_TXE, DISABLE);
	while(n > 0x00)
	{		
		TxBuffer1[NbrOfDataToTransfer1++] = *p++;
		n--;
	}
	USART_ITConfig(USARTc, USART_IT_TXE, ENABLE);
}

/**
  * @brief  Detect data from USARTc. 检测通讯串口是否有数据发来
  * @param  None.
  * @retval None
  */
bool USARTc_Available(void)
{
	if(RxCounter1 == NbrOfDataToRead1)
	{
		return false;
	}
	else
	{
		return true;
	}
}
/**
  * @brief  Read a byte from USARTc. 从通讯串口读取一个字节
  * @param  None.
  * @retval None
  */
uint8_t USARTc_ReadByte(void)
{
	uint8_t c;
	
	USART_ITConfig(USARTc, USART_IT_RXNE, DISABLE);
	
	c = RxBuffer1[RxCounter1++];
	
	USART_ITConfig(USARTc, USART_IT_RXNE, ENABLE);
	
	return c;
}


/**
  * @brief  This function handles USARTs global interrupt request.
  * @param  None
  * @retval None
  */
void USARTs_IRQHandler(void)
{
  if(USART_GetITStatus(USARTs, USART_IT_RXNE) != RESET)
  {
    /* Read one byte from the receive data register */
    RxBuffer2[NbrOfDataToRead2++] = (uint8_t)USART_ReceiveData(USARTs);

    if(RxCounter2 == NbrOfDataToRead2)
    {
      /* Disable the USARTc Receive interrupt */
      // USART_ITConfig(USARTs, USART_IT_RXNE, DISABLE);
    }
  }
  
  if(USART_GetITStatus(USARTs, USART_IT_TXE) != RESET)
  {   
    /* Write one byte to the transmit data register */
    USART_SendData(USARTs, TxBuffer2[TxCounter2++]);

    if(TxCounter2 == NbrOfDataToTransfer2)
    {
      /* Disable the USARTc Transmit interrupt */
      USART_ITConfig(USARTs, USART_IT_TXE, DISABLE);
    }    
  }
}



/**
  * @brief  Send a buffer to USARTc 向传感器串口发送一串数据
  * @param  buffer to send; length of buffer. 需要发送的数据和数据长度
  * @retval None
  */
void USARTs_SendBuffer(uint8_t* buffer, uint16_t length)
{
	uint8_t* p = buffer;
	uint16_t n = length;
	USART_ITConfig(USARTs, USART_IT_TXE, DISABLE);
	while(n > 0x00)
	{		
		TxBuffer2[NbrOfDataToTransfer2++] = *p++;
		n--;
	}
	USART_ITConfig(USARTs, USART_IT_TXE, ENABLE);
}

/**
  * @brief  Detect data from USARTc. 检测传感器串口是否有数据发来
  * @param  None.
  * @retval None
  */
bool USARTs_Available(void)
{
	if(RxCounter2 == NbrOfDataToRead2)
	{
		return false;
	}
	else
	{
		return true;
	}
}
/**
  * @brief  Read a byte from USARTs. 从传感器串口读取一个字节
  * @param  None.
  * @retval None
  */
uint8_t USARTs_ReadByte(void)
{
	uint8_t c;
	
	USART_ITConfig(USARTs, USART_IT_RXNE, DISABLE);
	c = RxBuffer2[RxCounter2++];
	USART_ITConfig(USARTs, USART_IT_RXNE, ENABLE);
	
	return c;
}
