#include "pid.h"
 
pid_struct GM6020_speed_pid;
pid_struct GM6020_angle_pid;

int Speed_I_Max=25000,Speed_Output_Max=25000;
int Angle_I_Max=0,Angle_Output_Max=320;

int Speed_Kp=20,Speed_Ki=10,Speed_Kd;
int Angle_Kp=2,Angle_Ki,Angle_Kd=2;//������(1~10)

void pid_set(pid_struct *pid,//����pid����
              float kp,
              float ki,
              float kd,
              float i_max,
              float out_max)
{
  pid->kp      = kp;
  pid->ki      = ki;
  pid->kd      = kd;
  pid->i_max   = i_max;
  pid->out_max = out_max;
}
 
 
float PID_Control(pid_struct *pid, float target, float current)//PID���㺯��
{
  pid->target = target;
  pid->current = current;
  pid->err[1] = pid->err[0];
  pid->err[0] = pid->target - pid->current;
  
  pid->p_out  = pid->kp * pid->err[0];
  pid->i_out += pid->ki * pid->err[0];
  pid->d_out  = pid->kd * (pid->err[0] - pid->err[1]);
	pid->i_out=(pid->i_out)>(pid->i_max)?(pid->i_max):((pid->i_out)<(-(pid->i_max))?(-(pid->i_max)):(pid->i_out));//�޷�
 
  pid->output = pid->p_out + pid->i_out + pid->d_out;
	pid->output=(pid->output)>(pid->out_max)?(pid->out_max):((pid->output)<(-(pid->out_max))?(-(pid->out_max)):(pid->output));//�޷�
  return pid->output;
}
 
void GM6020_PID_Set()//�ǶȻ����ٶȻ���PID��ʼ��,ֻ�ǳ����
{
	pid_set(&GM6020_speed_pid, Speed_Kp, Speed_Ki, Speed_Kd, Speed_I_Max, Speed_Output_Max);
	pid_set(&GM6020_angle_pid, Angle_Kp, Angle_Ki, Angle_Kd, Angle_I_Max, Angle_Output_Max);
}
