#include "tracking.h"
#include "gpio.h"
#include "chassis.h"
#include "mode.h"
#include "settlement.h"
#include "communication.h"
#include "room_search.h"


#define car_forward_speed 15
#define car_turn_right1_L 20
#define car_turn_right2_L 20
#define car_turn_right3_L 23
#define car_turn_right4_L 20
#define car_turn_right1_R 18
#define car_turn_right2_R 15
#define car_turn_right3_R 0
#define car_turn_right4_R -15


#define car_turn_left1_L 18
#define car_turn_left2_L 15
#define car_turn_left3_L 0
#define car_turn_left4_L -15
#define car_turn_left1_R 20
#define car_turn_left2_R 20
#define car_turn_left3_R 23
#define car_turn_left4_R 10


//#define  OpenMV_Open  HAL_UART_Transmit(&huart3,(uint8_t*)"555",3,0xfff);



extern UART_HandleTypeDef huart3;
int tracking[8];
void Read_GPIO(void)
{
   tracking[7]=HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_1);
	 tracking[6]=HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_0);
	 tracking[5]=HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_3);
	 tracking[4]=HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_2);
	 tracking[3]=HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_5);
	 tracking[2]=HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_4);
	 tracking[1]=HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_7);
	 tracking[0]=HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_6);
}


 void Tracking_Move(void)
 {
   if((tracking[0]|tracking[7])==1)
	 {
	  if(tracking[0]==1)
		{	
      if(tracking[7]==1) Car_Forward(car_forward_speed);
      else Car_Turn(car_turn_left4_L,car_turn_left4_R);
		}
	  else Car_Turn(car_turn_right4_L,car_turn_right4_R);
	 }
	 else
	 {
	  if((tracking[1]|tracking[6])==1)
	  {
	   if(tracking[1]==1)
		 {	
      if(tracking[6]==1) Car_Forward(car_forward_speed);
      else Car_Turn(car_turn_left3_L,car_turn_left3_R);
		 }
	   else Car_Turn(car_turn_right3_L,car_turn_right3_R);
	  }
		else
		{
		 if((tracking[2]|tracking[5])==1)
	   {
	    if(tracking[2]==1)
		  {	
       if(tracking[5]==1) Car_Forward(car_forward_speed);
       else Car_Turn(car_turn_left2_L,car_turn_left2_R);
		  }
	    else Car_Turn(car_turn_right2_L,car_turn_right2_R);
	   }
		 else
		 {
		 	if((tracking[3]|tracking[4])==1)
	    {
	     if(tracking[3]==1)
		   {	
        if(tracking[4]==1) Car_Forward(car_forward_speed);
        else Car_Turn(car_turn_left1_L,car_turn_left1_R);
		   }
	     else Car_Turn(car_turn_right1_L,car_turn_right1_R);
		  }
			else
			{
			Car_Forward(0);
			}	
		 }
	  }
  }
}
 

int Tx_cnt=0;//发送次数累计
int car_out=0;//无黑线计数变量
void Tracking_Switch_Mode(void)
{
 if((tracking[0]||tracking[1]||tracking[2]||tracking[3]||tracking[4]||tracking[5]||tracking[6]||tracking[7])==0)
 {
 car_out++;
 }
 if(car_out>80)//单位5ms， 0.4s执行一次
 {
  car_out=0;
	 if(Display_Settlement_time==4)
	 {
	  ELECTRONIC_CAR_MODE=3;
	 }
	 else
	 {
		Tx_cnt++;
	  HAL_UART_Transmit(&huart3,(uint8_t*)"555",3,0xfff);
    if(Tx_cnt>5)
    {	
     ELECTRONIC_CAR_MODE=2;
		 Tx_cnt=0;
    }
	 }
 }
}


int car_out_flag=0; //保证0.4s后再进行房间号判断的标志位
int car_out2=0;//出线计数
int Rx_Flag_Reset2=0;//数据清零判断位，0为未清零，1为已清零
void Tracking_Switch_Mode2(void)
{
 if((tracking[0]||tracking[1]||tracking[2]||tracking[3]||tracking[4]||tracking[5]||tracking[6]||tracking[7])==0)
 {
  car_out2++;
 }
 if(car_out2>80)//单位5ms, 0.4s执行一次
 {
	if(Rx_Flag_Reset2==0)
	{
	 Rx_Flag_Reset2=1;
	 Mv_Message=0;
	 car_out_flag=1;
	}
	 HAL_UART_Transmit(&huart3,(uint8_t*)"555",3,0xfff);
	 car_out2=0;
 }
 if(car_out_flag==1)
 {
  if(Mv_Message==0||Mv_Message==4&Display_Settlement_time2!=3)
	{
		
	}
	else
	{
	 if(Mv_Message==Run_Judge||Display_Settlement_time2==3)
	 {
		 Turn_Back_Flag=1;
		 Rx_Flag_Reset2=0;
		 car_out_flag=0;
	 }
	 else
	 {
		Room_Search_MODE=2;
		Rx_Flag_Reset2=0;
		car_out_flag=0; 
	 }
  }
 }
}

int car_out3=0;
void Tracking_Switch_Mode3(void)
{
 if((tracking[0]||tracking[1]||tracking[2]||tracking[3]||tracking[4]||tracking[5]||tracking[6]||tracking[7])==0)
 {
 car_out3++;
	 if(car_out3>80)
	 {
	  car_out3=0;
	  Turn_back_MODE=4;
	 }
 }
}
