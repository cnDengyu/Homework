#include <stm32f10x.h>
#include "./timer.h"
#include "./usart.h"
#include "./core.h"

static bool isHeartbeatRequired = false;

static void RCC_Configuration(void);
static void GPIO_Configuration(void);
static void NVIC_Configuration(void);

/**
  * @brief  Configures for core ability. 初始化核心功能。
  * @param  None
  * @retval None
  */
void Core_Init(void)
{
	/*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
     */     
       
  /* System Clocks Configuration */
  RCC_Configuration();

  /* NVIC Configuration */
  NVIC_Configuration();

  /* GPIO Configuration */
  GPIO_Configuration();
	
	/* Timer Basic Configuration */
	TIMER2_BASE_Configuration();
	
	/* USART Configuration*/
	USART_Configuration();
	
	// PWM Timer Configuration
	TIMER3_BASE_Configuration();
	
}

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
static void RCC_Configuration(void)
{
	/* PCLK1 = HCLK/4 */
  RCC_PCLK1Config(RCC_HCLK_Div4);

  /* TIM2 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	/* TIM3 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	/* GPIOA and GPIOB clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
                         RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);

  /* GPIOC clock enable */
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC | USARTc_GPIO_CLK | USARTs_GPIO_CLK | RCC_APB2Periph_AFIO , ENABLE); 	

	/* Enable USARTc Clock */
  RCC_APB2PeriphClockCmd(USARTc_CLK, ENABLE);
	
	/* Enable USARTs Clock */
  RCC_APB1PeriphClockCmd(USARTs_CLK, ENABLE);
}

/**
  * @brief  Configure the GPIO Pins.
  * @param  None
  * @retval None
  */
static void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
//=============================================================================
//LED -> PC13
//=============================================================================			 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_PinRemapConfig(GPIO_Remap_USART1,ENABLE);
	/* Configure USARTc Rx as input floating */
  GPIO_InitStructure.GPIO_Pin = USARTc_RxPin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(USARTc_GPIO, &GPIO_InitStructure);
	
	/* Configure USARTs Rx as input floating */
  GPIO_InitStructure.GPIO_Pin = USARTs_RxPin;
  GPIO_Init(USARTs_GPIO, &GPIO_InitStructure);
  
  /* Configure USARTc Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = USARTc_TxPin;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(USARTc_GPIO, &GPIO_InitStructure);
	
	/* Configure USARTs Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = USARTs_TxPin;
  GPIO_Init(USARTs_GPIO, &GPIO_InitStructure);

	/* GPIOA Configuration:TIM3 Channel1, 2, 3 and 4 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

}

/**
  * @brief  Configure the nested vectored interrupt controller.
  * @param  None
  * @retval None
  */
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
	
	/* Configure the NVIC Preemption Priority Bits */  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  
  /* Enable the USARTc Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USARTc_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	/* Enable the USARTz Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USARTs_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* Enable the TIM2 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  // NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
}

/**
  * @brief  Core codes running on main thread
  * @param  None
  * @retval None
  */
void Core_Run(void)
{
	
	isHeartbeatRequired = false;
	if(updateSecond())
	{
		isHeartbeatRequired = true;
		updateSecondClear();
	}

}

bool updateHeartbeatSend(void)
{
	return isHeartbeatRequired;
}

