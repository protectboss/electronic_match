#ifndef __CHASSIS_H_
#define __CHASSIS_H_


#include "main.h"

typedef struct
{
int encoder;
int targer_speed;
}MOTO_DATA_TypeDef;


typedef struct
{
MOTO_DATA_TypeDef Moto1;
MOTO_DATA_TypeDef Moto2;
MOTO_DATA_TypeDef Moto3;
MOTO_DATA_TypeDef Moto4;
}MOTO_NUMBER_TypeDef;


void Chassis_Init(void);


extern MOTO_NUMBER_TypeDef MotoData;


void Moto1_Go_Forward(int PWM);
void Moto1_Draw_Back(int PWM);
void Moto1_Stop(void);

void Moto2_Go_Forward(int PWM);
void Moto2_Draw_Back(int PWM);
void Moto2_Stop(void);

void Moto3_Go_Forward(int PWM);
void Moto3_Draw_Back(int PWM);
void Moto3_Stop(void);

void Moto4_Go_Forward(int PWM);
void Moto4_Draw_Back(int PWM);
void Moto4_Stop(void);


void Moto1_Speed_Output(int speed);
void Moto2_Speed_Output(int speed);
void Moto3_Speed_Output(int speed);
void Moto4_Speed_Output(int speed);


void Car_Turn(int left_speed,int right_speed);
void Car_Forward(int speed);


#endif
