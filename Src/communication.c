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
if(as[0]==236) Run_Judge=5;//房间标志位全部清零
if(as[0]==108) Run_Judge=4;//拾取所有垃圾程序运行
if(as[0]==239) Run_Judge=3;//拾取3号房间 690号
if(as[0]==238) Run_Judge=2;//拾取2号房间 485号
if(as[0]==237) Run_Judge=1;//拾取1号房间 231号
if(as[0]==255) Run_Judge=0;//停止运行所有程序
}

void Communication_Jude_Mv(void)
{
if(bs[0]==237) 
{
	Mv_Message=1;//1号房间  231房间号  bs[0]=108（原始）
  bs[0]=0;
}
if(bs[0]==238) 
{
	Mv_Message=2;//2号房间  485房间号  bs[0]=173(
	bs[0]=0;
}
if(bs[0]==239) 
{
	Mv_Message=3;//3号房间  690房间号
  bs[0]=0;
}
if(bs[0]==236) 
{
	Mv_Message=4;//环境
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
 HAL_GPIO_WritePin(GPIOE,GPIO_PIN_13,GPIO_PIN_RESET);//关闭消毒
 Joint_Normal();
}

