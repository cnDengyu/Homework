#include <math.h>
#include <string.h>
#include "matrix/matrix.h"
#include "sensor/sensor_status.h"
#include "./estimator.h"

static bool isInitlized = false;
static bool isLonLatInit = false;
static bool isAccInit = false;
static bool isHeightInit = false;

static bool isUpdate = false;
static bool isAltUpdate = false;
static bool isLonLatUpdate = false;

static const double pi = 3.1415926535;
// static const double g = 9.8;
static const double ReE7 = 0.6378;

static struct GlobalPositionInt pos;
static struct LocalPosition pos_loc;
static struct GlobalOrigin ori;
static uint32_t lastAccTime = 0;
static uint32_t lastHeiTime = 0;
static uint32_t lastGpsTime = 0;

/*		Kalman Filter 卡尔曼滤波
 *	
 *	Prediction:			预测方程
 *			x_pre = F*x + u
 *			P_pre = F*P*F' + Q
 *
 *	Measurement:		更新方程
 *			y = z - H*x_pre
 *			S = H*P_pre*H' + R
 *			K = P_pre*H'*S_inv
 * 			x = x_pre + K*y
 *			P = (I - K*H)*P_pre
*/
// 卡尔曼增益
static Matrix* P = NULL;
static Matrix* P_pre = NULL;
// 状态估计值
static Matrix* x = NULL;
static Matrix* x_pre = NULL;

// 状态估计器初始化
static void EstimatorInitlize(uint8_t type);
// 全球坐标到局部坐标
static int Global2Local(Matrix* dst_6_1, int32_t globalLon, int32_t globalLat, int32_t globalAlt);
// 箭体加速度到导航加速度
static int Acc2Local(Matrix* dst_6_1, int16_t a[], float q[], int16_t gyro[3], double vel[3]);
// Predict position when IMU updates			IMU更新时，位置更新
static void EstimatorPredict(void);
// Measure Altitude when Pressure updates	气压计更新时，位置更新
static void EstimatorMeasureAlt(void);
// Measure position when GPS updates			GPS更新时，位置更新
static void EstimatorMeasureLonLat(void);

static uint32_t lastTime;

void Estimator_Run(void)
{
	uint8_t sensorFlag = updateSensor();
	
	isUpdate = false;
	
	if(sensorFlag != 0x00)
	{
		if(isInitlized)
		{
			switch(sensorFlag)
			{
				// Since Acceleration is received first and Quartnion is received next
				// 传感器发送一次数据中，先发送加速度，后发送四元数。
				// 因此，需要等到四元数一同发送完毕才能得到有效的地面系加速度数据。
				case TYPE_Q:
					EstimatorPredict();
					break;
				
				case TYPE_PRESS:
					EstimatorMeasureAlt();
					break;
				
				case TYPE_LONLAT:
					EstimatorMeasureLonLat();
					break;
				
			}
		}else{
			EstimatorInitlize(sensorFlag);
		}
		isUpdate = true;
	}
}

bool updateEstimator()
{
	return isUpdate;
}

bool isEstimatorInitlized()
{
	return isInitlized;
}

/**
  * @brief  Initlize Value 赋初始值。
  * @param  type of Value 数值类型
  * @retval None
  */
