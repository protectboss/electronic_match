#include "encoder.h"
#include "tim.h"
#include "chassis.h"

void Encoder_Init(void)
{
HAL_TIM_Encoder_Start(&htim1,TIM_CHANNEL_ALL);
HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_ALL);
HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_ALL);
HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_ALL);
}

void Read_Encoder_Speed(void)
{
 MotoData.Moto1.encoder=(short)(__HAL_TIM_GetCounter(&htim1));
 __HAL_TIM_SET_COUNTER(&htim1,0);
 MotoData.Moto2.encoder=(short)(__HAL_TIM_GetCounter(&htim2));
 __HAL_TIM_SET_COUNTER(&htim2,0);
 MotoData.Moto3.encoder=(short)(__HAL_TIM_GetCounter(&htim3));
 __HAL_TIM_SET_COUNTER(&htim3,0);
 MotoData.Moto4.encoder=(short)(__HAL_TIM_GetCounter(&htim4));
 __HAL_TIM_SET_COUNTER(&htim4,0);
}


Encoder_Sum_TypeDef Encoder_Sum;

void Read_Encoder_Sum(void)
{
 MotoData.Moto1.encoder=(short)(__HAL_TIM_GetCounter(&htim1));
 Encoder_Sum.Moto1+=(short)(__HAL_TIM_GetCounter(&htim1));
 __HAL_TIM_SET_COUNTER(&htim1,0);
	
 MotoData.Moto2.encoder=(short)(__HAL_TIM_GetCounter(&htim2));
 Encoder_Sum.Moto2+=(short)(__HAL_TIM_GetCounter(&htim2));
 __HAL_TIM_SET_COUNTER(&htim2,0);
	
 MotoData.Moto3.encoder=(short)(__HAL_TIM_GetCounter(&htim3));
 Encoder_Sum.Moto3+=(short)(__HAL_TIM_GetCounter(&htim3));
 __HAL_TIM_SET_COUNTER(&htim3,0);
	
 MotoData.Moto4.encoder=(short)(__HAL_TIM_GetCounter(&htim4));
 Encoder_Sum.Moto4+=(short)(__HAL_TIM_GetCounter(&htim4));
 __HAL_TIM_SET_COUNTER(&htim4,0);
}

void Encoder_Sum_Zero(void)
{
Encoder_Sum.Moto1=0;
Encoder_Sum.Moto2=0;
Encoder_Sum.Moto3=0;
Encoder_Sum.Moto4=0;
}
void Encoder_Zero(void)
{
 __HAL_TIM_SET_COUNTER(&htim1,0);
 __HAL_TIM_SET_COUNTER(&htim2,0);
 __HAL_TIM_SET_COUNTER(&htim3,0);
 __HAL_TIM_SET_COUNTER(&htim4,0);
}
