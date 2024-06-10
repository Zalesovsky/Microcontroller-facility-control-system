#include "header.h"

void TIM6_SetTime(uint16_t time)
{
	TIM6_Waiting();//Waiting when timer end counting
	TIM6 -> ARR = time;//Set the value(time) in the actual auto-reload register
}

void TIM6_Waiting(void)
{
	while(TIM6 -> CR1 & TIM_CR1_CEN);//Timer is running?
}
