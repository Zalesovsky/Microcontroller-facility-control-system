#include "header.h"

void Emergency(uint16_t emergTime)
{
	GPIOA -> BSRR |= GPIO_BSRR_BS_7 |
					 GPIO_BSRR_BS_8;//Set bit PA7(O1), PA8(O2) to 1
	GPIOA -> LCKR |= GPIO_LCKR_LCK7 |
					 GPIO_LCKR_LCK8;//Port configuration lock key active(the value of the port bit can no longer be modified until the next reset)
	TIM6 -> CR1 &= ~TIM_CR1_CEN;//Disable timer
	TIM6_SetTime(emergTime);//Set time interval for signal ES
	GPIOA -> BSRR |= GPIO_BSRR_BR_2;//Set bit PA2(ES) to 1
	TIM6 -> CR1 |= TIM_CR1_CEN;//TIM6(counter) enabled
	//TIM6 interrupt handler invert PA2(ES)
	TIM14 -> CR1 |= TIM_CR1_CEN;//TIM14(display) enabled
	for(;;);//Waiting reboot
}
