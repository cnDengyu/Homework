#include "core/timer.h"
#include "actuator.h"

void ActRudder(unsigned short id, double angle)
{
	double pulserate = 0;
	
	pulserate = ((angle / 180 * 2 + 0.5)/20);

	switch(id)
	{
		case ID_RUDDER_1:
			TIM3Set(1, pulserate);
			break;
		case ID_RUDDER_2:
			TIM3Set(2, pulserate);
			break;
		case ID_RUDDER_3:
			TIM3Set(3, pulserate);
			break;
		case ID_RUDDER_4:
			TIM3Set(4, pulserate);
			break;
		default:
			break;
	}
}

void ActTurbofan(double force)
{
	
}

void ActParachute(double angle)
{
	
}
