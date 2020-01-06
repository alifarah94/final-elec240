#include <stm32f4xx.h>	
#include "Interrupts.h"
#include "ADC.h"
#include "LCD.h"
#include "LED.h"
#include "DAC.h"
#include "USART.h"
#include <stdbool.h>
#include "switch.h"


int counter = 0;
int counterred = 0;
float buffer = 0;
int counterbutton = 0;
int total;
int count1 = 0;
bool done = false;


void Timer2setup(void){
	RCC->APB1ENR|=RCC_APB1ENR_TIM2EN;		//timer 2 clock enabled
	TIM2->DIER|=TIM_DIER_UIE;						//timer uptdate interrupt enabled
	TIM2->PSC=32-1;	
	TIM2->ARR=58;  // set to 48000hz
	TIM2->CNT=0;							//zero timer counter
	NVIC->ISER[0]|=(1u<<28);		//timer 2 global interrupt enabled
	TIM2->CR1|=TIM_CR1_CEN;		//start timer counter
}


void Timer3setup(void){
	RCC->APB1ENR|=RCC_APB1ENR_TIM3EN;		//timer 2 clock enabled
	TIM3->DIER|=TIM_DIER_UIE;						//timer uptdate interrupt enabled
	TIM3->PSC=1001-1;	
	TIM3->ARR=9000;  // set to 48000hz
	TIM3->CNT=0;							//zero timer counter
	NVIC->ISER[0]|=(1u<<29);		//timer 2 global interrupt enabled
	TIM3->CR1|=TIM_CR1_CEN;		//start timer counter
}

void button2(void){

RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; //ONLY GPIO C clock enable
RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
GPIOC->MODER &= ~(0x3U<<(2*13)); // turns pin 13 to input 
SYSCFG ->EXTICR[3] |= (0x01<<5); // sets the SYSCFG external interrupt configuration register
EXTI -> IMR |= EXTI_IMR_MR13; // sending a 1 to the 13th bit of the interrupt mask register
EXTI -> RTSR |= EXTI_RTSR_TR13; // send a 1 to the 13th bit of the rising trigger selection register 
	EXTI -> FTSR |= EXTI_FTSR_TR13; // send a 1 to the 13th bit of the rising trigger selection register 
NVIC_EnableIRQ(EXTI15_10_IRQn); //enables the buttons interrupt handler
}

void UsartInterrupt(void){
NVIC->ISER[1]|=(1u<<11);
NVIC_EnableIRQ(USART3_IRQn);
//NVIC_SetPriority(USART3_IRQn,46);
}


void dot(int count){

	if (count>=5000){	
		Toggle_Blue();
		done = true;
	}
}


void dash(int count){

	if (count>=15000){	
		Toggle_Blue();
		done = true;
	}
}


void TIM2_IRQHandler(void)			//TIMER 2 INTERRUPT SERVICE ROUTINE. SET TO 48KHz
{
	

			TIM2->SR&=~TIM_SR_UIF;		//clear interrupt flag in status register
			ADC_DATA=read_adc();			//read value from ADC
			output_dac(ADC_DATA);			//send straight to DAC (DAC pin should replicate ADC pin)
			buffer += ADC_DATA;       // buffer that stores the adc value. 
			counter+=1;               // counter that increments by 1 

	
			// reads buffer after 4800 samples (1/10 of timer)		
			if(counter>=4800){				
			    AnalogueSignal((buffer/4800)); // Prints bar representing voltage
			    ActualVoltage((buffer/4800));  // Prints voltage on LCD
					//morselibary((buffer/4800));    //blinks blue led. morse code
				  Toggle_Red();                    // toggles red LED (48KHz/10)
				  buffer = 0;                    // buffer set to 0
				  counter = 0;                   // counter set to 0
				
				
			if(USART3->DR == '1'){
					//if USART 3 is equal to 1  print DC voltage
					USART_SendString((unsigned char*)"\033[8;1H");
					USART_SendString((unsigned char*)"\033[K");
				USART_SendString((unsigned char*)"Voltage = ");	
					DisplayVoltageUsart(ADC_DATA);
					AnalogueSignalUsart(ADC_DATA);
					output_dac(ADC_DATA);
				}
				
				
				else if(USART3->DR == '2'){
					//if USART 3 is equal to 2  print square wave voltage 
				USART_SendString((unsigned char*)"\033[8;1H");
					USART_SendString((unsigned char*)"\033[K");
					USART_SendString((unsigned char*)"Square wave = ");
					SquareWaveUsart(ADC_DATA);
					
					
				
				}
					else if(USART3->DR == '3'){
						//if USART 3 is equal to 3 print the Triangle wave voltage
				USART_SendString((unsigned char*)"\033[8;1H");
						USART_SendString((unsigned char*)"\033[K");
					USART_SendString((unsigned char*)"Tri wave = ");
					TriangleWaveUsart(ADC_DATA);
				
				
				}
						else if(USART3->DR == '4'){
							//if USART 3 is equal to 4  print the sine wave voltage
				USART_SendString((unsigned char*)"\033[8;1H");
							USART_SendString((unsigned char*)"\033[K");
					USART_SendString((unsigned char*)"Sine wave = ");
					SineWaveUsart(ADC_DATA);
						
		
			}
			
	
			
		
		
}
			}
void USART3_IRQHandler(void)
{
	//interrupt handler for USART3

			}

void TIM3_IRQHandler(void){
			TIM3->SR&=~TIM_SR_UIF;

}

void EXTI15_10_IRQHandler(void){

//EXTI->PR |= EXTI_PR_PR13;
pressed();// function that stops switch bounce
count1=count1+1;

EXTI->PR |= EXTI_PR_PR13;

}
