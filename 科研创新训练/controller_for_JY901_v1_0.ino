/*------------------------------------
 * 科研创新训练：水火箭控制系统
 * 时间：2021.10.19
 * 版本：1.0
 * 作者：章登宇
 *------------------------------------*/
#include <Wire.h>
#include <Servo.h>
#include <MsTimer2.h>
#include <JY901.h>

/*
 * 第一部分：参数定义
 * 包括：
 * 1.1 舵面校准量
 * 1.2 普适常量
 * 1.3 箭体参数
 * 1.4 状态变量
 * 1.5 姿态控制参数
 * 1.6 时序控制参数
 */
// 1.1 舵面校准
// 1.1.1 舵面起始角
#define START_POSITION 90
// 1.1.2 四个舵面的校准量
#define S1_R 5
#define S2_R 5
#define S3_R 5
#define S4_R 2
// 1.1.3 计算各个舵面总的初始角
const double start_position[4] = {START_POSITION + S1_R,
                                  START_POSITION + S2_R,
                                  START_POSITION + S3_R,
                                  START_POSITION + S4_R
                                 };
// 1.2 普适常量
// 1.2.1 圆周率
const double pi = 3.1415926535;
// 1.2.2 大气密度
const double rho = 1.293;
// 1.2.3 重力加速度
const double g = 9.8;

// 1.3 箭体参数
// 1.3.1 舵面中心的质心距
const double d2 = 0.170;
const double d1 = 0.105;
// 1.3.2 舵面面积
const double aera = 0.0019982143;
// 1.3.3 全箭总长
const double rocket_length = 0.410;
// 1.3.4 箭体质量
const double rocket_mass = 0.3443;
// 1.3.5 转动惯量
// 暂时使用匀质杆模型
const double rocket_J = 1 / 12 * rocket_mass * rocket_length * rocket_length;

// 1.4 状态参数
// 状态参数是指随火箭运行而变化的变量
// 1.4.1 全局速度变量（z轴）
double g_v = 0;
// 1.4.2 全局时间变量（毫秒）
unsigned long g_time = 0;
// 1.4.3 舵机对象
Servo s1, s2, s3, s4, parachute;
// 1.4.4 传感器有新信息的状态标志
bool flag = false;
// 1.4.5 全局时序状态
unsigned int time_state = 0;

// 1.5 姿态控制参数
// 1.5.1 最小速度：当箭体速度低于此值时，按照此值计算控制参数
#define V_MIN 10.0
// 1.5.2 控制系统的预期调节时间
const double t_s = 4;
// 1.5.3 控制系统的开环增益
const double K_r = 0.800;
// const double K_r = 0;
// 1.5.4 控制系统的位置反馈系数（参考值）
const double Kp_r = 1;
// 1.5.5 控制系统的速度反馈系数（参考值）
const double Kc_r = 0.6667;
// 1.5.6 轴向开环增益（参考值）
const double Kr_r = 0.0370;
// const double Kr_r = 1;

// 1.6 时序控制参数
// 定义时序控制触发条件
#ifdef TEST
// 1.6.1 时序触发速度（测试）
#define V_TIMER 1.0
// 1.6.2 时序触发加速度（测试）
#define A_TIMER (-1*g)
#else
// 1.6.1 时序触发速度（实飞）
#define V_TIMER 10.0
// 1.6.2 时序触发加速度（实飞）
#define A_TIMER (2*g)
#endif

/*
 * 第二部分：程序函数
 */
// 2.1 初始化函数
// 设备上电时，执行一次本函数
void setup() {
  // 2.1.1 GPIO引脚初始化
  // 初始化指示灯引脚
  pinMode(13, OUTPUT);
  // 设置2号引脚为输入模式
  pinMode(2, INPUT);

  // 2.1.2 舵机引脚初始化
  // 舵面控制连接到12~9引脚
  s1.attach(12);
  s2.attach(8);
  s3.attach(9);
  s4.attach(7);
  parachute.attach(11);

  // 2.1.3 设置舵机初始位置
  parachute.write(90);
  s1.write(start_position[0]);
  s2.write(start_position[1]);
  s3.write(start_position[2]);
  s4.write(start_position[3]);

  // 2.1.4 启动串口，接收传感器信息
  Serial.begin(115200);
}

