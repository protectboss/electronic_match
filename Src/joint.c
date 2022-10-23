#include "joint.h"
#include "tim.h"
#include "mode.h"
#include "room_search.h"


#define box_set 0 //盒子普通放置
#define box_push 1500 //盒子推出
#define box_pull 2500 //盒子线回收

#define yaw_ahead 2070 //yaw轴朝前

#define pitch_clamping 3300 //夹子pitch夹取位置
#define pitch_place 1300 //夹子pitch放置盒子位置
#define pitch_normal 2300 //夹子pitch正常摆放位置

#define clip_open 1680 //夹子打开
#define clip_close 2600 //夹子关闭 

#define box_open 2500 //盒子打开
#define box_close 1340 //盒子关闭


void Joint_Init(void)
{
 HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_1);//360舵机在500-2000顺时钟旋转、在2000-2500逆时针旋转
 HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_2);//转向yaw关节2040时候为正面
 HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_3);//转向pitch关节1300放置位置3000抓取位置
 HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_4);//夹取  1780张开2300关闭
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
 Joint_mode_time[0]=400;//夹子前伸      除以两百单位为秒
 Joint_mode_time[1]=100;//夹子抓取         单位5ms
 Joint_mode_time[2]=400;//夹子往后摆木块
 Joint_mode_time[3]=300;//打开盒子
 Joint_mode_time[4]=100;//打开夹子
 Joint_mode_time[5]=200;//关闭盒子
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
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_13,GPIO_PIN_SET);//打开消毒
 if(Joint_time<Joint_time_sum[0])
 { 	
	 Joint_Move(box_set,yaw_ahead,pitch_clamping,clip_open,box_close);//夹子前伸
 }

 if((Joint_time_sum[0]<Joint_time)&&(Joint_time<Joint_time_sum[1]))
 { 	
 	 Joint_Move(box_set,yaw_ahead,pitch_clamping,clip_close,box_close);//夹子抓取物块
 }

 if((Joint_time_sum[1]<Joint_time)&&(Joint_time<Joint_time_sum[2]))
 {
	 Joint_Move(box_set,yaw_ahead,pitch_place,clip_close,box_close);//夹子往后摆木块
 }

 if((Joint_time_sum[2]<Joint_time)&&(Joint_time<Joint_time_sum[3]))
 {
	 Joint_Move(box_set,yaw_ahead,pitch_place,clip_close,box_open);//打开盒子
 }

 if((Joint_time_sum[3]<Joint_time)&&(Joint_time<Joint_time_sum[4]))
 {
 	 Joint_Move(box_set,yaw_ahead,pitch_place,clip_open,box_open);//打开夹子
 }
 
 if((Joint_time_sum[4]<Joint_time)&&(Joint_time<Joint_time_sum[5]))
 {
   Joint_Move(box_set,yaw_ahead,pitch_place,clip_open,box_close);//关闭盒子
 }
}

void Joint_Switch_Mode(void)
{
 if(Joint_time>Joint_time_sum[5])
 {
   Joint_time=0;
	 ELECTRONIC_CAR_MODE=3;
	 HAL_GPIO_WritePin(GPIOE,GPIO_PIN_13,GPIO_PIN_RESET);//关闭消毒
 }
}


void Turn_Back(void)
{
 if(Joint_time>Joint_time_sum[5])
 {
   Joint_time=0;
	 Turn_back_MODE=2;
	 HAL_GPIO_WritePin(GPIOE,GPIO_PIN_13,GPIO_PIN_RESET);//关闭消毒
 }
}


void Joint_Normal(void)
{
	 Joint_Move(box_set,yaw_ahead,pitch_normal,clip_open,box_close);//夹子正常摆放
}

void Throw_rubbish(void)
{
	 Joint_Move(box_push,yaw_ahead,pitch_normal,clip_open,box_close);//盒子推出
}

void Recycling_Line(void)
{
	 Joint_Move(box_pull,yaw_ahead,pitch_normal,clip_open,box_close);//线回收
}

void Recycling_rubbish(void)
{
	 Joint_Move(box_set,yaw_ahead,pitch_normal,clip_open,box_open);//夹子正常摆放,盒子盖子打开

}

void Clamping_RUbbish(void)
{
	Joint_Move(box_set,yaw_ahead,pitch_clamping,clip_close,box_close);//夹子抓取物块
}
