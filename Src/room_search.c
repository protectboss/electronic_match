#include "room_search.h"
#include "tracking.h"
#include "encoder.h"
#include "joint.h"
#include "main.h"
#include "chassis.h"
#include "pid.h"
#include "settlement.h"


int	Room_Search_MODE=1; //寻找对应房间号的垃圾模式
int Turn_back_MODE=1;   //返回的模式 
int Turn_Back_Flag=0;   //1表示已抓取垃圾正在返回，0表示未抓取垃圾


void Room_Search_Mode1(void)
{
  Read_Encoder_Speed();
  Read_GPIO();
	Tracking_Switch_Mode2();
  Tracking_Move();
	WZPid(&Pid.No1,MotoData.Moto1.targer_speed,MotoData.Moto1.encoder);
	WZPid(&Pid.No2,MotoData.Moto2.targer_speed,MotoData.Moto2.encoder);
	WZPid(&Pid.No3,MotoData.Moto3.targer_speed,MotoData.Moto3.encoder);
	WZPid(&Pid.No4,MotoData.Moto4.targer_speed,MotoData.Moto4.encoder);
	Moto1_Speed_Output(Pid.No1.output);
	Moto2_Speed_Output(Pid.No2.output);
	Moto3_Speed_Output(Pid.No3.output);
	Moto4_Speed_Output(Pid.No4.output);
	Joint_Normal();
}


void Room_Search_Mode2(void)
{
 Joint_Normal();
 Displacement_Mode_Judge2();
 Displacement_Switch_Mode2();
}


void Turn_Back_Mode1(void)
{
  Joint_Clamping();
	Turn_Back();
  Moto1_Speed_Output(0);
	Moto2_Speed_Output(0);
	Moto3_Speed_Output(0);
	Moto4_Speed_Output(0);
}


void Turn_Back_Mode2(void)
{
 Joint_Normal();
 Displacement_Mode_Judge3();
 Displacement_Switch_Mode3();
}


void Turn_Back_Mode3(void)
{
  Read_Encoder_Speed();
  Read_GPIO();
	Tracking_Switch_Mode3();
  Tracking_Move();
	WZPid(&Pid.No1,MotoData.Moto1.targer_speed,MotoData.Moto1.encoder);
	WZPid(&Pid.No2,MotoData.Moto2.targer_speed,MotoData.Moto2.encoder);
	WZPid(&Pid.No3,MotoData.Moto3.targer_speed,MotoData.Moto3.encoder);
	WZPid(&Pid.No4,MotoData.Moto4.targer_speed,MotoData.Moto4.encoder);
	Moto1_Speed_Output(Pid.No1.output);
	Moto2_Speed_Output(Pid.No2.output);
	Moto3_Speed_Output(Pid.No3.output);
	Moto4_Speed_Output(Pid.No4.output);
	Joint_Normal();
}	

void Turn_Back_Mode4(void)
{
 Turn_Back_Displacement4();
}




void Room_Search_Mode_Judge(void)
{
 if(Turn_Back_Flag==0)
 {
  switch(Room_Search_MODE)
  {
	  case 1:Room_Search_Mode1();break;
	  case 2:Room_Search_Mode2();break;
  }
 }
 else
 {
  switch(Turn_back_MODE)
  {
 	 case 1:Turn_Back_Mode1();break;
	 case 2:Turn_Back_Mode2();break;
	 case 3:Turn_Back_Mode3();break;	
	 case 4:Turn_Back_Mode4();break;
  }
 }
}

