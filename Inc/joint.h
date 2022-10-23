#ifndef __JOINT_H_
#define __JOINT_H_

#include "tim.h"

void Joint_Init(void);
void Joint_Move(int box_position,int yaw,int pitch,int clip,int box_cap);
void Joint_time_Init(void);
void Joint_Time_Sum(void);
void Joint_Clamping(void);
void Joint_Normal(void);
void Throw_rubbish(void);
void Recycling_Line(void);
void Joint_Switch_Mode(void);
void Turn_Back(void);
void Recycling_rubbish(void);


extern int32_t Joint_time;
void Clamping_RUbbish(void);



#endif