static void EstimatorInitlize(uint8_t type)
{
	struct ScaledSensorStatus status;
	SensorScaledGet(&status);
	
	pos.vx = 0;
	pos.vy = 0;
	pos.vz = 0;
	
	switch(type)
	{
		case TYPE_LONLAT:
			pos.lon = status.lon;
			pos.lat = status.lat;
			pos.alt = status.alt;
			ori.lon = pos.lon;
			ori.lat = pos.lat;
			
			lastTime = status.timestamp;
			isLonLatInit = true;
			break;
		
		// Use Pressure but not GPS to measure altitude, 
		// precision of GPS height is very low.
		// 使用气压计读数而不是GPS读数来测量高度
		// 因为GPS高度精度非常低
		case TYPE_PRESS:
			pos.alt = status.height;
			ori.alt = pos.alt;
			
			isHeightInit = true;
			break;
		
		case TYPE_ACC:
			pos.vx = 0;
			pos.vy = 0;
			pos.vz = 0;
			isAccInit = true;
			break;
		
		default:
			return;
	}
	
	if(isSensorAllInitlized() && isLonLatInit && isHeightInit && isAccInit && (!isInitlized))
	{
		Global2Local(x, status.lon, status.lat, status.alt);
		lastAccTime = status.timestamp;
		lastHeiTime = status.timestamp;
		lastGpsTime = status.timestamp;
		isInitlized = true;
	}
}

void EstimatorGet(struct LocalPosition* dst)
{
	memcpy(dst, &pos_loc, sizeof(pos_loc));
}

// transfer Global Position into Local Position in NED
// 把全球坐标转换到局部坐标，北东地坐标系
static int Global2Local(Matrix* dst_6_1, int32_t globalLon, int32_t globalLat, int32_t globalAlt)
{
	if(dst_6_1->cols == 1 && dst_6_1->rows >= 3)
	{
		MatrixSetValue(dst_6_1, 1, 1, (globalLat - ori.lat)/180*pi*ReE7);
		MatrixSetValue(dst_6_1, 2, 1, (globalLon - ori.lon)/180*pi*ReE7);
		MatrixSetValue(dst_6_1, 3, 1, (ori.alt - globalAlt)/1000);
		return 0;
	}else{
		return -1;
	}
}

// transfer Body Acceleration into NED
// 把箭体加速度转换到北东地坐标系
static int Acc2Local(Matrix* dst_6_1, int16_t a[], float q[], int16_t gyro[3], double vel[3])
{
	unsigned int i=0;
	Matrix* a_body = NULL;	// 箭体参考系的加速度
	Matrix* T_B_N = NULL;		// 箭体坐标系到导航坐标系的转换阵
	Matrix* a_navaix = NULL;		// 箭体系的加速度在导航坐标系的投影
	Matrix* a_nav = NULL;		// 导航参考系（北东地）的加速度
	double a_body_temp[3] = {0,0,0};	// 临时变量
	Matrix* omega = NULL;				// 箭体系角速度矢量
	Matrix* omega_nav = NULL;		// 导航系角速度矢量
	Matrix* v = NULL;						// 导航系速度矢量
	Matrix* temp = NULL;
	
	if(dst_6_1->cols != 1 || dst_6_1->rows != 6)
	{
		return -1;
	}
	
	a_body = MatrixCreate(3,1);
	for(i=0; i<3; i++)
	{
		MatrixSetValue(a_body, i+1, 1, (double)a[i]/1000.0);
	}
	
	omega = MatrixCreate(3, 1);
	MatrixSetValue(omega, 1, 1, gyro[0]/1000.0);
	MatrixSetValue(omega, 2, 1, gyro[1]/1000.0);
	MatrixSetValue(omega, 3, 1, gyro[2]/1000.0);
	
	v = MatrixBuildFromArray(vel, 3, 1);
	
	/*	rotation matrix from XYZ body to NED navigation frame
	*	
	*		 N			q0^2+q1^2-q2^2-q3^2				2(q1q2-q0q3)								2(q1q3+q0q2)
	*		T		=		2(q1q2+q0q3)							q0^2-q1^2+q2^2-q3^2					2(q2q3-q0q1)
	*		 B			2(q1q3-q0q2)							2(q2q3+q0q1)								q0^2-q1^2-q2^2+q3^2	
	*/
	T_B_N = MatrixCreate(3,3);
	MatrixSetValue(T_B_N, 1, 1, (double)(q[0]*q[0] + q[1]*q[1] - q[2]*q[2] - q[3]*q[3]));
	MatrixSetValue(T_B_N, 2, 2, (double)(q[0]*q[0] - q[1]*q[1] + q[2]*q[2] - q[3]*q[3]));
	MatrixSetValue(T_B_N, 3, 3, (double)(q[0]*q[0] - q[1]*q[1] - q[2]*q[2] + q[3]*q[3]));
	MatrixSetValue(T_B_N, 1, 2, (double)(2*(q[1]*q[2]-q[0]*q[3])));
	MatrixSetValue(T_B_N, 1, 3, (double)(2*(q[1]*q[3]+q[0]*q[2])));
	MatrixSetValue(T_B_N, 2, 3, (double)(2*(q[2]*q[3]-q[0]*q[1])));
	MatrixSetValue(T_B_N, 2, 1, (double)(2*(q[1]*q[2]+q[0]*q[3])));
	MatrixSetValue(T_B_N, 3, 1, (double)(2*(q[1]*q[3]-q[0]*q[2])));
	MatrixSetValue(T_B_N, 3, 2, (double)(2*(q[2]*q[3]+q[0]*q[1])));
	
	// a_nav = T_B_N * a_body
	MatrixMultiply(T_B_N, a_body, &a_navaix);
	MatrixMultiply(T_B_N, omega, &omega_nav);
	
	MatrixCrossProduct(omega_nav, v, &temp);
	
	MatrixAdd(a_navaix, temp, &a_nav);
	
	// output
	for(i=0; i<3; i++)
	{
		MatrixGetValue(a_nav, i+1, 1, &a_body_temp[i]);
		MatrixSetValue(dst_6_1, i+1, i, a_body_temp[i]);
	}
	
	MatrixDelete(&temp);
	MatrixDelete(&v);
	MatrixDelete(&omega_nav);
	MatrixDelete(&omega);
	MatrixDelete(&a_navaix);
	MatrixDelete(&a_nav);
	MatrixDelete(&T_B_N);
	MatrixDelete(&a_body);
		
}

