#include <string.h>
#include <stdbool.h>
#include <stm32f10x.h>
#include "core/timer.h"
#include "./sensor_status.h"

#define TYPESNUM 11

static struct RawSensorStatus rawSensorStatus;
static struct ScaledSensorStatus scaledSensorStatus;
static bool initlized[TYPESNUM] = {false, false, false, false, false, false, false, false, false, false, false};

static float oriPressure = 0;

static uint8_t sensorRefreshed = 0x00;

static const double pi = 3.1415926535;

void SensorGet(void* stcInfo, uint8_t infoType)
{
	switch(infoType)
	{
		case TYPE_TIME:
			memcpy(stcInfo, &rawSensorStatus.stcTime,8);
			break;
		case TYPE_ACC:
			memcpy(stcInfo, &rawSensorStatus.stcAcc,8);
			break;
		case TYPE_GYRO:
			memcpy(stcInfo, &rawSensorStatus.stcGyro,8);
			break;
		case TYPE_ANGLE:
			memcpy(stcInfo, &rawSensorStatus.stcAngle,8);
			break;
		case TYPE_MAG:
			memcpy(stcInfo, &rawSensorStatus.stcMag,8);
			break;
		case TYPE_DSTATUS:
			memcpy(stcInfo, &rawSensorStatus.stcDStatus,8);
			break;
		case TYPE_PRESS:
			memcpy(stcInfo, &rawSensorStatus.stcPress,8);
			break;
		case TYPE_LONLAT:
			memcpy(stcInfo, &rawSensorStatus.stcLonLat,8);
			break;
		case TYPE_GPSV:
			memcpy(stcInfo, &rawSensorStatus.stcGPSV,8);
			break;
		case TYPE_Q:
			memcpy(stcInfo, &rawSensorStatus.stcQ,8);
		case TYPE_PRE:
			memcpy(stcInfo, &rawSensorStatus.stcPre, 8);
			break;
		
	}
}

void SensorScaledGet(struct ScaledSensorStatus* dst)
{
	memcpy(dst, &scaledSensorStatus, sizeof(scaledSensorStatus));
}

