#include "settlement.h"
#include "encoder.h"
#include "pid.h"
#include "tim.h"
#include "chassis.h"
#include "mode.h"
#include "room_search.h"
#include "joint.h"


#define settlement_speed 30   //位移速度，不改
#define settlement_low_speed 20   //用于精度较高时的位移速度，不改


#define settlement1_right_distance 1610   //第一段向右行走的路程，从循迹一到循迹二(已调)
#define settlement1_turn_right_distance 2270   //第一段的转弯路程，从循迹一到循迹二(已调)
#define settlement2_left_distance 1100    //第二段向左走的路程，从循迹二到循迹三(已调)
#define settlement2_turn_left_distance 2270    //第二段左转的路程，从循迹二到循迹三(已调)


#define turn_back1_turn_right_distance 2000              //从循迹一终点处转弯路程，转一百八十度
#define turn_back2_back_distance  1700     //从循迹二终点处到循迹一线上的后退路程
#define turn_back2_right_distance   1900    //从循迹二终点处到循迹一线上的向右走的路程

#define turn_back3_turn_right_distance 1000  //从循迹三终点处回来循迹一，右转的路程(已调)
#define turn_back3_right_distance 6900   //从循迹三终点处回来循迹一，右走的路程


#define turn_back4_right_distance	2200   //终点(起点)处向右转弯路程，转180度




short Settlement_Zero_Flag[4];
short Display_Settlement_Mode=1;
int32_t Switch_Mode_Cnt=0;
short Display_Settlement_time=1;
int32_t Drop_Litter_Cnt=0;


void Settlement_Flag_Init(void)
{
 Settlement_Zero_Flag[0]=0;
 Settlement_Zero_Flag[1]=0;
 Settlement_Zero_Flag[2]=0;
 Settlement_Zero_Flag[3]=0;
}

                       /*位移定义函数*/

void Displacement_forward(int distance,int speed)
{
 if(Encoder_Sum.Moto1<distance) MotoData.Moto1.targer_speed=speed;
 else MotoData.Moto1.targer_speed=0;

 if(Encoder_Sum.Moto2<distance) MotoData.Moto2.targer_speed=speed;
 else MotoData.Moto2.targer_speed=0;

 if(Encoder_Sum.Moto3<distance) MotoData.Moto3.targer_speed=speed;
 else MotoData.Moto3.targer_speed=0;

 if(Encoder_Sum.Moto4<distance) MotoData.Moto4.targer_speed=speed;
 else MotoData.Moto4.targer_speed=0;
}

void Displacement_back(int distance,int speed)
{
 if(Encoder_Sum.Moto1>-distance) MotoData.Moto1.targer_speed=-speed;
 else MotoData.Moto1.targer_speed=0;

 if(Encoder_Sum.Moto2>-distance) MotoData.Moto2.targer_speed=-speed;
 else MotoData.Moto2.targer_speed=0;

 if(Encoder_Sum.Moto3>-distance) MotoData.Moto3.targer_speed=-speed;
 else MotoData.Moto3.targer_speed=0;

 if(Encoder_Sum.Moto4>-distance) MotoData.Moto4.targer_speed=-speed;
 else MotoData.Moto4.targer_speed=0;
}

void Displacement_left(int distance,int speed)
{
 if(Encoder_Sum.Moto1>-distance) MotoData.Moto1.targer_speed=-speed;
 else MotoData.Moto1.targer_speed=0;

 if(Encoder_Sum.Moto2<distance) MotoData.Moto2.targer_speed=speed;
 else MotoData.Moto2.targer_speed=0;

 if(Encoder_Sum.Moto3<distance) MotoData.Moto3.targer_speed=speed;
 else MotoData.Moto3.targer_speed=0;

 if(Encoder_Sum.Moto4>-distance) MotoData.Moto4.targer_speed=-speed;
 else MotoData.Moto4.targer_speed=0;
}

void Displacement_right(int distance,int speed)
{
 if(Encoder_Sum.Moto1<distance) MotoData.Moto1.targer_speed=speed;
 else MotoData.Moto1.targer_speed=0;

 if(Encoder_Sum.Moto2>-distance) MotoData.Moto2.targer_speed=-speed;
 else MotoData.Moto2.targer_speed=0;

 if(Encoder_Sum.Moto3>-distance) MotoData.Moto3.targer_speed=-speed;
 else MotoData.Moto3.targer_speed=0;

 if(Encoder_Sum.Moto4<distance) MotoData.Moto4.targer_speed=speed;
 else MotoData.Moto4.targer_speed=0;
}

