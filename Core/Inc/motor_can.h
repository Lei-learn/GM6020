#ifndef __MOTOR_CAN_H
#define __MOTOR_CAN_H

#include "main.h"
#include "can.h"

typedef struct{
	uint16_t motor_id;//电机ID
	int16_t Voltage;//电压值
	uint16_t Angle;//机械角度
	int16_t Speed;//转速
	int16_t Torque;//实际扭矩
	uint8_t Temp;//温度
}motor_info_t;

void can_filter_init(void);
void Set_voltage(CAN_HandleTypeDef* hcan,int16_t v1otage);


#endif