// 2.2 循环函数
// 本函数在初始化函数执行一次后，会无休止地重复执行。
void loop() {
  // 2.2.1 定义临时变量
  // 2.2.1.1 舵偏角控制量
  double angle1 = 0, angle2 = 0, angle3 = 0, angle4 = 0;
  // 2.2.1.2 箭体倾角
  double angle[3];
  // 2.2.1.3 箭体角速度
  double omega[3] = {0, 0, 0};
  // 2.2.1.4 等效舵偏角控制量
  double theta_x = 0, theta_y = 0, theta_z = 0;
  // 2.2.1.5 时间差分：上次运行时间
  static unsigned long last_time = 0;
  // 2.2.1.6 时间差分：本次运行时间
  unsigned long this_time = 0;
  // 2.2.1.7 z方向相对加速度和绝对加速度
  static double a_z = 0, a_r = 0;
  // 2.2.1.8 最大控制角
  double max_angle = 0;
  // 2.2.1.9 45°角对应的弧度
  const double phi45 = 45.0 / 180.0 * pi;
  // 2.2.1.10 控制参数
  double Kp = Kp_r, Kc = Kc_r, K = K_r, Kr = Kr_r;
  // 2.2.1.11 Cotex积分计步
  // static unsigned int integrate_step = 0;
  // 2.2.1.12 Cotex积分参数
  // static double integrate_data[5] = {0,0,0,0};

  // 2.2.2 时序控制：
  // 如果z方向加速度大于指定值，则启动计时，并点亮指示灯
    if (time_state == 0) {
      if ( a_z > A_TIMER ) { // && g_v > V_TIMER
        // 启用定时器，在指定毫秒数后调用开伞函数（2.3）
        MsTimer2::set(1320, openParachute);
        MsTimer2::start();
        // 调整全局时序标记
        time_state = 1;
        // 点亮指示灯
        digitalWrite(13, HIGH);
      } 
      // 速度小于特定负值，也点亮指示灯
      else if ( g_v < -V_TIMER) {
        digitalWrite(13, HIGH);
      } else if (g_v < V_TIMER) {
        digitalWrite(13, LOW);
      }
    }

  // 2.2.3 处理串口信息
  // 如果有新的串口信息，则执行if内的代码。
  if (flag) {
    // 2.2.3.1 从传感器中读取角度和角速度
    angle[0] = (float)JY901.stcAngle.Angle[0] / 32768 * 180;
    angle[1] = (float)JY901.stcAngle.Angle[1] / 32768 * 180;
    angle[2] = (float)JY901.stcAngle.Angle[2] / 32768 * 180;
    omega[0] = (float)JY901.stcGyro.w[0] / 32768 * 2000;
    omega[1] = (float)JY901.stcGyro.w[1] / 32768 * 2000;
    omega[2] = (float)JY901.stcGyro.w[2] / 32768 * 2000;

    // 2.2.3.2 读取z方向加速度并积分得到z方向速度
    a_r = (float)JY901.stcAcc.a[2] / 32768 * 16;
    a_z = (a_r - cos(angle[0] * pi / 180)*cos(angle[1] * pi / 180)) * g;
    
    // 2.2.3.3 使用 Cotex 公式积分
    /*
    switch(integrate_step){
      case 0:
        // last_time = JY901.stcTime.ucHour * 3600 * 1000 + JY901.stcTime.ucMinute * 60 * 1000 + JY901.stcTime.ucSecond * 1000+JY901.stcTime.usMiliSecond;
        last_time = g_time;
      case 1:
      case 2:
      case 3:
        integrate_data[integrate_step] = a_z;
        integrate_step ++;
        break;
      case 4:
        // this_time = JY901.stcTime.ucHour * 3600 * 1000 + JY901.stcTime.ucMinute * 60 * 1000 + JY901.stcTime.ucSecond * 1000+JY901.stcTime.usMiliSecond;;
        this_time = g_time;
        integrate_data[integrate_step] = a_z;
        g_v += (float)(this_time - last_time)/90000* \
          (7*integrate_data[0]+ \
          32*integrate_data[1]+ \
          12*integrate_data[2]+ \
          32*integrate_data[3]+ \
          7*integrate_data[4]);
        last_time = this_time;
        integrate_data[0] = a_z;
        integrate_step = 1;
        break;
      default:break;
    }
*/

    // 2.2.3.3 矩形公式积分
    if (last_time != 0 && time_state == 1) {
      this_time = g_time;
      g_v = g_v + (float)(this_time - last_time) / 1000 * a_z;
      last_time = this_time;
    }else{
      last_time = g_time;
    }

    // 2.2.3.4 随z方向速度平方反比调整开环增益
    if (g_v > V_MIN) {
        K = K_r * V_MIN * V_MIN / g_v / g_v;
        Kr = Kr_r * V_MIN * V_MIN / g_v / g_v;
      }

    // 2.2.3.5 比例-微分控制，得到所需等效舵偏角
    theta_x = (-Kp * angle[0] - Kc * omega[0]) * K;
    theta_y = (-Kp * angle[1] - Kc * omega[1]) * K;
    theta_z = (- Kc * omega[2]) * Kr;

    // 2.2.3.5 控制量分配到四个舵面
    angle1 = theta_y / 2 + theta_z/4;
    angle2 = theta_x / 2 + theta_z/4;
    angle3 = -theta_y / 2 + theta_z/4;
    angle4 = -theta_x / 2 + theta_z/4;
    
    // 2.2.3.6 控制角换算成弧度制
    angle1 = angle1 * pi / 180;
    angle2 = angle2 * pi / 180;
    angle3 = angle3 * pi / 180;
    angle4 = angle4 * pi / 180;

    // 2.2.3.7 控制角约束，最大45°
    max_angle = max(max(abs(angle1),abs(angle2)),max(abs(angle3),abs(angle4)));
    if (max_angle > (phi45 * phi45)) {
      angle1 = angle1 / max_angle * phi45 * phi45;
      angle2 = angle2 / max_angle * phi45 * phi45;
      angle3 = angle3 / max_angle * phi45 * phi45;
      angle4 = angle4 / max_angle * phi45 * phi45;
    }

    // 2.2.3.8 非线性环节:绝对开方
    angle1 = abssqrt(angle1);
    angle2 = abssqrt(angle2);
    angle3 = abssqrt(angle3);
    angle4 = abssqrt(angle4);

    // 2.2.3.9 换算回角度制
    angle1 = angle1 / pi * 180;
    angle2 = angle2 / pi * 180;
    angle3 = angle3 / pi * 180;
    angle4 = angle4 / pi * 180;

    // 2.2.3.10 写入角度到舵机
    s1.write(start_position[0] + angle1);
    s2.write(start_position[1] + angle2);
    s3.write(start_position[2] + angle3);
    s4.write(start_position[3] + angle4);

    // 2.2.4 重置串口标记
    flag = false;
  }
}

