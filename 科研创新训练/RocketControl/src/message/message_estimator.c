#include "mavlink/common/mavlink.h"
#include "./message_system.h"
#include "core/timer.h"
#include "core/usart.h"
#include "estimator/estimator.h"
#include "message_estimator.h"

void MessageEstimatorSender(void)
{
	mavlink_local_position_ned_t posm;
	mavlink_message_t msg;
	uint8_t buffer[USART_MAX_BUFFER];
	uint16_t len;
	struct LocalPosition pos;
	
	if(isEstimatorInitlized)
	{
		
		EstimatorGet(&pos);
		
		posm.time_boot_ms = GetBootTimeMs();
		posm.x = pos.pos[0];
		posm.y = pos.pos[1];
		posm.z = pos.pos[2];
		posm.vx = pos.vel[0];
		posm.vy = pos.vel[1];
		posm.vz = pos.vel[2];
		
		mavlink_msg_local_position_ned_encode(mavlink_system.sysid, mavlink_system.compid, &msg, &posm);
		len = mavlink_msg_to_send_buffer(buffer, &msg);
		USARTc_SendBuffer(buffer, len);
		
	}
}