#include "chassis.h"
#include "tim.h"


MOTO_NUMBER_TypeDef MotoData;

/*初始化pwm*/
void Chassis_Init(void)
{
 HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_1);
 HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_2);
 HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_3);
 HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_4);
}

/*整车移动各个目标电机输出速度*/
void Car_Forward(int speed)
{
MotoData.Moto1.targer_speed=speed;
MotoData.Moto2.targer_speed=speed;
MotoData.Moto3.targer_speed=speed;
MotoData.Moto4.targer_speed=speed;
}

void Car_Turn(int left_speed,int right_speed)
{
MotoData.Moto1.targer_speed=left_speed;
MotoData.Moto2.targer_speed=right_speed;
MotoData.Moto3.targer_speed=left_speed;
MotoData.Moto4.targer_speed=right_speed;
}


/*对各个电机进行gpio配置与pwm输出*/
void Moto1_Go_Forward(int PWM)
{
 HAL_GPIO_WritePin(GPIOF,GPIO_PIN_0,GPIO_PIN_RESET);
 HAL_GPIO_WritePin(GPIOF,GPIO_PIN_1,GPIO_PIN_SET);
 __HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_1,PWM);
}

void Moto1_Draw_Back(int PWM)
{
 HAL_GPIO_WritePin(GPIOF,GPIO_PIN_0,GPIO_PIN_SET);
 HAL_GPIO_WritePin(GPIOF,GPIO_PIN_1,GPIO_PIN_RESET);
 __HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_1,-PWM);
}

void Moto1_Stop(void)
{
 HAL_GPIO_WritePin(GPIOF,GPIO_PIN_0,GPIO_PIN_RESET);
 HAL_GPIO_WritePin(GPIOF,GPIO_PIN_1,GPIO_PIN_RESET);
 __HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_1,0);
}


void Moto2_Go_Forward(int PWM)
{
 HAL_GPIO_WritePin(GPIOF,GPIO_PIN_2,GPIO_PIN_RESET);
 HAL_GPIO_WritePin(GPIOF,GPIO_PIN_3,GPIO_PIN_SET);
 __HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_2,PWM);
}

void Moto2_Draw_Back(int PWM)
{
 HAL_GPIO_WritePin(GPIOF,GPIO_PIN_2,GPIO_PIN_SET);
 HAL_GPIO_WritePin(GPIOF,GPIO_PIN_3,GPIO_PIN_RESET);
 __HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_2,-PWM);
}

void Moto2_Stop(void)
{
 HAL_GPIO_WritePin(GPIOF,GPIO_PIN_2,GPIO_PIN_RESET);
 HAL_GPIO_WritePin(GPIOF,GPIO_PIN_3,GPIO_PIN_RESET);
 __HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_2,0);
}


void Moto3_Go_Forward(int PWM)
{
 HAL_GPIO_WritePin(GPIOF,GPIO_PIN_5,GPIO_PIN_RESET);
 HAL_GPIO_WritePin(GPIOF,GPIO_PIN_4,GPIO_PIN_SET);
 __HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_3,PWM);
}

void Moto3_Draw_Back(int PWM)
{
 HAL_GPIO_WritePin(GPIOF,GPIO_PIN_5,GPIO_PIN_SET);
 HAL_GPIO_WritePin(GPIOF,GPIO_PIN_4,GPIO_PIN_RESET);
 __HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_3,-PWM);
}

void Moto3_Stop(void)
{
 HAL_GPIO_WritePin(GPIOF,GPIO_PIN_5,GPIO_PIN_RESET);
 HAL_GPIO_WritePin(GPIOF,GPIO_PIN_4,GPIO_PIN_RESET);
 __HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_3,0);
}


void Moto4_Go_Forward(int PWM)
{
 HAL_GPIO_WritePin(GPIOF,GPIO_PIN_6,GPIO_PIN_RESET);
 HAL_GPIO_WritePin(GPIOF,GPIO_PIN_7,GPIO_PIN_SET);
 __HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_4,PWM);
}

void Moto4_Draw_Back(int PWM)
{
 HAL_GPIO_WritePin(GPIOF,GPIO_PIN_6,GPIO_PIN_SET);
 HAL_GPIO_WritePin(GPIOF,GPIO_PIN_7,GPIO_PIN_RESET);
 __HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_4,-PWM);
}

void Moto4_Stop(void)
{
 HAL_GPIO_WritePin(GPIOF,GPIO_PIN_6,GPIO_PIN_RESET);
 HAL_GPIO_WritePin(GPIOF,GPIO_PIN_7,GPIO_PIN_RESET);
 __HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_4,0);
}


/*将电机输出转化为直观的电机速度函数*/
void Moto1_Speed_Output(int speed)
{
 if(speed>0) Moto1_Go_Forward(speed);
 else 
 {
  if(speed<0) Moto1_Draw_Back(speed);
  else Moto1_Stop();
 }
}

void Moto2_Speed_Output(int speed)
{
 if(speed>0) Moto2_Go_Forward(speed);
 else 
 {
  if(speed<0) Moto2_Draw_Back(speed);
  else Moto2_Stop();
 }
}

void Moto3_Speed_Output(int speed)
{
 if(speed>0) Moto3_Go_Forward(speed);
 else 
 {
  if(speed<0) Moto3_Draw_Back(speed);
  else Moto3_Stop();
 }
}

void Moto4_Speed_Output(int speed)
{
 if(speed>0) Moto4_Go_Forward(speed);
 else 
 {
  if(speed<0) Moto4_Draw_Back(speed);
  else Moto4_Stop();
 }
}

