#include "header.h"

//Clock control initialization
void RCC_Init(void)
{
	RCC -> AHBENR |= RCC_AHBENR_GPIOAEN |
					 RCC_AHBENR_GPIOBEN;//I/O port A and port B clock enable
	RCC -> APB1ENR |= RCC_APB1ENR_TIM6EN |
					  RCC_APB1ENR_TIM14EN;//Timers(TIM6 and TIM14) clock enable
	RCC -> APB2ENR |= RCC_APB2ENR_ADCEN |
					  RCC_APB2ENR_USART1EN;//ADC and USART1 interfaces clock enabled
}

//Digital block initialization
void Digital_Init(void)
{
	GPIOA -> MODER &= ~(GPIO_MODER_MODER3 |
						GPIO_MODER_MODER4 |
						GPIO_MODER_MODER5 |
						GPIO_MODER_MODER6);//Input mode PA3-PA6(D0-D3)
	GPIOA -> MODER |= GPIO_MODER_MODER7_0;//Output mode PA7(O1)
	GPIOA -> BSRR |= GPIO_BSRR_BS_7;//Set PA7(O1)
	GPIOA -> PUPDR |= GPIO_PUPDR_PUPDR3_0 |
					 GPIO_PUPDR_PUPDR4_0 |
					 GPIO_PUPDR_PUPDR5_0 |
					 GPIO_PUPDR_PUPDR6_0;//Pull-up mode PA3-PA6
	SYSCFG -> EXTICR[1] &= ~ SYSCFG_EXTICR1_EXTI3_PA;//Select input PA3 for the external interrupt
	EXTI -> IMR |= EXTI_IMR_MR3;//Interrupt request from Line 3 is masked
	EXTI -> FTSR |= EXTI_FTSR_FT3;//Falling trigger enabled (for Event and interrupt) for input line 3
	NVIC_SetPriority(EXTI2_3_IRQn, 0);//Set higher priority for D0
	NVIC_EnableIRQ(EXTI2_3_IRQn);
}

//Analog block initialization
void Analog_Init(void)
{
	GPIOA -> MODER |= GPIO_MODER_MODER8_0;//Output mode PA8(O2)
	GPIOA -> MODER |= GPIO_MODER_MODER1;//Analog mode PA1(A) for ADC
	GPIOA -> BSRR |= GPIO_BSRR_BS_8;//Set bit PA8(O2) to 1
	//Set CONT=0 and EXTSEL=0x0 for clearing ADSTART bit by hardware after ADC conversion
	ADC1 -> CFGR1 &= ~ADC_CFGR1_CONT;//Single conversion mode
	ADC1 -> CFGR1 &= ~(0x7 << ADC_CFGR1_EXTSEL_Pos);//Set EXTSEL=0x0
	ADC1 -> CFGR2 |= ADC_CFGR2_CKMODE_0;//ADC clock source PCLK divided by 2
	ADC1 -> SMPR |= ADC_SMPR_SMP_0;//Sampling time selection 7.5 ADC clock cycles
	ADC1 -> CHSELR |= ADC_CHSELR_CHSEL1;//Input Channel 1(PA1) is selected for conversion
	ADC1 -> IER |= ADC_IER_EOSEQIE;//End of conversion sequence interrupt enable
	ADC1 -> CR |= ADC_CR_ADCAL;//Write 1 to calibrate the ADC
	while(ADC1 -> CR & ADC_CR_ADCAL);//Calibration complete?
	ADC1 -> CR |= ADC_CR_ADEN;//ADC interface clock enabled
}

//Emergency block initialization
void Emergency_Init(void)
{
	GPIOA -> MODER |= GPIO_MODER_MODER2_0;//Output mode PA2(ES)
	GPIOA -> BSRR |= GPIO_BSRR_BR_2;//Reset PA2(ES)
}

