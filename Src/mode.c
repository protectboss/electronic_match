#include "mode.h"
#include "joint.h"
#include "main.h"
#include "chassis.h"
#include "tracking.h"
#include "encoder.h"
#include "pid.h"
#include "settlement.h"


int ELECTRONIC_CAR_MODE=1;


void Car_Mode1(void)
{
  Read_Encoder_Speed();
  Read_GPIO();
	Tracking_Switch_Mode();
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


void Car_Mode2(void)
{
  Joint_Clamping();
	Joint_Switch_Mode();
  Moto1_Speed_Output(0);
	Moto2_Speed_Output(0);
	Moto3_Speed_Output(0);
	Moto4_Speed_Output(0);
}


void Car_Mode3(void)
{
	/*机械臂控制部分*/
 if(Drop_Litter_Cnt==0)
 {
  Joint_Normal();
 }
 if((0<Drop_Litter_Cnt)&&(Drop_Litter_Cnt<=1050))
 {
  Throw_rubbish();
 }
 if(1050<Drop_Litter_Cnt&&Drop_Litter_Cnt<=1950)
 {
	 Recycling_Line();
 }
 if(Drop_Litter_Cnt>1950)
 {
  Joint_Normal();
 }
 
 
 /*底盘位移结算部分*/
 Displacement_Mode_Judge();
 Displacement_Switch_Mode();
}


void Car_Mode_Judge(void)
{
 switch(ELECTRONIC_CAR_MODE)
 {
	 case 1:Car_Mode1();break;
	 case 2:Car_Mode2();break;
	 case 3:Car_Mode3();break;
 }
}

