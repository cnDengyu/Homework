#include "mavlink/common/mavlink.h"
#include "./message_system.h"
#include "sensor/sensor_status.h"
#include "core/timer.h"
#include "core/usart.h"
#include "./message_sensor.h"


static void MessageIMUSender(void);
static void MessagePressureSender(void);
static void MessageAttitudeSender(void);
static void MessageQuaternionSender(void);
static void MessageGPSIntSender(void);

void MessageSensorSender(void)
{
	uint8_t flag = SensorRefreshed();
	
	if(flag != 0)
	{
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, 0);
	
		switch(flag)
		{
		
			case TYPE_TIME:
				break;
		
			case TYPE_ACC:
			case TYPE_MAG:
				MessageIMUSender();
				break;
			
			case TYPE_GYRO:
				// MessageIMUSender();
				MessageAttitudeSender();
				// MessageQuaternionSender();
				break;

			case TYPE_ANGLE:
				MessageAttitudeSender();
				break;

			case TYPE_DSTATUS:
				break;
		
			case TYPE_PRESS:
				MessagePressureSender();
				break;
		
			case TYPE_LONLAT:
			// case TYPE_GPSV:
				MessageGPSIntSender();
				break;
		
			case TYPE_Q:
				MessageQuaternionSender();
				break;
		}
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, 1);
		// SensorReaded();
	}
	
}

static void MessageIMUSender(void)
{
	mavlink_scaled_imu_t imu;
	mavlink_message_t msg;
	uint8_t buffer[USART_MAX_BUFFER];
	uint16_t len;
	struct ScaledSensorStatus status;
	
	if(isSensorInitlized(TYPE_ACC) && \
		isSensorInitlized(TYPE_GYRO) && \
		isSensorInitlized(TYPE_MAG))
	{
		
		SensorScaledGet(&status);
		
		imu.time_boot_ms = GetBootTimeMs();
		imu.xacc = status.a[0];
		imu.yacc = status.a[1];
		imu.zacc = status.a[2];
		imu.xgyro = status.gyro[0];
		imu.ygyro = status.gyro[1];
		imu.zgyro = status.gyro[2];
		imu.xmag = status.mag[0];
		imu.ymag = status.mag[1];
		imu.zmag = status.mag[2];
		imu.temperature = status.T;
		
		mavlink_msg_scaled_imu_encode(mavlink_system.sysid, mavlink_system.compid, &msg, &imu);
		len = mavlink_msg_to_send_buffer(buffer, &msg);
		USARTc_SendBuffer(buffer, len);
		
	}
	
}

static void MessagePressureSender(void)
{
	mavlink_scaled_pressure_t pressure;
	mavlink_message_t msg;
	uint8_t buffer[USART_MAX_BUFFER];
	uint16_t len;
	struct ScaledSensorStatus status;
	
	// ensure temperature data
	if(isSensorInitlized(TYPE_ACC) | isSensorInitlized(TYPE_GYRO) | isSensorInitlized(TYPE_MAG))
	{
		
		SensorScaledGet(&status);
		
		pressure.time_boot_ms = GetBootTimeMs();
		pressure.press_abs = status.pressure;
		pressure.press_diff = status.press_diff;
		pressure.temperature = status.T;
		pressure.temperature_press_diff = 0;
		
		mavlink_msg_scaled_pressure_encode(mavlink_system.sysid, mavlink_system.compid, &msg, &pressure);
		len = mavlink_msg_to_send_buffer(buffer, &msg);
		USARTc_SendBuffer(buffer, len);
		
	}
	
}

static void MessageAttitudeSender(void)
{
	mavlink_attitude_t att;
	mavlink_message_t msg;
	uint8_t buffer[USART_MAX_BUFFER];
	uint16_t len;
	struct ScaledSensorStatus status;
	
	if(isSensorInitlized(TYPE_ANGLE) && \
		isSensorInitlized(TYPE_GYRO))
	{
		
		SensorScaledGet(&status);
		
		att.time_boot_ms = GetBootTimeMs();
		att.roll = status.angle[0];
		att.pitch = status.angle[1];
		att.yaw = status.angle[2];
		att.rollspeed = status.w[0];
		att.pitchspeed = status.w[1];
		att.yawspeed = status.w[2];
		
		mavlink_msg_attitude_encode(mavlink_system.sysid, mavlink_system.compid, &msg, &att);
		len = mavlink_msg_to_send_buffer(buffer, &msg);
		USARTc_SendBuffer(buffer, len);
		
	}
}

static void MessageQuaternionSender(void)
{
	mavlink_attitude_quaternion_t qua;
	mavlink_message_t msg;
	uint8_t buffer[USART_MAX_BUFFER];
	uint16_t len;
	struct ScaledSensorStatus status;
	
	if(isSensorInitlized(TYPE_Q) && \
		isSensorInitlized(TYPE_GYRO))
	{
		
		SensorScaledGet(&status);
		
		qua.time_boot_ms = GetBootTimeMs();
		qua.q1 = status.q[0];
		qua.q2 = status.q[1];
		qua.q3 = status.q[2];
		qua.q4 = status.q[3];
		qua.rollspeed = status.w[0];
		qua.pitchspeed = status.w[1];
		qua.yawspeed = status.w[2];
		qua.repr_offset_q[0] = 0;
		qua.repr_offset_q[1] = 0;
		qua.repr_offset_q[2] = 0;
		qua.repr_offset_q[3] = 0;
		
	}
}

static void MessageGPSIntSender(void)
{
	mavlink_gps_raw_int_t gps;
	mavlink_message_t msg;
	uint8_t buffer[USART_MAX_BUFFER];
	uint16_t len;
	struct ScaledSensorStatus status;
	
	if(isSensorInitlized(TYPE_LONLAT) && \
		isSensorInitlized(TYPE_GPSV))
	{
		
		SensorScaledGet(&status);
		
		gps.time_usec = GetBootTimeMs();
		gps.fix_type = GPS_FIX_TYPE_3D_FIX;
		gps.lat = status.lat;
		gps.lon = status.lon;
		gps.alt = status.alt;
		gps.eph = status.eph;
		gps.epv = status.epv;
		gps.cog = UINT16_MAX;
		gps.yaw = status.yaw;
		gps.satellites_visible = status.satellites_visible;
		gps.alt_ellipsoid = status.lon;
		gps.vel = status.vel;
		gps.h_acc = 500;
		gps.v_acc = 500;
		gps.vel_acc = 500;
		gps.hdg_acc = 500;
		
		mavlink_msg_gps_raw_int_encode(mavlink_system.sysid, mavlink_system.compid, &msg, &gps);
		len = mavlink_msg_to_send_buffer(buffer, &msg);
		USARTc_SendBuffer(buffer, len);
		
	}
}

