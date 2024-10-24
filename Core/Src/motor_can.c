#include "motor_can.h"

motor_info_t GM6020;

/*滤波器配置及can初始化*/
void can_filter_init(void)
{ 	
	

	CAN_FilterTypeDef can_filter_structure;
	can_filter_structure.FilterActivation = ENABLE;//使能滤波器
	can_filter_structure.FilterMode = CAN_FILTERMODE_IDMASK;//掩码模式
	can_filter_structure.FilterScale = CAN_FILTERSCALE_32BIT;
	can_filter_structure.FilterIdHigh = 0x0000;//下面配置则不筛选ID
	can_filter_structure.FilterIdLow = 0x0000;
	can_filter_structure.FilterMaskIdHigh = 0x0000;
	can_filter_structure.FilterMaskIdLow = 0x0000;
	can_filter_structure.FilterBank = 0;
	can_filter_structure.FilterFIFOAssignment = CAN_RX_FIFO0;//使用FIFO0
	HAL_CAN_ConfigFilter(&hcan1, &can_filter_structure);
	
	HAL_CAN_Start(&hcan1);
	HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);//使能中断

}

/*设置电机电压*/
void Set_voltage(CAN_HandleTypeDef* hcan,int16_t v1otage)
{
  CAN_TxHeaderTypeDef tx_header;
  uint8_t             tx_data[8] = {0};
    
  tx_header.StdId = 0x1ff;
  tx_header.IDE   = CAN_ID_STD;//标准ID
  tx_header.RTR   = CAN_RTR_DATA;//数据帧
  tx_header.DLC   = 8;//数据长度
 
  tx_data[2] = (v1otage>>8)&0xff;//电机拨码开关ID为2
  tx_data[3] = (v1otage)&0xff;
	 
  HAL_CAN_AddTxMessage(&hcan1, &tx_header, tx_data,(uint32_t*)CAN_TX_MAILBOX0);//发送报文
}

//接收中断回调函数
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
  CAN_RxHeaderTypeDef rx_header;
  uint8_t             rx_data[8];
  if(hcan==&hcan1)
  {
		HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, rx_data); //接收报文
		if(rx_header.StdId==0x206){
			GM6020.Angle= ((rx_data[0] << 8) | rx_data[1]);
			GM6020.Speed= ((rx_data[2] << 8) | rx_data[3]);
			GM6020.Torque=((rx_data[4] << 8) | rx_data[5]);
			GM6020.Temp=rx_data[6];
		}
	}
}
