#ifndef _INTERRUPTS_H_



#include <stm32f4xx.h>		//INCLUDE THE HEADER FILE FOR THIS MCU FAMILY
															//this file contains the definitions for register addresses and values etc...ADC

extern unsigned short ADC_DATA;

void dot(int count);
void dash(int count);
void Timer2setup(void); // timer 2 inistialise 
void Timer3setup(void); // timer 3 inistialise 
void TIM2_IRQHandler(void);			//TIMER 2 INTERRUPT SERVICE ROUTINE
void TIM3_IRQHandler(void);			//TIMER 3 INTERRUPT SERVICE ROUTINE
void button2(void);  // initalises button
void UsartInterrupt(void); //  //button INTERRUPT SERVICE ROUTINE

#endif		