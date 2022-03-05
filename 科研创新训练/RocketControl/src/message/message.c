#include "core/timer.h"
#include "mavlink/common/mavlink.h"
#include "core/usart.h"
#include "sensor/sensor_status.h"
#include "./message_system.h"
#include "./message_sensor.h"
#include "./message.h"

static void HeartBeatSender(void);
static void CommandAckSender(uint16_t command_id, uint8_t result);
static void MessageReceiver(void);

void MessageManager(void)
{
	
	HeartBeatSender();
	
	MessageReceiver();
	
	MessageSensorSender();
	
}

static void MessageReceiver(void)
{
	uint8_t nextbyte;
	mavlink_status_t status;
	mavlink_message_t msg;
	int chan = MAVLINK_COMM_0;
	
	while(USARTc_Available())
	{
		nextbyte = USARTc_ReadByte();
		if(mavlink_parse_char(chan, nextbyte, &msg, &status))
		{
			switch(msg.msgid) {
				
				case MAV_CMD_REQUEST_PROTOCOL_VERSION:
					CommandAckSender(msg.msgid, MAV_RESULT_ACCEPTED);
					break;
				
				case MAVLINK_MSG_ID_PARAM_REQUEST_LIST:
					
					break;
				
				default:
					break;
			}
		}
	}
}

static void HeartBeatSender(void)
{
	mavlink_message_t msg;
	mavlink_heartbeat_t heartbeat;
	uint8_t buffer[USART_MAX_BUFFER];
	uint16_t len;
	
	if(isHeartBeatRequired())
	{
					
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, 0);
		
		heartbeat.type = MAV_TYPE_ROCKET;
		heartbeat.autopilot = MAV_AUTOPILOT_GENERIC;
		heartbeat.base_mode = MAV_MODE_FLAG_HIL_ENABLED;
		heartbeat.custom_mode = 0;
		heartbeat.system_status = MAV_STATE_BOOT;
		mavlink_msg_heartbeat_encode(mavlink_system.sysid, mavlink_system.compid, &msg, &heartbeat);
		len = mavlink_msg_to_send_buffer(buffer, &msg);
		USARTc_SendBuffer(buffer, len);
			
		HeartBeatSended();
		
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, 1);
	}
}

static void CommandAckSender(uint16_t command_id, uint8_t result)
{
	mavlink_message_t msg;
	mavlink_command_ack_t ack;
	uint8_t buffer[USART_MAX_BUFFER];
	uint16_t len;
	
	ack.command = command_id;
	ack.result = result;
	mavlink_msg_command_ack_encode(mavlink_system.sysid, mavlink_system.compid, &msg, &ack);
	len = mavlink_msg_to_send_buffer(buffer, &msg);
	USARTc_SendBuffer(buffer, len);
}

static void CommandParamValueSender()
{
	
}
