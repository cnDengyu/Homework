
#include <stm32f10x.h>
#include "core/core.h"

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
	
	// Core Ability Initlize ���ĳ����ʼ��
	CORE_Configuration();
	
	while(1)
	{
		
		// Thread:Core �����߳�
		CORE_Loop();
		
		// Thread:Event Happens by Second ÿ���߳�
		if(g_secondFlag == true)
		{
			GPIO_WriteBit(GPIOC, GPIO_Pin_13, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13)));
			g_secondFlag = false;
		}
		
	}
}