// Predict position when IMU updates
static void EstimatorPredict(void)
{
	unsigned int i=0;
	double tempvalue = 0;
	double dt;
	struct ScaledSensorStatus status;
	double v[3] = {0,0,0};
	
	Matrix* tempMatrix = NULL;
	Matrix* tempMatrix2 = NULL;
	Matrix* F_t = NULL;
	Matrix* Q = NULL;
	Matrix* u = NULL;
	Matrix* F = NULL;
	
	x = MatrixCreate(6,1);
	u = MatrixCreate(6,1);
	
	SensorScaledGet(&status);
	
	dt = (status.timestamp - lastAccTime) / 1000.0;
	lastAccTime = status.timestamp;
	
	// get Local Position
	
	// Global2Local(x, lastStatus.lon, lastStatus.lat, lastStatus.height);
	
	/*
	 * 	Predict Equation of x
	 *  状态预测方程
	 *
	 *	x_pre = F*x + u
	 *
	 *  		1		0		0		dt	0		0
	 *			0		1		0		0		dt	0
	 *	F=	0		0		1		0		0		dt
	 *  		0		0		0		1		0		0
	 *			0		0		0		0		1		0
	 *			0		0		0		0		0		1
	 *
	 *  		ax*dt^2/2
	 *			ay*dt^2/2
	 *	u=	az*dt^2/2
	 *  		ax*dt
	 *			ay*dt
	 *			az*dt
	 */
	// Set F
	F = MatrixCreateEye(6);
	for(i=1; i<=3; i++)
	{
		MatrixSetValue(F, i, i+3, dt);
	}
	
	v[0] = pos.vx;
	v[1] = pos.vy;
	v[2] = pos.vz;
	
	// Set u
	Acc2Local(u, status.a, status.q, status.gyro, v);
	for(i=1; i<=3; i++)
	{
		MatrixGetValue(u, i, 1, &tempvalue);
		MatrixSetValue(u, i, 1, tempvalue*dt*dt/2);
		MatrixGetValue(u, i+3, 1, &tempvalue);
		MatrixSetValue(u, i+3, 1, tempvalue*dt);
	}
	
	MatrixMultiply(F, x, &tempMatrix);
	MatrixAdd(tempMatrix, u, &x_pre);
	
	/*
	 *	Predict Equation of P
	 *	预测方程的协方差矩阵
	 *
	 *	P_pre = FPF' + Q
	 *
	 *			1		0		0		0		0		0
	 *			0		1		0		0		0		0
	 *  P0 =0		0		1		0		0		0
	 *			0		0		0		100	0		0
	 * 			0		0		0		0		100	0
	 * 			0		0		0		0		0		100
	 *
	 *	Q = eye(6)
	 *
	 */
	if(P == NULL)
	{
		P = MatrixCreateEye(6);
		MatrixSetValue(P, 4, 4, 100);
		MatrixSetValue(P, 5, 5, 100);
		MatrixSetValue(P, 6, 6, 100);
	}
	
	MatrixTransfer(F, &F_t);
	Q = MatrixCreateEye(6);
	MatrixMultiply(P, F_t, &tempMatrix);
	MatrixMultiply(F, tempMatrix, &tempMatrix2);
	MatrixAdd(tempMatrix2, Q, &P_pre);
	
	//output
	for(i=1; i<=3; i++)
	{
		MatrixGetValue(x_pre, i, 1, &pos_loc.pos[i]);
		MatrixGetValue(x_pre, i+3, 1, &pos_loc.vel[i+3]);
	}
	
	isUpdate = true;
	
	MatrixDelete(&F);
	MatrixDelete(&F_t);
	MatrixDelete(&tempMatrix2);
	MatrixDelete(&tempMatrix);
	MatrixDelete(&Q);
	MatrixDelete(&u);
}

