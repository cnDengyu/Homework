#include "mavlink/minimal/mavlink.h"
#include "message_system.h"

const mavlink_system_t mavlink_system = {
    158, // System ID (1-255)
    MAV_COMP_ID_AUTOPILOT1  // Component ID (a MAV_COMPONENT value)
};
