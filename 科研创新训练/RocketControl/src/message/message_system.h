#pragma once
#ifndef __MESSAGE_SYSTEM
#define __MESSAGE_SYSTEM

#include "mavlink/minimal/mavlink.h"

extern const mavlink_system_t mavlink_system;

uint8_t GetSystemStatus(void);
void SetSystemStatus(uint8_t status);
/*
0	MAV_STATE_UNINIT	Uninitialized system, state is unknown.
1	MAV_STATE_BOOT	System is booting up.
2	MAV_STATE_CALIBRATING	System is calibrating and not flight-ready.
3	MAV_STATE_STANDBY	System is grounded and on standby. It can be launched any time.
4	MAV_STATE_ACTIVE	System is active and might be already airborne. Motors are engaged.
5	MAV_STATE_CRITICAL	System is in a non-normal flight mode. It can however still navigate.
6	MAV_STATE_EMERGENCY	System is in a non-normal flight mode. It lost control over parts or over the whole airframe. It is in mayday and going down.
7	MAV_STATE_POWEROFF	System just initialized its power-down sequence, will shut down now.
8	MAV_STATE_FLIGHT_TERMINATION	System is terminating itself.
*/

#endif
