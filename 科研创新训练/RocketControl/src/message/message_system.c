#include "mavlink/minimal/mavlink.h"
#include "message_system.h"

const mavlink_system_t mavlink_system = {
    158, // System ID (1-255)
    MAV_COMP_ID_AUTOPILOT1  // Component ID (a MAV_COMPONENT value)
};

static uint8_t global = MAV_STATE_CALIBRATING;

uint8_t GetSystemStatus(void)
{
	return global;
}

void SetSystemStatus(uint8_t status)
{
	global = status;
}
