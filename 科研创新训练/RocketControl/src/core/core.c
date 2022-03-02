#include <stm32f10x.h>
#include "core/configuration.h"
#include "core/timer.h"
#include "core/core.h"


/**
  * @brief  Configures for core ability. 初始化核心功能。
  * @param  None
  * @retval None
  */
void CORE_Configuration(void)
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
	TIMER_BASE_Configuration();
	
}

/**
  * @brief  Core codes running on main thread
  * @param  None
  * @retval None
  */
void CORE_Loop(void)
{
	
}
