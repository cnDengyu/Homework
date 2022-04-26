#pragma once
#ifndef __SENSOR_STATUS
#define __SENSOR_STATUS

#include <stdbool.h>
#include <stm32f10x.h>

/*
#define SAVE 			0x00
#define CALSW 		0x01
#define RSW 			0x02
#define RRATE			0x03
#define BAUD 			0x04
#define AXOFFSET	0x05
#define AYOFFSET	0x06
#define AZOFFSET	0x07
#define GXOFFSET	0x08
#define GYOFFSET	0x09
#define GZOFFSET	0x0a
#define HXOFFSET	0x0b
#define HYOFFSET	0x0c
#define HZOFFSET	0x0d
#define D0MODE		0x0e
#define D1MODE		0x0f
#define D2MODE		0x10
#define D3MODE		0x11
#define D0PWMH		0x12
#define D1PWMH		0x13
#define D2PWMH		0x14
#define D3PWMH		0x15
#define D0PWMT		0x16
#define D1PWMT		0x17
#define D2PWMT		0x18
#define D3PWMT		0x19
#define IICADDR		0x1a
#define LEDOFF 		0x1b
#define GPSBAUD		0x1c

#define YYMM				0x30
#define DDHH				0x31
#define MMSS				0x32
#define MS					0x33
#define AX					0x34
#define AY					0x35
#define AZ					0x36
#define GX					0x37
#define GY					0x38
#define GZ					0x39
#define HX					0x3a
#define HY					0x3b
#define HZ					0x3c			
#define Roll				0x3d
#define Pitch				0x3e
#define Yaw					0x3f
#define TEMP				0x40
#define D0Status		0x41
#define D1Status		0x42
#define D2Status		0x43
#define D3Status		0x44
#define PressureL		0x45
#define PressureH		0x46
#define HeightL			0x47
#define HeightH			0x48
#define LonL				0x49
#define LonH				0x4a
#define LatL				0x4b
#define LatH				0x4c
#define GPSHeight   0x4d
#define GPSYAW      0x4e
#define GPSVL				0x4f
#define GPSVH				0x50
#define q0          0x51
#define q1          0x52
#define q2          0x53
#define q3          0x54
      
#define DIO_MODE_AIN 0
#define DIO_MODE_DIN 1
#define DIO_MODE_DOH 2
#define DIO_MODE_DOL 3
#define DIO_MODE_DOPWM 4
#define DIO_MODE_GPS 5		
*/

#define TYPE_TIME 	0x50
#define TYPE_ACC 		0x51
#define TYPE_GYRO 	0x52
#define TYPE_ANGLE 	0x53
#define TYPE_MAG 		0x54
#define TYPE_DSTATUS 0x55
#define TYPE_PRESS 	0x56
#define TYPE_LONLAT 0x57
#define TYPE_GPSV 	0x58
#define TYPE_Q 			0x59
#define TYPE_PRE		0x5A

struct SInfo
{
	short item[4];
};
struct STime
{
	unsigned char ucYear;
	unsigned char ucMonth;
	unsigned char ucDay;
	unsigned char ucHour;
	unsigned char ucMinute;
	unsigned char ucSecond;
	unsigned short usMiliSecond;
};
struct SAcc
{
	short a[3];
	short T;
};

struct SGyro
{
	short w[3];
	short T;
};

struct SAngle
{
	short Angle[3];
	short T;
};

struct SMag
{
	short h[3];
	short T;
};

struct SDStatus
{
	short sDStatus[4];
};

struct SPress
{
	long lPressure;
	long lAltitude;
};



struct SLonLat
{
	long lLon;
	long lLat;
};

struct SGPSV
{
	short sGPSHeight;
	short sGPSYaw;
	long lGPSVelocity;
};
struct SQ
{ short q[4];
};
struct SPre
{
	unsigned short SN;
	unsigned short PDOP;
	unsigned short HDOP;
	unsigned short VDOP;
};

struct RawSensorStatus
{
	struct STime		stcTime;
	struct SAcc 		stcAcc;
	struct SGyro 		stcGyro;
	struct SAngle 	stcAngle;
	struct SMag 		stcMag;
	struct SDStatus stcDStatus;
	struct SPress 	stcPress;
	struct SLonLat 	stcLonLat;
	struct SGPSV 		stcGPSV;
	struct SQ       stcQ;
	struct SPre 		stcPre;
};

struct ScaledAngle
{
	float Angle[3];
};
struct ScaledGyro
{
	int16_t w[3];
	int16_t T;
};
struct ScaledAcc
{
	int16_t a[3];
	int16_t T;
};
struct ScaledPress
{
	float pressure;
	float altitude;
};
struct ScaledSensorStatus
{
	uint32_t timestamp;
	unsigned char ucYear;
	unsigned char ucMonth;
	unsigned char ucDay;
	unsigned char ucHour;
	unsigned char ucMinute;
	unsigned char ucSecond;
	unsigned short usMiliSecond;
	int16_t a[3];			// acceleration in mG
	int16_t T;				// temperature in cdegC
	int16_t gyro[3];		// Angular speed in mrad/s
	float w[3];				// angular speed in rad/s
	float angle[3];		// angle in rad
	int16_t mag[3];		// Magnetic field in mGauss
	short dStatus[4];
	float pressure;		// pressure in hPa
	float press_diff; // Differential pressure in hPa
	int32_t height;		// pressure height in mm
	int32_t lon;			// Longitude in degE7
	int32_t lat;			// Latitude in degE7
	int32_t alt;			// Altitude in mm
	uint16_t eph;			// horizontal dilution of position (unitless * 100)
	uint16_t epv;			// GPS VDOP vertical dilution of position (unitless * 100).
	uint16_t vel;			// GPS ground speed in cm/s
	uint16_t yaw;			// Yaw in earth frame from north. cdeg
	uint8_t satellites_visible;
	float q[4];
};



void SensorGet(void* stcInfo, uint8_t infoType);
void SensorScaledGet(struct ScaledSensorStatus* dst);
void SensorSetFromBuffer(char ucRxBuffer[]);

uint8_t updateSensor(void);
void updateSensorClear(void);

bool isSensorInitlized(uint8_t type);
bool isSensorAllInitlized(void);

#endif