// Measure Altitude when Pressure updates
static void EstimatorMeasureAlt(void)
{
	double dt;
	struct ScaledSensorStatus status;
	Matrix* y = NULL;
	Matrix* z = NULL;
	Matrix* H = NULL;
	Matrix* S = NULL;
	Matrix* H_t = NULL;
	Matrix* R = NULL;
	Matrix* K = NULL;
	Matrix* S_i = NULL;
	Matrix* I = NULL;
	Matrix* temp = NULL;
	Matrix* temp2 = NULL;
	
	SensorScaledGet(&status);
	dt = (status.timestamp - lastAccTime) / 1000.0;
	lastAccTime = status.timestamp;
	
/*	
 *	Measurement:
 *			y = z - H*x_pre
 *			S = H*P_pre*H' + R
 *			K = P_pre*H'*S_inv
 * 			x = x_pre + K*y
 *			P = (I - K*H)*P_pre
*/
	// y = z - H*x_pre
	z = MatrixCreate(1,1);
	MatrixSetValue(z, 1, 1, -status.height);
	
	H = MatrixCreate(1,6);
	MatrixSetZeros(H);
	MatrixSetValue(H, 1, 3, 1);
	
	MatrixMultiply(H, x_pre, &temp);
	MatrixMinus(z, temp, &y);
	
	//S = H*P_pre*H' + R
	MatrixTransfer(H, &H_t);
	MatrixMultiply(P_pre, H_t, &temp);
	MatrixMultiply(H, temp, &temp2);
	R = MatrixCreateEye(temp2->rows);
	MatrixAdd(temp2, R, &S);
	
	//K = P_pre*H'*S_inv
	MatrixInv(S, &S_i);
	MatrixMultiply(H_t, S_i, &temp);
	MatrixMultiply(P_pre, temp, &K);
	
	//x = x_pre + K*y
	MatrixMultiply(K, y, &temp);
	MatrixAdd(x_pre, temp, &x);
	
	//P = (I-KH)P_pre
	I = MatrixCreateEye(K->rows);
	MatrixMultiply(K, H, &temp);
	MatrixMinus(I, temp, &temp2);
	MatrixMultiply(temp2, P_pre, &P);
	
	MatrixGetValue(x, 3, 1, &pos_loc.pos[2]);
	
	isAltUpdate = true;
	
	MatrixDelete(&temp2);
	MatrixDelete(&temp);
	MatrixDelete(&I);
	MatrixDelete(&S_i);
	MatrixDelete(&K);
	MatrixDelete(&R);
	MatrixDelete(&H_t);
	MatrixDelete(&S);
	MatrixDelete(&H);
	MatrixDelete(&z);
	MatrixDelete(&y);
}