// 2.3 时序控制函数：开启降落伞
void openParachute()
{
  // 关闭定时器
  MsTimer2::stop();
  parachute.write(180);
  // 全局时序标记
  time_state = 2;
}

// 2.4 数学函数：绝对开方
double abssqrt(double angle)
{
  if (angle < 0) {
    return -sqrt(-angle);
  } else {
    return sqrt(angle);
  }
}

// 2.5 串口事件处理函数
// 这个函数会在每两次循环函数（2.2）之间执行
// 读取传感器数据，修改自JY901库
void serialEvent() {
  static unsigned char ucRxBuffer[250];
  static unsigned char ucRxCnt = 0;
  unsigned char ucData;
  while (Serial.available())
  {
    ucData = Serial.read();
    ucRxBuffer[ucRxCnt++] = ucData;
    if (ucRxBuffer[0] != 0x55)
    {
      ucRxCnt = 0;
      return;
    }
    if (ucRxCnt < 11) {
      return;
    }
    else
    {
      switch (ucRxBuffer[1])
      {
        case 0x50:  memcpy(&(JY901.stcTime), &ucRxBuffer[2], 8); break;
        case 0x51:  memcpy(&(JY901.stcAcc), &ucRxBuffer[2], 8); break;
        case 0x52:  memcpy(&(JY901.stcGyro), &ucRxBuffer[2], 8); break;
        case 0x53:  memcpy(&(JY901.stcAngle), &ucRxBuffer[2], 8); break;
        case 0x54:  memcpy(&(JY901.stcMag), &ucRxBuffer[2], 8); break;
        case 0x55:  memcpy(&(JY901.stcDStatus), &ucRxBuffer[2], 8); break;
        case 0x56:  memcpy(&(JY901.stcPress), &ucRxBuffer[2], 8); break;
        case 0x57:  memcpy(&(JY901.stcLonLat), &ucRxBuffer[2], 8); break;
        case 0x58:  memcpy(&(JY901.stcGPSV), &ucRxBuffer[2], 8); break;
      }
      ucRxCnt = 0;
      // 记录信号时间
      g_time = millis();
      // 串口标记
      flag = true;
      break;
    }
  }
}
