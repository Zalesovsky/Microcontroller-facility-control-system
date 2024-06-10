#include "header.h"

void Display_SetDigit(uint16_t N, uint8_t rank)
{
	uint8_t digit = Get_Digit(N, rank);//Get digit from the number of the corresponding rank
	//Set digit on display
	if(digit == 0)
	{
    	Display_Zero();
	}
	if(digit == 1)
	{
    	Display_One();
	}
	if(digit == 2)
	{
    	Display_Two();
	}
	if(digit == 3)
	{
    	Display_Three();
	}
	if(digit == 4)
	{
    	Display_Four();
	}
	if(digit == 5)
	{
    	Display_Five();
	}
	if(digit == 6)
	{
    	Display_Six();
	}
	if(digit == 7)
	{
    	Display_Seven();
	}
	if(digit == 8)
	{
    	Display_Eight();
	}
	if(digit == 9)
	{
    	Display_Nine();
	}
	else
	{
		Display_Reset();
	}

	//Select rank number of display
	if(rank == 1)
	{
		GPIOB -> BSRR |= GPIO_BSRR_BR_8 |
						 GPIO_BSRR_BS_11;//Enable G0 and disable G3
	}
	if(rank == 2)
	{
		GPIOB -> BSRR |= GPIO_BSRR_BR_9 |
						 GPIO_BSRR_BS_8;//Enable G1 and disable G0
	}
	if(rank == 3)
	{
		GPIOB -> BSRR |= GPIO_BSRR_BR_10 |
						 GPIO_BSRR_BS_9;//Enable G2 and disable G1
	}
	if(rank == 4)
	{
		GPIOB -> BSRR |= GPIO_BSRR_BR_11 |
						 GPIO_BSRR_BS_10;//Enable G3 and disable G2
	}
	else
	{
		GPIOB -> BSRR |= GPIO_BSRR_BS_8 |
						 GPIO_BSRR_BS_9 |
						 GPIO_BSRR_BS_10 |
						 GPIO_BSRR_BS_11;//Disable G0-G3
	}
}

uint8_t Get_Digit(uint16_t N, uint8_t rank)
{
	uint8_t digit = 0;//Result
	//Do this while rank of value will not coincide with rank of display
	for(;rank > 0; rank--)
	{
		digit = N % 10;//Get digit at this rank(1) (1234 % 10 = 4)
		N /= 10;//Move to the next rank(1234 / 10 = (int)123)
	}
	return digit;//Return result
}

void Display_Reset(void)
{
	GPIOB -> BSRR |= GPIO_BSRR_BR_0 |
					 GPIO_BSRR_BR_1 |
					 GPIO_BSRR_BR_2 |
					 GPIO_BSRR_BR_3 |
					 GPIO_BSRR_BR_4 |
					 GPIO_BSRR_BR_5 |
					 GPIO_BSRR_BR_6 |
					 GPIO_BSRR_BR_7;//Reset a,b,c,d,e,f,g,dp
}

void Display_Zero(void)
{
	GPIOB -> BSRR |= GPIO_BSRR_BS_0 |
					 GPIO_BSRR_BS_1 |
					 GPIO_BSRR_BS_2 |
					 GPIO_BSRR_BS_3 |
					 GPIO_BSRR_BS_4 |
					 GPIO_BSRR_BS_5 |
					 GPIO_BSRR_BR_6 |
					 GPIO_BSRR_BR_7;//0 = a,b,c,d,e,f
}

void Display_One(void)
{
	GPIOB -> BSRR |= GPIO_BSRR_BR_0 |
					 GPIO_BSRR_BS_1 |
					 GPIO_BSRR_BS_2 |
					 GPIO_BSRR_BR_3 |
					 GPIO_BSRR_BR_4 |
					 GPIO_BSRR_BR_5 |
					 GPIO_BSRR_BR_6 |
					 GPIO_BSRR_BR_7;//1 = b,c
}

