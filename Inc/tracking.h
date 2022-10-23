#ifndef __TRACKING_H_
#define __TRACKING_H_

void Read_GPIO(void);
void Out_flag_reset(void); 
void Tracking_Move(void);
void Tracking_Switch_Mode(void);
void Tracking_Switch_Mode2(void);
void Tracking_Switch_Mode3(void);



extern int Rx_Flag_Reset2;//数据清零判断位，0为未清零，1为已清零

#endif
