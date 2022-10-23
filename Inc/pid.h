#ifndef __PID_H_
#define __PID_H_

#include "main.h"


typedef struct 
{
 float Kp,Ki,Kd;
 float error,error_last;
 float integral,integral_max;
 float output,output_max;
}WZPID_TypeDef;


typedef struct
{
 WZPID_TypeDef No1;
 WZPID_TypeDef No2;
 WZPID_TypeDef No3;
 WZPID_TypeDef No4;
}WZPID_NumberTypeDef;


void WZPid(WZPID_TypeDef *WZpid,float target,float real);
void WZPid_Init(WZPID_TypeDef *WZpid,float p,float i,float d,float Integral_max,float Out_max);
void ALL_Pid_Init(void);


extern WZPID_NumberTypeDef Pid;



#endif