void Displacement_turn_left(int distance,int speed)
{
 if(Encoder_Sum.Moto1>-distance) MotoData.Moto1.targer_speed=-speed;
 else MotoData.Moto1.targer_speed=0;

 if(Encoder_Sum.Moto2<distance) MotoData.Moto2.targer_speed=speed;
 else MotoData.Moto2.targer_speed=0;

 if(Encoder_Sum.Moto3>-distance) MotoData.Moto3.targer_speed=-speed;
 else MotoData.Moto3.targer_speed=0;

 if(Encoder_Sum.Moto4<distance) MotoData.Moto4.targer_speed=speed;
 else MotoData.Moto4.targer_speed=0;
}

void Displacement_turn_right(int distance,int speed)
{
 if(Encoder_Sum.Moto1<distance) MotoData.Moto1.targer_speed=speed;
 else MotoData.Moto1.targer_speed=0;

 if(Encoder_Sum.Moto2>-distance) MotoData.Moto2.targer_speed=-speed;
 else MotoData.Moto2.targer_speed=0;

 if(Encoder_Sum.Moto3<distance) MotoData.Moto3.targer_speed=speed;
 else MotoData.Moto3.targer_speed=0;

 if(Encoder_Sum.Moto4>-distance) MotoData.Moto4.targer_speed=-speed;
 else MotoData.Moto4.targer_speed=0;
}


/*--------------------------------------------------拾取所有垃圾时的位移函数-----------------------------------------------------------*/

void Displacement_Settlement1(void)
{
	if(Settlement_Zero_Flag[0]==0)
	{
   Encoder_Zero();
	 Encoder_Sum_Zero();
	 Settlement_Zero_Flag[0]=1;
	 Display_Settlement_Mode=1;
	}
  Read_Encoder_Sum();
	
	if(Display_Settlement_Mode==1)
	{
	 Displacement_right(settlement1_right_distance,settlement_speed);
	 if(MotoData.Moto1.targer_speed==0&&MotoData.Moto2.targer_speed==0&&MotoData.Moto3.targer_speed==0&&MotoData.Moto4.targer_speed==0)
   {
	  Encoder_Zero();
	  Encoder_Sum_Zero();
	  Display_Settlement_Mode=2;
   }
	}
	
		if(Display_Settlement_Mode==2)
	{
	 Displacement_turn_right(settlement1_turn_right_distance,settlement_speed);
	 if(MotoData.Moto1.targer_speed==0&&MotoData.Moto2.targer_speed==0&&MotoData.Moto3.targer_speed==0&&MotoData.Moto4.targer_speed==0)
   {	
	  Switch_Mode_Cnt++;
   }
	}
	
	WZPid(&Pid.No1,MotoData.Moto1.targer_speed,MotoData.Moto1.encoder);
	WZPid(&Pid.No2,MotoData.Moto2.targer_speed,MotoData.Moto2.encoder);
	WZPid(&Pid.No3,MotoData.Moto3.targer_speed,MotoData.Moto3.encoder);
	WZPid(&Pid.No4,MotoData.Moto4.targer_speed,MotoData.Moto4.encoder);
	Moto1_Speed_Output(Pid.No1.output);
	Moto2_Speed_Output(Pid.No2.output);
	Moto3_Speed_Output(Pid.No3.output);
	Moto4_Speed_Output(Pid.No4.output);
}