// Measure position when GPS updates
static void EstimatorMeasureLonLat(void)
{
	double dt;
	double tempvalue;
	struct ScaledSensorStatus status;
	Matrix* y = NULL;
	Matrix* z = NULL;
	Matrix* H = NULL;
	Matrix* S = NULL;
	Matrix* H_t = NULL;
	Matrix* R = NULL;
	Matrix* K = NULL;
	Matrix* S_i = NULL;
	Matrix* I = NULL;
	Matrix* temp = NULL;
	Matrix* temp2 = NULL;
	
	SensorScaledGet(&status);
	dt = (status.timestamp - lastGpsTime) / 1000.0;
	lastGpsTime = status.timestamp;
	
/*	
 *	Measurement:
 *			y = z - H*x_pre
 *			S = H*P_pre*H' + R
 *			K = P_pre*H'*S_inv
 * 			x = x_pre + K*y
 *			P = (I - K*H)*P_pre
*/
	
	// get z from status
	temp = MatrixCreate(3,1);
	Global2Local(temp, status.lon, status.lat, status.alt);
	z = MatrixCreate(2,1);
	MatrixGetValue(temp, 1, 1, &tempvalue);
	MatrixSetValue(z, 1, 1, tempvalue);
	MatrixGetValue(temp, 2, 1, &tempvalue);
	MatrixSetValue(z, 2, 1, tempvalue);
	MatrixDelete(&temp);
	
	// set measurement matrix
	H = MatrixCreate(1,6);
	MatrixSetZeros(H);
	MatrixSetValue(H, 1, 1, 1);
	MatrixSetValue(H, 1, 2, 1);
	
	// y = z - H*x_pre
	MatrixMultiply(H, x_pre, &temp);
	MatrixMinus(z, temp, &y);
	
	//S = H*P_pre*H' + R
	MatrixTransfer(H, &H_t);
	MatrixMultiply(P_pre, H_t, &temp);
	MatrixMultiply(H, temp, &temp2);
	R = MatrixCreateEye(temp2->rows);
	MatrixAdd(temp2, R, &S);
	
	//K = P_pre*H'*S_inv
	MatrixInv(S, &S_i);
	MatrixMultiply(H_t, S_i, &temp);
	MatrixMultiply(P_pre, temp, &K);
	
	//x = x_pre + K*y
	MatrixMultiply(K, y, &temp);
	MatrixAdd(x_pre, temp, &x);
	
	//P = (I-KH)P_pre
	I = MatrixCreateEye(K->rows);
	MatrixMultiply(K, H, &temp);
	MatrixMinus(I, temp, &temp2);
	MatrixMultiply(temp2, P_pre, &P);
	
	MatrixGetValue(x, 1, 1, &pos_loc.pos[0]);
	MatrixGetValue(x, 2, 1, &pos_loc.pos[1]);
	
	isLonLatUpdate = true;
	
	MatrixDelete(&temp2);
	MatrixDelete(&temp);
	MatrixDelete(&I);
	MatrixDelete(&S_i);
	MatrixDelete(&K);
	MatrixDelete(&R);
	MatrixDelete(&H_t);
	MatrixDelete(&S);
	MatrixDelete(&H);
	MatrixDelete(&z);
	MatrixDelete(&y);
}
