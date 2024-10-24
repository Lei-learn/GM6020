#ifndef __PID_H_
#define __PID_H_
 
#include "main.h"
#include "stm32f4xx.h"
 
typedef struct 
{
  float kp;//比例
  float ki;//积分
  float kd;//微分
  float i_max;//积分限幅
  float out_max;//输出限幅
  
  float target;      // 目标角度
  float current;      // 当前角度
  float err[2];   // error and last error差值
 
  float p_out;//比例输出
  float i_out;//积分输出
  float d_out;//微分输出
  float output;//pid总输出
}pid_struct;
 
 
void GM6020_PID_Set(void);
float PID_Control(pid_struct *pid, float ref, float fdb);
 
#endif
