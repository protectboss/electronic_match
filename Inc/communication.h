#ifndef __COMMUNICATION_H_
#define __COMMUNICATION_H_

#include "usart.h"

void Communication_Init(void);
void Communication_Judge_Nano(void);
void Communication_Jude_Mv(void);
void Search_Room_Reset(void);


extern uint8_t Run_Judge;
extern uint8_t Mv_Message;


#endif