void Display_Two(void)
{
	GPIOB -> BSRR |= GPIO_BSRR_BS_0 |
					 GPIO_BSRR_BS_1 |
					 GPIO_BSRR_BR_2 |
					 GPIO_BSRR_BS_3 |
					 GPIO_BSRR_BS_4 |
					 GPIO_BSRR_BR_5 |
					 GPIO_BSRR_BS_6 |
					 GPIO_BSRR_BR_7;//2 = a,b,d,e,g
}

void Display_Three(void)
{
	GPIOB -> BSRR |= GPIO_BSRR_BS_0 |
					 GPIO_BSRR_BS_1 |
					 GPIO_BSRR_BS_2 |
					 GPIO_BSRR_BS_3 |
					 GPIO_BSRR_BR_4 |
					 GPIO_BSRR_BR_5 |
					 GPIO_BSRR_BS_6 |
					 GPIO_BSRR_BR_7;//3 = a,b,c,d,g
}

void Display_Four(void)
{
	GPIOB -> BSRR |= GPIO_BSRR_BR_0 |
					 GPIO_BSRR_BS_1 |
					 GPIO_BSRR_BS_2 |
					 GPIO_BSRR_BR_3 |
					 GPIO_BSRR_BR_4 |
					 GPIO_BSRR_BS_5 |
					 GPIO_BSRR_BS_6 |
					 GPIO_BSRR_BR_7;//4 = b,c,f,g
}

void Display_Five(void)
{
	GPIOB -> BSRR |= GPIO_BSRR_BS_0 |
					 GPIO_BSRR_BR_1 |
					 GPIO_BSRR_BS_2 |
					 GPIO_BSRR_BS_3 |
					 GPIO_BSRR_BR_4 |
					 GPIO_BSRR_BS_5 |
					 GPIO_BSRR_BS_6 |
					 GPIO_BSRR_BR_7;//5 = a,c,d,f,g
}

void Display_Six(void)
{
	GPIOB -> BSRR |= GPIO_BSRR_BS_0 |
					 GPIO_BSRR_BR_1 |
					 GPIO_BSRR_BS_2 |
					 GPIO_BSRR_BS_3 |
					 GPIO_BSRR_BS_4 |
					 GPIO_BSRR_BS_5 |
					 GPIO_BSRR_BS_6 |
					 GPIO_BSRR_BR_7;//6 = a,c,d,e,f,g
}

void Display_Seven(void)
{
	GPIOB -> BSRR |= GPIO_BSRR_BS_0 |
					 GPIO_BSRR_BS_1 |
					 GPIO_BSRR_BS_2 |
					 GPIO_BSRR_BR_3 |
					 GPIO_BSRR_BR_4 |
					 GPIO_BSRR_BR_5 |
					 GPIO_BSRR_BR_6 |
					 GPIO_BSRR_BR_7;//7 = a,b,c
}

void Display_Eight(void)
{
	GPIOB -> BSRR |= GPIO_BSRR_BS_0 |
					 GPIO_BSRR_BS_1 |
					 GPIO_BSRR_BS_2 |
					 GPIO_BSRR_BS_3 |
					 GPIO_BSRR_BS_4 |
					 GPIO_BSRR_BS_5 |
					 GPIO_BSRR_BS_6 |
					 GPIO_BSRR_BR_7;//8 = a,b,c,d,e,f,g
}

void Display_Nine(void)
{
	GPIOB -> BSRR |= GPIO_BSRR_BS_0 |
					 GPIO_BSRR_BS_1 |
					 GPIO_BSRR_BS_2 |
					 GPIO_BSRR_BS_3 |
					 GPIO_BSRR_BR_4 |
					 GPIO_BSRR_BS_5 |
					 GPIO_BSRR_BS_6 |
					 GPIO_BSRR_BR_7;//9 = a,b,c,d,f,g
}
