#pragma once
#ifndef __ACTUATOR_H
#define __ACTUATOR_H

#define ID_RUDDER_1 1
#define ID_RUDDER_2 2
#define ID_RUDDER_3 3
#define ID_RUDDER_4 4
#define ID_PARACHUTE 11
#define ID_TURBOFAN 0

void ActRudder(unsigned short id, double angle);
void ActTurbofan(double force);
void ActParachute(double angle);

#endif
