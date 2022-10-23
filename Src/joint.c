#include "joint.h"
#include "tim.h"
#include "mode.h"
#include "room_search.h"


#define box_set 0 //������ͨ����
#define box_push 1500 //�����Ƴ�
#define box_pull 2500 //�����߻���

#define yaw_ahead 2070 //yaw�ᳯǰ

#define pitch_clamping 3300 //����pitch��ȡλ��
#define pitch_place 1300 //����pitch���ú���λ��
#define pitch_normal 2300 //����pitch�����ڷ�λ��

#define clip_open 1680 //���Ӵ�
#define clip_close 2600 //���ӹر� 

#define box_open 2500 //���Ӵ�
#define box_close 1340 //���ӹر�


void Joint_Init(void)
{
 HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_1);//360�����500-2000˳ʱ����ת����2000-2500��ʱ����ת
 HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_2);//ת��yaw�ؽ�2040ʱ��Ϊ����
 HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_3);//ת��pitch�ؽ�1300����λ��3000ץȡλ��
 HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_4);//��ȡ  1780�ſ�2300�ر�
 HAL_TIM_PWM_Start(&htim9,TIM_CHANNEL_1);
 HAL_TIM_PWM_Start(&htim9,TIM_CHANNEL_2);
}


void Joint_Move(int box_position,int yaw,int pitch,int clip,int box_cap)
{
 __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_1,box_position);
 __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_2,yaw);
 __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_3,pitch);
 __HAL_TIM_SetCompare(&htim8,TIM_CHANNEL_4,clip);
 __HAL_TIM_SetCompare(&htim9,TIM_CHANNEL_1,box_cap);
}

int32_t Joint_time=0;
int16_t Joint_mode_time[6];
int32_t Joint_time_sum[6];

void Joint_time_Init(void)
{
 Joint_mode_time[0]=400;//����ǰ��      �������ٵ�λΪ��
 Joint_mode_time[1]=100;//����ץȡ         ��λ5ms
 Joint_mode_time[2]=400;//���������ľ��
 Joint_mode_time[3]=300;//�򿪺���
 Joint_mode_time[4]=100;//�򿪼���
 Joint_mode_time[5]=200;//�رպ���
}

void Joint_Time_Sum(void)
{
	Joint_time_sum[0]=Joint_mode_time[0];
  Joint_time_sum[1]=Joint_mode_time[0]+Joint_mode_time[1];
	Joint_time_sum[2]=Joint_mode_time[0]+Joint_mode_time[1]+Joint_mode_time[2];
	Joint_time_sum[3]=Joint_mode_time[0]+Joint_mode_time[1]+Joint_mode_time[2]+Joint_mode_time[3];
	Joint_time_sum[4]=Joint_mode_time[0]+Joint_mode_time[1]+Joint_mode_time[2]+Joint_mode_time[3]+Joint_mode_time[4];
	Joint_time_sum[5]=Joint_mode_time[0]+Joint_mode_time[1]+Joint_mode_time[2]+Joint_mode_time[3]+Joint_mode_time[4]+Joint_mode_time[5];
}

void Joint_Clamping(void)
{
	Joint_time++;
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_13,GPIO_PIN_SET);//������
 if(Joint_time<Joint_time_sum[0])
 { 	
	 Joint_Move(box_set,yaw_ahead,pitch_clamping,clip_open,box_close);//����ǰ��
 }

 if((Joint_time_sum[0]<Joint_time)&&(Joint_time<Joint_time_sum[1]))
 { 	
 	 Joint_Move(box_set,yaw_ahead,pitch_clamping,clip_close,box_close);//����ץȡ���
 }

 if((Joint_time_sum[1]<Joint_time)&&(Joint_time<Joint_time_sum[2]))
 {
	 Joint_Move(box_set,yaw_ahead,pitch_place,clip_close,box_close);//���������ľ��
 }

 if((Joint_time_sum[2]<Joint_time)&&(Joint_time<Joint_time_sum[3]))
 {
	 Joint_Move(box_set,yaw_ahead,pitch_place,clip_close,box_open);//�򿪺���
 }

 if((Joint_time_sum[3]<Joint_time)&&(Joint_time<Joint_time_sum[4]))
 {
 	 Joint_Move(box_set,yaw_ahead,pitch_place,clip_open,box_open);//�򿪼���
 }
 
 if((Joint_time_sum[4]<Joint_time)&&(Joint_time<Joint_time_sum[5]))
 {
   Joint_Move(box_set,yaw_ahead,pitch_place,clip_open,box_close);//�رպ���
 }
}

void Joint_Switch_Mode(void)
{
 if(Joint_time>Joint_time_sum[5])
 {
   Joint_time=0;
	 ELECTRONIC_CAR_MODE=3;
	 HAL_GPIO_WritePin(GPIOE,GPIO_PIN_13,GPIO_PIN_RESET);//�ر�����
 }
}


void Turn_Back(void)
{
 if(Joint_time>Joint_time_sum[5])
 {
   Joint_time=0;
	 Turn_back_MODE=2;
	 HAL_GPIO_WritePin(GPIOE,GPIO_PIN_13,GPIO_PIN_RESET);//�ر�����
 }
}


void Joint_Normal(void)
{
	 Joint_Move(box_set,yaw_ahead,pitch_normal,clip_open,box_close);//���������ڷ�
}

void Throw_rubbish(void)
{
	 Joint_Move(box_push,yaw_ahead,pitch_normal,clip_open,box_close);//�����Ƴ�
}

void Recycling_Line(void)
{
	 Joint_Move(box_pull,yaw_ahead,pitch_normal,clip_open,box_close);//�߻���
}

void Recycling_rubbish(void)
{
	 Joint_Move(box_set,yaw_ahead,pitch_normal,clip_open,box_open);//���������ڷ�,���Ӹ��Ӵ�

}

void Clamping_RUbbish(void)
{
	Joint_Move(box_set,yaw_ahead,pitch_clamping,clip_close,box_close);//����ץȡ���
}