void Displacement_Settlement2(void)
{
	if(Settlement_Zero_Flag[1]==0)
	{
   Encoder_Zero();
	 Encoder_Sum_Zero();
	 Settlement_Zero_Flag[1]=1;
	 Display_Settlement_Mode=1;
	}
  Read_Encoder_Sum();
	
	if(Display_Settlement_Mode==1)
	{
	 Displacement_left(settlement2_left_distance,settlement_speed);
	 if(MotoData.Moto1.targer_speed==0&&MotoData.Moto2.targer_speed==0&&MotoData.Moto3.targer_speed==0&&MotoData.Moto4.targer_speed==0)
   {
	  Encoder_Zero();
	  Encoder_Sum_Zero();
	  Display_Settlement_Mode=2;
   }
	}
	
		if(Display_Settlement_Mode==2)
	{
	 Displacement_turn_left(settlement2_turn_left_distance,settlement_speed);
	 if(MotoData.Moto1.targer_speed==0&&MotoData.Moto2.targer_speed==0&&MotoData.Moto3.targer_speed==0&&MotoData.Moto4.targer_speed==0)
   {	
	  Switch_Mode_Cnt++;
   }
	}
	WZPid(&Pid.No1,MotoData.Moto1.targer_speed,MotoData.Moto1.encoder);
	WZPid(&Pid.No2,MotoData.Moto2.targer_speed,MotoData.Moto2.encoder);
	WZPid(&Pid.No3,MotoData.Moto3.targer_speed,MotoData.Moto3.encoder);
	WZPid(&Pid.No4,MotoData.Moto4.targer_speed,MotoData.Moto4.encoder);
	Moto1_Speed_Output(Pid.No1.output);
	Moto2_Speed_Output(Pid.No2.output);
	Moto3_Speed_Output(Pid.No3.output);
	Moto4_Speed_Output(Pid.No4.output);
}

int Displacement_Settlement_cnt3=0;
void Displacement_Settlement3(void)
{
	if(Settlement_Zero_Flag[2]==0)
	{
   Encoder_Zero();
	 Encoder_Sum_Zero();
	 Settlement_Zero_Flag[2]=1;
	 Display_Settlement_Mode=1;
	}
  Read_Encoder_Sum();
	
	
	if(Display_Settlement_Mode==1)
	{
	 Displacement_turn_right(turn_back3_turn_right_distance,settlement_low_speed);
	 if(MotoData.Moto1.targer_speed==0&&MotoData.Moto2.targer_speed==0&&MotoData.Moto3.targer_speed==0&&MotoData.Moto4.targer_speed==0)
   {
		Displacement_Settlement_cnt3++;
	  if(Displacement_Settlement_cnt3==50)
		{
		Encoder_Zero();
	  Encoder_Sum_Zero();
	  Display_Settlement_Mode=2;
		Displacement_Settlement_cnt3=0;
		}
   }
	}
	
		if(Display_Settlement_Mode==2)
	{
	 Displacement_right(turn_back3_right_distance,settlement_low_speed);//8070
	 if(MotoData.Moto1.targer_speed==0&&MotoData.Moto2.targer_speed==0&&MotoData.Moto3.targer_speed==0&&MotoData.Moto4.targer_speed==0)
   {	
	  Switch_Mode_Cnt++;
   }
	}
	WZPid(&Pid.No1,MotoData.Moto1.targer_speed,MotoData.Moto1.encoder);
	WZPid(&Pid.No2,MotoData.Moto2.targer_speed,MotoData.Moto2.encoder);
	WZPid(&Pid.No3,MotoData.Moto3.targer_speed,MotoData.Moto3.encoder);
	WZPid(&Pid.No4,MotoData.Moto4.targer_speed,MotoData.Moto4.encoder);
	Moto1_Speed_Output(Pid.No1.output);
	Moto2_Speed_Output(Pid.No2.output);
	Moto3_Speed_Output(Pid.No3.output);
	Moto4_Speed_Output(Pid.No4.output);
}

void Displacement_Settlement4(void)
{
	if(Settlement_Zero_Flag[3]==0)
	{
   Encoder_Zero();
	 Encoder_Sum_Zero();
	 Settlement_Zero_Flag[3]=1;
	 Display_Settlement_Mode=1;
	}
  Read_Encoder_Sum();
	
	
		if(Display_Settlement_Mode==1)
	{
	 Displacement_turn_left(turn_back4_right_distance,settlement_speed);
	 if(MotoData.Moto1.targer_speed==0&&MotoData.Moto2.targer_speed==0&&MotoData.Moto3.targer_speed==0&&MotoData.Moto4.targer_speed==0)
   {
		if(Drop_Litter_Cnt<2005)
		{
	   Drop_Litter_Cnt++;
		}
   }
	}
	WZPid(&Pid.No1,MotoData.Moto1.targer_speed,MotoData.Moto1.encoder);
	WZPid(&Pid.No2,MotoData.Moto2.targer_speed,MotoData.Moto2.encoder);
	WZPid(&Pid.No3,MotoData.Moto3.targer_speed,MotoData.Moto3.encoder);
	WZPid(&Pid.No4,MotoData.Moto4.targer_speed,MotoData.Moto4.encoder);
	Moto1_Speed_Output(Pid.No1.output);
	Moto2_Speed_Output(Pid.No2.output);
	Moto3_Speed_Output(Pid.No3.output);
	Moto4_Speed_Output(Pid.No4.output);
}

