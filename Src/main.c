#include "header.h"

//Output signal parameters from task[T1 = 55 ms, T2 = 89 ms, T3 = 21 ms]
uint8_t T1 = 55;
uint8_t T2 = 89;
uint8_t T3 = 21;

uint16_t N = 0;//ADC 12-bits code
uint16_t Q = 1000;//Constant from task(Variant * 100) to comparison

uint8_t emergFlag= 0;//Emergency flag(0 - emergency stop signal is not received, 1 - emergency stop signal is received)
uint16_t emergTime = 2;//Time emergency signal (1s/(250Hz * 2)= 2ms)

uint16_t baudRate = 2400;//Baud rate

uint8_t rank = 0;//Display rank number

uint8_t controlSymb = 0;//Exchange control symbol "?"

int main(void)
{
	//Initialization
	RCC_Init();
	Digital_Init();
	Analog_Init();
	Emergency_Init();
	Display_Init();
	Tumbler_Init();
	UART_Init(baudRate);
	TIM6_Init();
	TIM14_Init();
	for(;;)
	{
		Digital(T1);//Execute digital block
		N = Analog(Q, T2, T3);//Execute analog block and write result to N
		while(~(GPIOA -> IDR & GPIO_IDR_11));//Waiting if tumbler enable
	}
}

//Emergency sensor channel handler
void EXTI2_3_IRQHandler(void)
{
	//Selected trigger[PA3(D0)] request occurred?
	if(EXTI -> PR & EXTI_PR_PR3)
	{
		EXTI -> PR |= EXTI_PR_PR3;//Clearing this bit by writing "1"
		emergFlag = 1;//Emergency stop signal is received
		Emergency(emergTime);//Stop system
	}
}

//UART interface handler
void USART1_IRQHandler(void)
{
	//Received data is ready to be read?
	if(USART1->ISR & USART_ISR_RXNE)
	{
		//Is the Received byte a control symbol?
		if(controlSymb == '?')
		{
			UART_DataHandler(USART1 -> RDR);//Read received data
			controlSymb = 0;//Clear control symbol
		}
		else
		{
			controlSymb = USART1 -> RDR;//Read byte
		}
	}
}

//Timer 6 handler
void TIM6_DAC_IRQHandler(void)
{
	//Timer counter is overflow?
	if(TIM6 -> SR & TIM_SR_UIF)
	{
		TIM6 -> SR &= ~TIM_SR_UIF;//Set bit on an update event to 0
		//Bit PA7(O1) equals 1?
		if(GPIOA -> ODR & GPIO_ODR_7)
		{
			GPIOA -> BSRR |= GPIO_BSRR_BS_7;//Set bit PA7(O1) to 1
			TIM6 -> CR1 &= ~TIM_CR1_CEN;//Disable timer
		}
		//Bit PA8(O2) equals 1?
		if(GPIOA -> ODR & GPIO_ODR_8)
		{
			GPIOA -> BSRR |= GPIO_BSRR_BS_8;//Set bit PA8(O2) to 1
			TIM6 -> CR1 &= ~TIM_CR1_CEN;//Disable timer
		}
		//Bit PA2(ES) equals 1?
		if(emergFlag)
		{
			GPIOA -> ODR &= ~(GPIOA -> ODR & GPIO_ODR_2);//Invert bit PA2(ES)
		}
	}
}

//Timer 14 handler
void TIM14_IRQHandler(void)
{
	//Timer counter is overflow?
	if(TIM14 -> SR & TIM_SR_UIF)
	{
		TIM14 -> SR &= ~TIM_SR_UIF;//Set bit on an update event to 0
		//Check rank of display
		if(rank < 4)
		{
			rank += 1;//Select next rank
			Display_SetDigit(N, rank);//Display selected digit
		}
		else
		{
			rank = 0;//Reset rank
		}
	}
}
