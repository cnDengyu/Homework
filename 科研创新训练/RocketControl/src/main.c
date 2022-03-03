
#include <stm32f10x.h>
#include "core/core.h"
#include "mavlink.h"

mavlink_system_t mavlink_system = {
    158, // System ID (1-255)
    MAV_COMP_ID_AUTOPILOT1  // Component ID (a MAV_COMPONENT value)
};

/**
  * @brief  Main program ������
  * @param  None
  * @retval None
  */
int main(void)
{
	mavlink_message_t msg;
	mavlink_heartbeat_t heartbeat;
	uint8_t buffer[USART_MAX_BUFFER];
	uint16_t len;
	
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
			
			// mavlink test
			USART_SendBreak(USARTc);
			
			heartbeat.type = MAV_TYPE_ROCKET;
			heartbeat.autopilot = MAV_AUTOPILOT_GENERIC;
			heartbeat.base_mode = MAV_MODE_FLAG_HIL_ENABLED;
			heartbeat.custom_mode = 0;
			heartbeat.system_status = MAV_STATE_BOOT;
			mavlink_msg_heartbeat_encode(mavlink_system.sysid, mavlink_system.compid, &msg, &heartbeat);
			len = mavlink_msg_to_send_buffer(buffer, &msg);
			USARTc_SendBuffer(buffer, len);
			
			g_secondFlag = false;
		}
		
	}
}