void Displacement_Switch_Mode(void)
{
 if(Switch_Mode_Cnt>100)
 {
 Switch_Mode_Cnt=0;
 ELECTRONIC_CAR_MODE=1;
 Display_Settlement_time++;
 }
}


void Displacement_Mode_Judge(void)
{
 switch(Display_Settlement_time)
 {
	 case 1:Displacement_Settlement1();break;
	 case 2:Displacement_Settlement2();break;
	 case 3:Displacement_Settlement3();break;
	 case 4:Displacement_Settlement4();break;
 }
}


/*--------------------------------------------------------拾取指定垃圾时的位移函数-----------------------------------------------------*/

int Switch_Mode_Cnt2=0;
short Settlement_Zero_Flag2[3];
short Display_Settlement_Mode2=1;
short Display_Settlement_time2=1;

void Settlement_Flag_Init2(void)
{
 Settlement_Zero_Flag2[0]=0;
 Settlement_Zero_Flag2[1]=0;
 Settlement_Zero_Flag2[2]=0;
}


void Move_Displacement1(void)
{
		if(Settlement_Zero_Flag2[0]==0)
	{
   Encoder_Zero();
	 Encoder_Sum_Zero();
	 Settlement_Zero_Flag2[0]=1;
	 Display_Settlement_Mode2=1;
	}
  Read_Encoder_Sum();
	
	if(Display_Settlement_Mode2==1)
	{
	 Displacement_right(settlement1_right_distance,settlement_speed);
	 if(MotoData.Moto1.targer_speed==0&&MotoData.Moto2.targer_speed==0&&MotoData.Moto3.targer_speed==0&&MotoData.Moto4.targer_speed==0)
   {
	  Encoder_Zero();
	  Encoder_Sum_Zero();
	  Display_Settlement_Mode2=2;
   }
	}
	
		if(Display_Settlement_Mode2==2)
	{
	 Displacement_turn_right(settlement1_turn_right_distance,settlement_speed);
	 if(MotoData.Moto1.targer_speed==0&&MotoData.Moto2.targer_speed==0&&MotoData.Moto3.targer_speed==0&&MotoData.Moto4.targer_speed==0)
   {	
	  Switch_Mode_Cnt2++;
   }
	}
	WZPid(&Pid.No1,MotoData.Moto1.targer_speed,MotoData.Moto1.encoder);
	WZPid(&Pid.No2,MotoData.Moto2.targer_speed,MotoData.Moto2.encoder);
	WZPid(&Pid.No3,MotoData.Moto3.targer_speed,MotoData.Moto3.encoder);
	WZPid(&Pid.No4,MotoData.Moto4.targer_speed,MotoData.Moto4.encoder);
	Moto1_Speed_Output(Pid.No1.output);
	Moto2_Speed_Output(Pid.No2.output);
	Moto3_Speed_Output(Pid.No3.output);
	Moto4_Speed_Output(Pid.No4.output);
}


void Move_Displacement2(void)
{
	if(Settlement_Zero_Flag2[1]==0)
	{
   Encoder_Zero();
	 Encoder_Sum_Zero();
	 Settlement_Zero_Flag2[1]=1;
	 Display_Settlement_Mode2=1;
	}
  Read_Encoder_Sum();
	
	if(Display_Settlement_Mode2==1)
	{
	 Displacement_left(settlement2_left_distance,settlement_speed);
	 if(MotoData.Moto1.targer_speed==0&&MotoData.Moto2.targer_speed==0&&MotoData.Moto3.targer_speed==0&&MotoData.Moto4.targer_speed==0)
   {
	  Encoder_Zero();
	  Encoder_Sum_Zero();
	  Display_Settlement_Mode2=2;
   }
	}
	
		if(Display_Settlement_Mode2==2)
	{
	 Displacement_turn_left(settlement2_turn_left_distance,settlement_speed);
	 if(MotoData.Moto1.targer_speed==0&&MotoData.Moto2.targer_speed==0&&MotoData.Moto3.targer_speed==0&&MotoData.Moto4.targer_speed==0)
   {	
	  Switch_Mode_Cnt2++;
   }
	}
	WZPid(&Pid.No1,MotoData.Moto1.targer_speed,MotoData.Moto1.encoder);
	WZPid(&Pid.No2,MotoData.Moto2.targer_speed,MotoData.Moto2.encoder);
	WZPid(&Pid.No3,MotoData.Moto3.targer_speed,MotoData.Moto3.encoder);
	WZPid(&Pid.No4,MotoData.Moto4.targer_speed,MotoData.Moto4.encoder);
	Moto1_Speed_Output(Pid.No1.output);
	Moto2_Speed_Output(Pid.No2.output);
	Moto3_Speed_Output(Pid.No3.output);
	Moto4_Speed_Output(Pid.No4.output);
}


