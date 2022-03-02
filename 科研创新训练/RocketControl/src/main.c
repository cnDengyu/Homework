
#include <stm32f10x.h>
#include "core/core.h"

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
	
	// Core Ability Initlize 核心程序初始化
	CORE_Configuration();
	
	while(1)
	{
		
		// Thread:Core 核心线程
		CORE_Loop();
		
		// Thread:Event Happens by Second 每秒线程
		if(g_secondFlag == true)
		{
			GPIO_WriteBit(GPIOC, GPIO_Pin_13, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13)));
			g_secondFlag = false;
		}
		
	}
}

