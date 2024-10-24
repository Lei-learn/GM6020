#include "motor_can.h"

motor_info_t GM6020;

/*�˲������ü�can��ʼ��*/
void can_filter_init(void)
{ 	
	

	CAN_FilterTypeDef can_filter_structure;
	can_filter_structure.FilterActivation = ENABLE;//ʹ���˲���
	can_filter_structure.FilterMode = CAN_FILTERMODE_IDMASK;//����ģʽ
	can_filter_structure.FilterScale = CAN_FILTERSCALE_32BIT;
	can_filter_structure.FilterIdHigh = 0x0000;//����������ɸѡID
	can_filter_structure.FilterIdLow = 0x0000;
	can_filter_structure.FilterMaskIdHigh = 0x0000;
	can_filter_structure.FilterMaskIdLow = 0x0000;
	can_filter_structure.FilterBank = 0;
	can_filter_structure.FilterFIFOAssignment = CAN_RX_FIFO0;//ʹ��FIFO0
	HAL_CAN_ConfigFilter(&hcan1, &can_filter_structure);
	
	HAL_CAN_Start(&hcan1);
	HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);//ʹ���ж�

}

/*���õ����ѹ*/
void Set_voltage(CAN_HandleTypeDef* hcan,int16_t v1otage)
{
  CAN_TxHeaderTypeDef tx_header;
  uint8_t             tx_data[8] = {0};
    
  tx_header.StdId = 0x1ff;
  tx_header.IDE   = CAN_ID_STD;//��׼ID
  tx_header.RTR   = CAN_RTR_DATA;//����֡
  tx_header.DLC   = 8;//���ݳ���
 
  tx_data[2] = (v1otage>>8)&0xff;//������뿪��IDΪ2
  tx_data[3] = (v1otage)&0xff;
	 
  HAL_CAN_AddTxMessage(&hcan1, &tx_header, tx_data,(uint32_t*)CAN_TX_MAILBOX0);//���ͱ���
}

//�����жϻص�����
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
  CAN_RxHeaderTypeDef rx_header;
  uint8_t             rx_data[8];
  if(hcan==&hcan1)
  {
		HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, rx_data); //���ձ���
		if(rx_header.StdId==0x206){
			GM6020.Angle= ((rx_data[0] << 8) | rx_data[1]);
			GM6020.Speed= ((rx_data[2] << 8) | rx_data[3]);
			GM6020.Torque=((rx_data[4] << 8) | rx_data[5]);
			GM6020.Temp=rx_data[6];
		}
	}
}