void Displacement_Switch_Mode2(void)
{
 if(Switch_Mode_Cnt2>100)
 {
 Switch_Mode_Cnt2=0;
 Room_Search_MODE=1;
 Display_Settlement_time2++;
 }
}


void Displacement_Mode_Judge2(void)
{
 switch(Display_Settlement_time2)
 {
	 case 1:Move_Displacement1();break;
	 case 2:Move_Displacement2();break;
 }
}



/*--------------------------------------------------返回运动路程结算-----------------------------------------------------------------*/
int Switch_Mode_Cnt3=0;
short Settlement_Zero_Flag3[4];
short Display_Settlement_Mode3=1;


void Settlement_Flag_Init3(void)
{
 Settlement_Zero_Flag3[0]=0;
 Settlement_Zero_Flag3[1]=0;
 Settlement_Zero_Flag3[2]=0;
 Settlement_Zero_Flag3[3]=0;
}


void Turn_Back_Displacement1(void)
{
	if(Settlement_Zero_Flag3[0]==0)
	{
   Encoder_Zero();
	 Encoder_Sum_Zero();
	 Settlement_Zero_Flag3[0]=1;
	 Display_Settlement_Mode3=1;
	}
  Read_Encoder_Sum();
	
	if(Display_Settlement_Mode3==1)
	{
	 Displacement_turn_right(turn_back1_turn_right_distance,settlement_speed);
	 if(MotoData.Moto1.targer_speed==0&&MotoData.Moto2.targer_speed==0&&MotoData.Moto3.targer_speed==0&&MotoData.Moto4.targer_speed==0)
   {
	  Switch_Mode_Cnt3++;
   }
	}

	
	WZPid(&Pid.No1,MotoData.Moto1.targer_speed,MotoData.Moto1.encoder);
	WZPid(&Pid.No2,MotoData.Moto2.targer_speed,MotoData.Moto2.encoder);
	WZPid(&Pid.No3,MotoData.Moto3.targer_speed,MotoData.Moto3.encoder);
	WZPid(&Pid.No4,MotoData.Moto4.targer_speed,MotoData.Moto4.encoder);
	Moto1_Speed_Output(Pid.No1.output);
	Moto2_Speed_Output(Pid.No2.output);
	Moto3_Speed_Output(Pid.No3.output);
	Moto4_Speed_Output(Pid.No4.output);
}


int turn_back_cnt2;//为了保证小车不歪掉，必须要延时再进行下一段
void Turn_Back_Displacement2(void)
{
	if(Settlement_Zero_Flag3[1]==0)
	{
   Encoder_Zero();
	 Encoder_Sum_Zero();
	 Settlement_Zero_Flag3[1]=1;
	 Display_Settlement_Mode3=1;
	}
  Read_Encoder_Sum();
	
	if(Display_Settlement_Mode3==1)
	{
	 Displacement_back(turn_back2_back_distance,settlement_speed);
	 if(MotoData.Moto1.targer_speed==0&&MotoData.Moto2.targer_speed==0&&MotoData.Moto3.targer_speed==0&&MotoData.Moto4.targer_speed==0)
   {
		turn_back_cnt2++;
		if(turn_back_cnt2>100)
		{
	  Encoder_Zero();
	  Encoder_Sum_Zero();
	  Display_Settlement_Mode3=2;
		turn_back_cnt2=0;
		}
   }
	}
	
		if(Display_Settlement_Mode3==2)
	{
	 Displacement_right(turn_back2_right_distance,settlement_speed);
	 if(MotoData.Moto1.targer_speed==0&&MotoData.Moto2.targer_speed==0&&MotoData.Moto3.targer_speed==0&&MotoData.Moto4.targer_speed==0)
   {	
	  Switch_Mode_Cnt3++;
   }
	}
	
	WZPid(&Pid.No1,MotoData.Moto1.targer_speed,MotoData.Moto1.encoder);
	WZPid(&Pid.No2,MotoData.Moto2.targer_speed,MotoData.Moto2.encoder);
	WZPid(&Pid.No3,MotoData.Moto3.targer_speed,MotoData.Moto3.encoder);
	WZPid(&Pid.No4,MotoData.Moto4.targer_speed,MotoData.Moto4.encoder);
	Moto1_Speed_Output(Pid.No1.output);
	Moto2_Speed_Output(Pid.No2.output);
	Moto3_Speed_Output(Pid.No3.output);
	Moto4_Speed_Output(Pid.No4.output);

}

