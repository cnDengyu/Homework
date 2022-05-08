#pragma once
#ifndef __ESTIMATOR_H
#define __ESTIMATOR_H

#include <stdbool.h>
#include <stm32f10x.h>

struct GlobalPositionInt{
	int32_t lat;	// Latitude, expressed in degE7
	int32_t lon;	// Longitude, expressed in degE7
	int32_t alt;	// Altitude (MSL). Note that virtually all GPS modules provide both WGS84 and MSL. in mm
	int32_t relative_alt;	// Altitude above ground in mm
	int16_t vx;		// Ground X Speed (Latitude, positive north) in cm/s
	int16_t vy;		// Ground Y Speed (Longitude, positive east) in cm/s
	int16_t vz;		// Ground Z Speed (Altitude, positive down) in cm/s
	int16_t hdg; 	// Vehicle heading (yaw angle) in cdeg, 0.0..359.99 degrees.  If unknown, set to: UINT16_MAX
};

struct GlobalOrigin{
	int32_t lat;	// Latitude, expressed in degE7
	int32_t lon;	// Longitude, expressed in degE7
	int32_t alt;	// Altitude (MSL). Note that virtually all GPS modules provide both WGS84 and MSL. in mm
};

struct LocalPosition{
	double pos[3];
	double vel[3];
};

void Estimator_Run(void);

bool updateEstimator(void);
bool isEstimatorInitlized(void);

void EstimatorGet(struct LocalPosition* dst);

#endif
