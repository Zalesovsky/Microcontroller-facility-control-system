#include "header.h"

void UART_TransmitByte(uint8_t byte)
{
	//Data is transferred to the shift register?
	if(USART1 -> ISR & USART_ISR_TXE)
	{
		USART1 -> TDR = byte;//Write sending byte in transmit data register
	}
}

void UART_DataHandler(uint8_t byte)
{
	//Received command equals command "D"?
	if(byte == 'D')
	{
		UART_TransmitByte(GPIOA -> ODR & GPIO_ODR_7);//Send PA7(O1) bit to ECM(ЭВМ)
	}
	//Received command equals command "A"?
	if(byte == 'A')
	{
		UART_TransmitByte(GPIOA -> ODR & GPIO_ODR_8);//Send PA8(O2) bit to ECM(ЭВМ)
	}
}