void Turn_Back_Displacement3(void)
{
	if(Settlement_Zero_Flag3[2]==0)
	{
   Encoder_Zero();
	 Encoder_Sum_Zero();
	 Settlement_Zero_Flag3[2]=1;
	 Display_Settlement_Mode3=1;
	}
  Read_Encoder_Sum();
	
	if(Display_Settlement_Mode3==1)
	{
	 Displacement_turn_right(turn_back3_turn_right_distance,settlement_low_speed);
	 if(MotoData.Moto1.targer_speed==0&&MotoData.Moto2.targer_speed==0&&MotoData.Moto3.targer_speed==0&&MotoData.Moto4.targer_speed==0)
   {
	  Encoder_Zero();
	  Encoder_Sum_Zero();
	  Display_Settlement_Mode3=2;
   }
	}
	
		if(Display_Settlement_Mode3==2)
	{
	 Displacement_right(turn_back3_right_distance,settlement_low_speed);
	 if(MotoData.Moto1.targer_speed==0&&MotoData.Moto2.targer_speed==0&&MotoData.Moto3.targer_speed==0&&MotoData.Moto4.targer_speed==0)
   {	
	  Switch_Mode_Cnt3++;
   }
	}
	
	WZPid(&Pid.No1,MotoData.Moto1.targer_speed,MotoData.Moto1.encoder);
	WZPid(&Pid.No2,MotoData.Moto2.targer_speed,MotoData.Moto2.encoder);
	WZPid(&Pid.No3,MotoData.Moto3.targer_speed,MotoData.Moto3.encoder);
	WZPid(&Pid.No4,MotoData.Moto4.targer_speed,MotoData.Moto4.encoder);
	Moto1_Speed_Output(Pid.No1.output);
	Moto2_Speed_Output(Pid.No2.output);
	Moto3_Speed_Output(Pid.No3.output);
	Moto4_Speed_Output(Pid.No4.output);

}


void Turn_Back_Displacement4(void)
{
	if(Settlement_Zero_Flag3[3]==0)
	{
   Encoder_Zero();
	 Encoder_Sum_Zero();
	 Settlement_Zero_Flag3[3]=1;
	 Display_Settlement_Mode3=1;
	}
  Read_Encoder_Sum();
	
	if(Display_Settlement_Mode3==1)
	{
	 Displacement_turn_right(turn_back4_right_distance,settlement_speed);
	 if(MotoData.Moto1.targer_speed==0&&MotoData.Moto2.targer_speed==0&&MotoData.Moto3.targer_speed==0&&MotoData.Moto4.targer_speed==0)
   {
		 Recycling_rubbish();
   }
	}
	
	WZPid(&Pid.No1,MotoData.Moto1.targer_speed,MotoData.Moto1.encoder);
	WZPid(&Pid.No2,MotoData.Moto2.targer_speed,MotoData.Moto2.encoder);
	WZPid(&Pid.No3,MotoData.Moto3.targer_speed,MotoData.Moto3.encoder);
	WZPid(&Pid.No4,MotoData.Moto4.targer_speed,MotoData.Moto4.encoder);
	Moto1_Speed_Output(Pid.No1.output);
	Moto2_Speed_Output(Pid.No2.output);
	Moto3_Speed_Output(Pid.No3.output);
	Moto4_Speed_Output(Pid.No4.output);

}

void Displacement_Switch_Mode3(void)
{
 if(Switch_Mode_Cnt3>100)
 {
 Switch_Mode_Cnt3=0;
 Turn_back_MODE=3;
 Display_Settlement_time2=4;
 }
}

void Displacement_Mode_Judge3(void)
{
 switch(Display_Settlement_time2)
 {
	 case 1:Turn_Back_Displacement1();break;
	 case 2:Turn_Back_Displacement2();break;
	 case 3:Turn_Back_Displacement3();break;
 }
}
