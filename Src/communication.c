#include "communication.h"
#include "usart.h"
#include "tracking.h"
#include "room_search.h"
#include "settlement.h"
#include "joint.h"


uint8_t buffer[3]={0};
uint8_t bufferMV[3]={0};

uint8_t Run_Judge=0;
uint8_t Mv_Message=0;
uint8_t Number1_flag;

extern unsigned short as[3];
unsigned short bs[3];

void Communication_Init(void)
{
 //HAL_UART_Receive_DMA(&huart1,buffer,3);
 __HAL_UART_ENABLE_IT(&huart1,UART_IT_IDLE);
}

void Communication_Judge_Nano(void)
{
if(as[0]==236) Run_Judge=5;//�����־λȫ������
if(as[0]==108) Run_Judge=4;//ʰȡ����������������
if(as[0]==239) Run_Judge=3;//ʰȡ3�ŷ��� 690��
if(as[0]==238) Run_Judge=2;//ʰȡ2�ŷ��� 485��
if(as[0]==237) Run_Judge=1;//ʰȡ1�ŷ��� 231��
if(as[0]==255) Run_Judge=0;//ֹͣ�������г���
}

void Communication_Jude_Mv(void)
{
if(bs[0]==237) 
{
	Mv_Message=1;//1�ŷ���  231�����  bs[0]=108��ԭʼ��
  bs[0]=0;
}
if(bs[0]==238) 
{
	Mv_Message=2;//2�ŷ���  485�����  bs[0]=173(
	bs[0]=0;
}
if(bs[0]==239) 
{
	Mv_Message=3;//3�ŷ���  690�����
  bs[0]=0;
}
if(bs[0]==236) 
{
	Mv_Message=4;//����
  bs[0]=0;
 }
}

void Search_Room_Reset(void)
{
	
 Room_Search_MODE=1;
 Turn_back_MODE=1;
	
 Rx_Flag_Reset2=0;
 Turn_Back_Flag=0;

 Display_Settlement_time2=1;
 Settlement_Flag_Init2();
 Settlement_Flag_Init3();
 Switch_Mode_Cnt2=0;
 Switch_Mode_Cnt3=0;
	
 Joint_time=0;
 HAL_GPIO_WritePin(GPIOE,GPIO_PIN_13,GPIO_PIN_RESET);//�ر�����
 Joint_Normal();
}