//Display block initialization
void Display_Init(void)
{
	GPIOB -> MODER |= GPIO_MODER_MODER0_0 |
					  GPIO_MODER_MODER1_0 |
					  GPIO_MODER_MODER2_0 |
					  GPIO_MODER_MODER3_0 |
					  GPIO_MODER_MODER4_0 |
					  GPIO_MODER_MODER5_0 |
					  GPIO_MODER_MODER6_0 |
					  GPIO_MODER_MODER7_0 |
					  GPIO_MODER_MODER8_0 |
					  GPIO_MODER_MODER9_0 |
					  GPIO_MODER_MODER10_0 |
					  GPIO_MODER_MODER11_0;//Output mode PB0-PB11(S0-S7, G0-G3)
	GPIOB -> BSRR |= GPIO_BSRR_BR_0 |
					 GPIO_BSRR_BR_1 |
					 GPIO_BSRR_BR_2 |
					 GPIO_BSRR_BR_3 |
					 GPIO_BSRR_BR_4 |
					 GPIO_BSRR_BR_5 |
					 GPIO_BSRR_BR_6 |
					 GPIO_BSRR_BR_7 |
					 GPIO_BSRR_BR_8 |
					 GPIO_BSRR_BR_9 |
					 GPIO_BSRR_BR_10 |
					 GPIO_BSRR_BR_11;//Reset PB0-PB11(S0-S7, G0-G3)
}

void Tumbler_Init(void)
{
	GPIOA -> MODER &= ~GPIO_MODER_MODER11;//Input mode PA11(ST)
	GPIOA -> PUPDR |= GPIO_PUPDR_PUPDR11_0;//Pull-up mode PA11(ST)
}

//UART initialization
void UART_Init(uint16_t baud)
{
	GPIOA -> MODER |= GPIO_MODER_MODER9_1 |
					  GPIO_MODER_MODER10_1;//Alternate function mode PA9, PA10(TX, RX)
	GPIOA -> OSPEEDR |= GPIO_OSPEEDER_OSPEEDR9 |
						GPIO_OSPEEDER_OSPEEDR10;//Configure the I/O PA9, PA10(TX, RX) high output speed
	GPIOA -> AFR[1] |= (0x01 << GPIO_AFRH_AFRH1_Pos) |
					   (0x01 << GPIO_AFRH_AFRH2_Pos);//Alternate function(AF1) selection for PA9, PA10(TX, RX)
	USART1->BRR = 8000000/baud;//Set USARTDIV in baud rate register(Tx/Rx baud = fCK / USARTDIV)
	USART1->CR1 |= USART_CR1_TE |
				   USART_CR1_RE |
				   USART_CR1_RXNEIE |
				   USART_CR1_TXEIE |
				   USART_CR1_UE;//Transmitter, receiver, receive interrupt, transmit interrupt, UART enable
	NVIC_SetPriority(USART1_IRQn, 4);//Set priority for USART
	NVIC_EnableIRQ(USART1_IRQn);
}

//Timer 6 initialization
void TIM6_Init(void)
{
	TIM6 -> DIER |= TIM_DIER_UIE;//Update interrupt enabled
	TIM6 -> PSC = 7999;//Set timer prescaler [Clock timer frequency = 8MHz / (7999 + 1) = 1kHz]
	NVIC_SetPriority(TIM6_DAC_IRQn, 1);//Set priority for timer
	NVIC_EnableIRQ(TIM6_DAC_IRQn);
}

//Timer 14 initialization
void TIM14_Init(void)
{
	TIM6 -> DIER |= TIM_DIER_UIE;//Update interrupt enabled
	TIM6 -> PSC = 7999;//Set timer prescaler [Clock timer frequency = 8MHz / (7999 + 1) = 1kHz]
	TIM6 -> ARR = 1;//Set the value(time) in the actual auto-reload register
	NVIC_SetPriority(TIM14_IRQn, 2);//Set priority for timer
	NVIC_EnableIRQ(TIM14_IRQn);
}
