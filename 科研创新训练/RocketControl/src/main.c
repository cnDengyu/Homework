
#include <stm32f10x.h>
#include "core/core.h"

/**
  * @brief  Main program ������
  * @param  None
  * @retval None
  */
int main(void)
{
	
	// Core Ability Initlize ���ĳ����ʼ��
	CORE_Configuration();
	
	while(1)
	{
		
		/*
		* Fake Thread Structure α�̼ܹ߳�
		*
		* scan specific variables, and decide which Fake Thread to run.
		* ɨ���ض���ȫ�ֱ���������Ӧ��ִ����Щα�̡߳�
		*
		* For example, when there is new information from Serial Port, run relative function.
		* For another example, when it's time to send a "Heart Beat" message, run relative function.
		* ���磬���������µ���Ϣ����ʱ��������صĴ������
		* �����磬������Ҫ��ʱ���͡�����������ʱ��������ش������
		* 
		* Under the Fake Thread Structure, 
		* interrupt functions can finish in a minimized controlable period, 
		* in case of interrupt irruption.
		* ��α�̼ܹ߳��£����е��жϷ�������ִ��ʱ�����������̣���ʱ��ɿأ��Է��жϳ�ͻ��
		*
		*	Exceptionally, it's better not to use Fake Thread when time precision acquared.
		* ����أ������ʱ�侫����Ҫ�󣬲�Ҫʹ��α�̡߳�
		*
		*/
		
		//---------------------------------------------
		// Fake Thread:Core �����߳�
		if(1)
		{
			CORE_Loop();
		}
		
		//---------------------------------------------
		// Fake Thread:Event Happens by Second ÿ���߳�
		if(g_secondFlag == true)
		{
			
			// Blink Test ���Ʋ���
			GPIO_WriteBit(GPIOC, GPIO_Pin_13, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13)));
			
			USART_SendData(USARTc, 't');
			
			g_secondFlag = false;
		}
		
	}
}

