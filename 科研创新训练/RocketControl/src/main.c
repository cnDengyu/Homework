
#include <stm32f10x.h>
#include "core/core.h"
#include "mavlink.h"

mavlink_system_t mavlink_system = {
    158, // System ID (1-255)
    MAV_COMP_ID_AUTOPILOT1  // Component ID (a MAV_COMPONENT value)
};

/**
  * @brief  Main program 主程序
  * @param  None
  * @retval None
  */
int main(void)
{
	mavlink_message_t msg;
	mavlink_heartbeat_t heartbeat;
	uint8_t buffer[USART_MAX_BUFFER];
	uint16_t len;
	
	// Core Ability Initlize 核心程序初始化
	CORE_Configuration();
	
	while(1)
	{
		
		/*
		* Fake Thread Structure 伪线程架构
		*
		* scan specific variables, and decide which Fake Thread to run.
		* 扫描特定的全局变量，决定应该执行哪些伪线程。
		*
		* For example, when there is new information from Serial Port, run relative function.
		* For another example, when it's time to send a "Heart Beat" message, run relative function.
		* 例如，当串口有新的信息发来时，运行相关的处理程序。
		* 又例如，到了需要定时发送“心跳包”的时候，运行相关处理程序。
		* 
		* Under the Fake Thread Structure, 
		* interrupt functions can finish in a minimized controlable period, 
		* in case of interrupt irruption.
		* 在伪线程架构下，所有的中断服务函数的执行时间可以缩到最短，且时间可控，以防中断冲突。
		*
		*	Exceptionally, it's better not to use Fake Thread when time precision acquared.
		* 例外地，如果对时间精度有要求，不要使用伪线程。
		*
		*/
		
		//---------------------------------------------
		// Fake Thread:Core 核心线程
		if(1)
		{
			CORE_Loop();
		}
		
		//---------------------------------------------
		// Fake Thread:Event Happens by Second 每秒线程
		if(g_secondFlag == true)
		{
			
			// Blink Test 闪灯测试
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

