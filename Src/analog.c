#include "header.h"

uint16_t Analog(uint16_t Q, uint8_t T2, uint8_t T3)
{
	uint16_t convRes = 0;//ADC conversion result
	uint16_t resVal = 0;//Result value (N)
	uint16_t refVol = 2964;//Reference voltage
	uint16_t ADCbits = 4095;//12 bits ADC
	ADC1 -> CR |= ADC_CR_ADSTART;//Start the ADC
	while(~(ADC1 -> ISR & ADC_ISR_EOSEQ));//Waiting when conversion sequence selected channel by ADC complete
	ADC1 -> ISR |= ADC_ISR_EOSEQ;//Cleaning end of sequence flag
	convRes = ADC1 -> DR;//Get conversion result from the last converted channel
	resVal = (convRes * refVol)/ADCbits;//Calculating a value relative to a reference voltage
	//Constant from task > calculating value?
	if(Q > resVal)
	{
		TIM6_SetTime(T2);//Set time interval T2 for signal O2
	}
	else
	{

		TIM6_SetTime(T3);//Set time interval T3 for signal O2
	}
	GPIOA -> BSRR = GPIO_BSRR_BS_8;//Set bit PA8(O2) to 1
	TIM6 -> CR1 |= TIM_CR1_CEN;//TIM6(counter) enabled
	//TIM6 interrupt handler sets PA8(O2) to 0
	return resVal;
}
