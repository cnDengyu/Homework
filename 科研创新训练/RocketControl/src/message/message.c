#include "core/core_type.h"
#include "mavlink/common/mavlink.h"
#include "core/usart.h"
#include "./message.h"

const mavlink_system_t mavlink_system = {
    158, // System ID (1-255)
    MAV_COMP_ID_AUTOPILOT1  // Component ID (a MAV_COMPONENT value)
};

static void SendHeartBeat(void);
static void SendCommandAck(uint16_t command_id, uint8_t result);

void MessageManager(void)
{
	uint8_t nextbyte;
	mavlink_status_t status;
	mavlink_message_t msg;
	int chan = MAVLINK_COMM_0;
	
	SendHeartBeat();
	
	while(USARTc_Available())
	{
		nextbyte = USARTc_ReadByte();
		if(mavlink_parse_char(chan, nextbyte, &msg, &status))
		{
			switch(msg.msgid) {
				
				case MAV_CMD_REQUEST_PROTOCOL_VERSION:
					SendCommandAck(msg.msgid, MAV_RESULT_ACCEPTED);
					break;
				
				case MAVLINK_MSG_ID_PARAM_REQUEST_LIST:
					
					break;
				
				default:
					break;
			}
		}
	}
}

static void SendHeartBeat(void)
{
	mavlink_message_t msg;
	mavlink_heartbeat_t heartbeat;
	uint8_t buffer[USART_MAX_BUFFER];
	uint16_t len;
	
	if(g_heartBeat == true)
	{
			
		// Blink Test …¡µ∆≤‚ ‘
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13)));
			
		heartbeat.type = MAV_TYPE_ROCKET;
		heartbeat.autopilot = MAV_AUTOPILOT_GENERIC;
		heartbeat.base_mode = MAV_MODE_FLAG_HIL_ENABLED;
		heartbeat.custom_mode = 0;
		heartbeat.system_status = MAV_STATE_BOOT;
		mavlink_msg_heartbeat_encode(mavlink_system.sysid, mavlink_system.compid, &msg, &heartbeat);
		len = mavlink_msg_to_send_buffer(buffer, &msg);
		USARTc_SendBuffer(buffer, len);
			
		g_heartBeat = false;
	}
}

static void SendCommandAck(uint16_t command_id, uint8_t result)
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

static void SendParamValue()
{
	
}
