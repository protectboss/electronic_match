#include "pid.h"
#include "tim.h"


#define LIMIT(x,min,max) x=(x<(min)?min:((x>=max)?max:x))


/*位置pid*/
void WZPid(WZPID_TypeDef *WZpid,float target,float real)
{
 WZpid->error_last=WZpid->error;
 WZpid->error=target-real;
 WZpid->output=(WZpid->error-WZpid->error_last)*WZpid->Kd;//微分部分
 WZpid->output+=(WZpid->error*WZpid->Kp);//误差部分
 WZpid->integral+=(WZpid->error*WZpid->Ki);//积分部分 
 LIMIT(WZpid->integral,-WZpid->integral_max,WZpid->integral_max);
 WZpid->output+=WZpid->integral;
 LIMIT(WZpid->output,-WZpid->output_max,WZpid->output_max);
}

void WZPid_Init(WZPID_TypeDef *WZpid,float p,float i,float d,float Integral_max,float Out_max)
{
 WZpid->Kp=p;
 WZpid->Ki=i;
 WZpid->Kd=d;
 WZpid->integral_max=Integral_max;
 WZpid->output_max=Out_max;
}


WZPID_NumberTypeDef Pid;
void ALL_Pid_Init(void)
{
 WZPid_Init(&Pid.No1,4,0.2,0,95,95);
 WZPid_Init(&Pid.No2,4,0.2,0,95,95);
 WZPid_Init(&Pid.No3,4,0.2,0,95,95);
 WZPid_Init(&Pid.No4,4,0.2,0,95,95);
}