void SensorSetFromBuffer(char ucRxBuffer[])
{
	switch(ucRxBuffer[1])
	{
		case TYPE_TIME:
			memcpy(&rawSensorStatus.stcTime, &ucRxBuffer[2] ,8);
			scaledSensorStatus.ucYear = rawSensorStatus.stcTime.ucYear;
			scaledSensorStatus.ucMonth = rawSensorStatus.stcTime.ucMonth;
			scaledSensorStatus.ucDay = rawSensorStatus.stcTime.ucDay;
			scaledSensorStatus.ucHour = rawSensorStatus.stcTime.ucHour;
			scaledSensorStatus.ucMinute = rawSensorStatus.stcTime.ucMinute;
			scaledSensorStatus.ucSecond = rawSensorStatus.stcTime.ucSecond;
			scaledSensorStatus.usMiliSecond = rawSensorStatus.stcTime.usMiliSecond;
			break;
		
		case TYPE_ACC:
			memcpy(&rawSensorStatus.stcAcc,  &ucRxBuffer[2],8);
			// Scale Acceleration into mG
			scaledSensorStatus.a[0] = (int16_t)((double)rawSensorStatus.stcAcc.a[0]/32.768*16);
			scaledSensorStatus.a[1] = (int16_t)((double)rawSensorStatus.stcAcc.a[1]/32.768*16);
			scaledSensorStatus.a[2] = (int16_t)((double)rawSensorStatus.stcAcc.a[2]/32.768*16);
			scaledSensorStatus.T = (int16_t)rawSensorStatus.stcAcc.T;
			break;
		
		case TYPE_GYRO:
			memcpy(&rawSensorStatus.stcGyro,  &ucRxBuffer[2],8);
			// Scale Gyro into mrad/s
			scaledSensorStatus.gyro[0] = (int16_t)((double)rawSensorStatus.stcGyro.w[0]/32.768*2000/180*pi);
			scaledSensorStatus.gyro[1] = (int16_t)((double)rawSensorStatus.stcGyro.w[1]/32.768*2000/180*pi);
			scaledSensorStatus.gyro[2] = (int16_t)((double)rawSensorStatus.stcGyro.w[2]/32.768*2000/180*pi);
			scaledSensorStatus.w[0] = (float)((double)rawSensorStatus.stcGyro.w[0]/32768*2000/180*pi);
			scaledSensorStatus.w[1] = (float)((double)rawSensorStatus.stcGyro.w[1]/32768*2000/180*pi);
			scaledSensorStatus.w[2] = (float)((double)rawSensorStatus.stcGyro.w[2]/32768*2000/180*pi);
			scaledSensorStatus.T = (int16_t)rawSensorStatus.stcGyro.T;
			break;
		
		case TYPE_ANGLE:
			memcpy(&rawSensorStatus.stcAngle,  &ucRxBuffer[2],8);
			scaledSensorStatus.angle[0] = (float)rawSensorStatus.stcAngle.Angle[0]/32768*(float)pi;
			scaledSensorStatus.angle[1] = (float)rawSensorStatus.stcAngle.Angle[1]/32768*(float)pi;
			scaledSensorStatus.angle[2] = (float)rawSensorStatus.stcAngle.Angle[2]/32768*(float)pi;
			break;
		
		case TYPE_MAG:
			memcpy(&rawSensorStatus.stcMag,  &ucRxBuffer[2],8);
			// Scale uT into mGauss
			scaledSensorStatus.mag[0] = rawSensorStatus.stcMag.h[0] * 10;
			scaledSensorStatus.mag[1] = rawSensorStatus.stcMag.h[1] * 10;
			scaledSensorStatus.mag[2] = rawSensorStatus.stcMag.h[2] * 10;
			scaledSensorStatus.T = (int16_t)rawSensorStatus.stcMag.T;
			break;
		
		case TYPE_DSTATUS:
			memcpy(&rawSensorStatus.stcDStatus,  &ucRxBuffer[2],8);
			scaledSensorStatus.dStatus[0] = rawSensorStatus.stcDStatus.sDStatus[0];
			scaledSensorStatus.dStatus[1] = rawSensorStatus.stcDStatus.sDStatus[1];
			scaledSensorStatus.dStatus[2] = rawSensorStatus.stcDStatus.sDStatus[2];
			scaledSensorStatus.dStatus[3] = rawSensorStatus.stcDStatus.sDStatus[3];
			break;
		
		case TYPE_PRESS:
			memcpy(&rawSensorStatus.stcPress,  &ucRxBuffer[2],8);
			// Scale Pa into hPa
			scaledSensorStatus.pressure = (float)rawSensorStatus.stcPress.lPressure/100;
			scaledSensorStatus.height = rawSensorStatus.stcPress.lAltitude * 10;
			if(initlized[TYPE_PRESS - TYPE_TIME] == false)
			{
				scaledSensorStatus.press_diff = 0;
				oriPressure = scaledSensorStatus.pressure;
				return;
			}else{
				scaledSensorStatus.press_diff = scaledSensorStatus.pressure - oriPressure;
			}
			
			break;
		
		case TYPE_LONLAT:
			memcpy(&rawSensorStatus.stcLonLat,  &ucRxBuffer[2],8);
			if(rawSensorStatus.stcPre.SN == 0 || initlized[TYPE_PRE-TYPE_TIME]==false)
			{
				return;
			}
			scaledSensorStatus.lon = rawSensorStatus.stcLonLat.lLon;
			scaledSensorStatus.lat = rawSensorStatus.stcLonLat.lLat;
			break;
		
		case TYPE_GPSV:
			memcpy(&rawSensorStatus.stcGPSV,  &ucRxBuffer[2],8);
			// no signal check
			if(rawSensorStatus.stcPre.SN == 0 || initlized[TYPE_PRE-TYPE_TIME]==false)
			{
				return;
			}
			if(!(rawSensorStatus.stcLonLat.lLat | rawSensorStatus.stcLonLat.lLon))
			{
				return;
			}
			// Scale dm into mm
			scaledSensorStatus.alt = rawSensorStatus.stcGPSV.sGPSHeight * 100;
			scaledSensorStatus.vel = (uint16_t)rawSensorStatus.stcGPSV.lGPSVelocity/36;
			scaledSensorStatus.yaw = (uint16_t)rawSensorStatus.stcGPSV.sGPSYaw;
			break;
		
		case TYPE_Q:
			memcpy(&rawSensorStatus.stcQ,  &ucRxBuffer[2],8);
			scaledSensorStatus.q[0] = (float)rawSensorStatus.stcQ.q[0]/32768;
			scaledSensorStatus.q[1] = (float)rawSensorStatus.stcQ.q[1]/32768;
			scaledSensorStatus.q[2] = (float)rawSensorStatus.stcQ.q[2]/32768;
			scaledSensorStatus.q[3] = (float)rawSensorStatus.stcQ.q[3]/32768;
			break;
		
		case TYPE_PRE:
			memcpy(&rawSensorStatus.stcPre, &ucRxBuffer[2], 8);
			scaledSensorStatus.eph = rawSensorStatus.stcPre.HDOP;
			scaledSensorStatus.epv = rawSensorStatus.stcPre.VDOP;
			scaledSensorStatus.satellites_visible = (uint8_t)rawSensorStatus.stcPre.SN;
			break;
		
		default:
			return;
	}
	initlized[ucRxBuffer[1] - TYPE_TIME] = true;
	sensorRefreshed = ucRxBuffer[1];
	scaledSensorStatus.timestamp = GetBootTimeMs();
}

uint8_t updateSensor(void)
{
	return sensorRefreshed;
}

void updateSensorClear(void)
{
	sensorRefreshed = 0x00;
}

bool isSensorInitlized(uint8_t type)
{
	if(TYPE_TIME <= type && TYPE_PRE >= type)
	{
		return initlized[type-TYPE_TIME];
	}
	else
	{
		return false;
	}
}

bool isSensorAllInitlized(void)
{
	unsigned int i=0;
	bool result=false;
	for(i=0; i<TYPESNUM; i++)
	{
		result = result & initlized[i];
	}
	return result;
}
