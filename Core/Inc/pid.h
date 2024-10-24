#ifndef __PID_H_
#define __PID_H_
 
#include "main.h"
#include "stm32f4xx.h"
 
typedef struct 
{
  float kp;//����
  float ki;//����
  float kd;//΢��
  float i_max;//�����޷�
  float out_max;//����޷�
  
  float target;      // Ŀ��Ƕ�
  float current;      // ��ǰ�Ƕ�
  float err[2];   // error and last error��ֵ
 
  float p_out;//�������
  float i_out;//�������
  float d_out;//΢�����
  float output;//pid�����
}pid_struct;
 
 
void GM6020_PID_Set(void);
float PID_Control(pid_struct *pid, float ref, float fdb);
 
#endif
