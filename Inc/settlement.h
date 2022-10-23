#ifndef __SETTLEMENT_H_
#define __SETTLEMENT_H_


#include "tim.h"

void Settlement_Flag_Init(void);
void Displacement_forward(int distance,int speed);
void Displacement_back(int distance,int speed);
void Displacement_left(int distance,int speed);
void Displacement_right(int distance,int speed);
void Displacement_turn_left(int distance,int speed);
void Displacement_turn_right(int distance,int speed);

void Displacement_Settlement1(void);
void Displacement_Settlement2(void);
void Displacement_Settlement3(void);
void Displacement_Settlement4(void);
void Displacement_Mode_Judge(void);
void Displacement_Switch_Mode(void);

void Settlement_Flag_Init2(void);
void Move_Displacement1(void);
void Move_Displacement2(void);
void Displacement_Switch_Mode2(void);
void Displacement_Mode_Judge2(void);

void Settlement_Flag_Init3(void);
void Turn_Back_Displacement1(void);
void Turn_Back_Displacement2(void);
void Turn_Back_Displacement3(void);
void Turn_Back_Displacement4(void);
void Displacement_Switch_Mode3(void);
void	Displacement_Mode_Judge3(void);


extern int32_t Switch_Mode_Cnt;
extern short Display_Settlement_time;
extern int32_t Drop_Litter_Cnt;
extern short Display_Settlement_time2;
extern int Switch_Mode_Cnt2;
extern int Switch_Mode_Cnt3;



#endif
