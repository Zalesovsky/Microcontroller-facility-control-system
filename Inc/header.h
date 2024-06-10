#include "stm32f051x8.h"
#include "math.h"

//Initialization method templates
void RCC_Init(void);
void Digital_Init(void);
void Analog_Init(void);
void Emergency_Init(void);
void Display_Init(void);
void Tumbler_Init(void);
void UART_Init(uint16_t baud);
void TIM6_Init(void);
void TIM14_Init(void);

//UART method templates
void UART_TransmitByte(uint8_t byte);
uint8_t UART_ReceiveByte(void);
void UART_DataHandler(uint8_t byte);

//Timer method templates
void TIM6_SetTime(uint16_t time);
void TIM6_Waiting(void);

//Blocks method templates
void Digital(uint8_t T1);
uint16_t Analog(uint16_t Q, uint8_t T2, uint8_t T3);
void Emergency(uint16_t emergTime);

//Boolean function method template
uint8_t Bool_Func(uint8_t D1, uint8_t D2, uint8_t D3);

//Display method templates
void Display_SetDigit(uint16_t N, uint8_t rank);
uint8_t Get_Digit(uint16_t N, uint8_t rank);
void Display_Reset(void);
void Display_Zero(void);
void Display_One(void);
void Display_Two(void);
void Display_Three(void);
void Display_Four(void);
void Display_Five(void);
void Display_Six(void);
void Display_Seven(void);
void Display_Eight(void);
void Display_Nine(void);
