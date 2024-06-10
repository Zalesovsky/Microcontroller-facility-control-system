#include "header.h"

void Digital(uint8_t T1)
{
	TIM6_SetTime(T1);//Set time interval T1 for signal O1
	//Boolean function equals 1?
	if(Bool_Func(GPIOA -> IDR & GPIO_IDR_4,
				 GPIOA -> IDR & GPIO_IDR_5,
				 GPIOA -> IDR & GPIO_IDR_6))
	{
		GPIOA -> BSRR |= GPIO_BSRR_BR_7;//Set bit PA7(O1) to 0
		TIM6 -> CR1 |= TIM_CR1_CEN;//TIM6(counter) enabled
		//TIM6 interrupt handler sets PA7(O1) to 0
	}
}

uint8_t Bool_Func(uint8_t D1, uint8_t D2, uint8_t D3)
{
	return (~D1 & D2) | D3;//Boolean function from task[(!D1 && D2) || D3]
}
