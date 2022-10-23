#ifndef __ENCODER_H
#define __ENCODER_H

#include "tim.h"

void Read_Encoder_Speed(void);
void Encoder_Init(void);
void Read_Encoder_Sum(void);
void Encoder_Sum_Zero(void);
void Encoder_Zero(void);


typedef struct
{
 int64_t Moto1;
 int64_t Moto2;
 int64_t Moto3;
 int64_t Moto4;
}Encoder_Sum_TypeDef;


extern Encoder_Sum_TypeDef Encoder_Sum;


#endif
