#ifndef __MOTOR_CAN_H
#define __MOTOR_CAN_H

#include "main.h"
#include "can.h"

typedef struct{
	uint16_t motor_id;//���ID
	int16_t Voltage;//��ѹֵ
	uint16_t Angle;//��е�Ƕ�
	int16_t Speed;//ת��
	int16_t Torque;//ʵ��Ť��
	uint8_t Temp;//�¶�
}motor_info_t;

void can_filter_init(void);
void Set_voltage(CAN_HandleTypeDef* hcan,int16_t v1otage);


#endif



