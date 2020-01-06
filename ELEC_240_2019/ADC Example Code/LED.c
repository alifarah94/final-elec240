#include <stm32f4xx.h>		//INCLUDE THE HEADER FILE FOR THIS MCU FAMILY
													//this file contains the definitions for register addresses and values etc...
#include "LED.h"
#include "Interrupts.h"
#include "LCD.H"
#include <stdbool.h>
#include "string.h"
#include "stdio.h"

bool redcount = false; // bool for red led to keep record if on or not
bool bluecount = false; // bool for blue led to keep record if on or not
bool greencount = false; // bool for green led to keep record if on or not

float sum1;


void Userinputdelay(unsigned int delay){

int count = 0; // DECLARED AND INITIALIZED COUNTER 
	
//incrementing a variable from 0 to However much the user desires 
while(count<delay){
count++;
}


}

void whiledelay (void){

int count = 0;  // DECLARED AND INITIALIZED COUNTER 
	
//incrementing a variable from 0 to 4,500,000 takes 100ms when MCU speed is 180MHz	
while(count<SystemCoreClock/180){
count++;
}



}
void delay (void)
{	
	unsigned int i;		//create variable
	for (i=0; i<1000000; i++);		//WAIT count to 1 million 
}


		//100ms BLOCKING DELAY
void delay_100ms_blocking(void)
{
	unsigned int i;				//increment a variable to waste time
	for(i=0; i<SystemCoreClock/180; i++);		//incrementing a variable from 0 to 4,500,000 takes 100ms when MCU speed is 180MHz
}




void LED_INIT (void){
//ENABLE PORT(S)
//RCC->AHB1ENR |= 0x02; //use label defined in stm32f4.h instead of hex value: easier to read and change
RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; //ONLY GPIO B clock enable
	
//CONFIGURE PORT:GPIOB  PIN:0 TO OUTPUT for LED1 (Green)
GPIOB->MODER |= 0x01; //ONLY set  GPIOB0
// the above assumes that bit 1 is to zero
GPIOB->MODER &= ~0x02; //ONLY clear GPIOB1
	
//CONFIGURE PORT:GPIOB  PIN:7 TO OUTPUT for LED2 (Blue)
GPIOB->MODER |= 0x01<<(7*2); //ONLY set  GPIOB7
// the above assumes that bit 1 is to zero
GPIOB->MODER &= ~(0x02<<(7*2)); //ONLY clear GPIOB6

//CONFIGURE PORT:GPIOB  PIN:14 TO OUTPUT for LED3 (Red)
GPIOB->MODER |= 0x01<<(14*2); //ONLY set  GPIOB14
// the above assumes that bit 1 is to zero
GPIOB->MODER &= ~(0x02<<(14*2)); //ONLY clear GPIOB15
}	


//sets red led
void red_on (void)
{
		GPIOB->BSRR |= (1<<(14));//0x4000;	
		GPIOB->BSRR |= ( 0 <<30);			
		redcount = true;
}


//resets red led
 void red_off (void)
{

	GPIOB->BSRR |= ( 1 <<30);
	GPIOB->BSRR |= ( 0 <<14);
	redcount = false;
}


//sets blue led
void blue_on (void)
{
		
		GPIOB->BSRR |= (1<<(7));//0x4000;	
		GPIOB->BSRR |= ( 0 <<23);
		bluecount = true;
}

//resets blue led
 void blue_off (void)
{

	GPIOB->BSRR |= ( 1 <<23);
	GPIOB->BSRR |= ( 0 <<7);
	bluecount = false;
}

//sets green led
void green_on (void)
{
		
		GPIOB->BSRR |= (1<<(0));	
		GPIOB->BSRR |= ( 0 <<16);
		greencount = true;
}

//rests green led
 void green_off (void)
{

	GPIOB->BSRR |= ( 1 <<16);
	GPIOB->BSRR |= ( 0 <<0);
	greencount = false;
}


// function that toggles the red LED
void Toggle_Red(void){
	
	if (redcount == false) {
			red_on();
		
	}
	else if (redcount == true ){
		red_off();
	}
	
}


// function that toggles the blue LED
void Toggle_Blue(void){ 

	if (bluecount == false) {
			blue_on();
		
	}
	else if (bluecount == true ){
		blue_off();
	}
	
}

// function that toggles the blue LED
void Toggle_Green(void){

	if (greencount == false) {
			green_on();
		
	}
	else if (greencount == true ){
		green_off();
	}
	
}



void morselibary(float mor){

		sum1 = (mor*3.3)/4095; // sum1 holds the voltage

		// long if-else statment to read the ADC and translate it to morse code
		if(sum1<0.5){

			// 0 
		blue_on();
		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();

			
		blue_off();
		delay_100ms_blocking();

			
		blue_on();
		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();

		blue_off();
		delay_100ms_blocking();

		
		blue_on();
		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();

			
		blue_off();
		delay_100ms_blocking();


		blue_on();
		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();

			
		blue_off();
		delay_100ms_blocking();


		blue_on();
		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();

			
		blue_off();
		delay_100ms_blocking();



		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();

		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();

			

		// V
		blue_on();
		delay_100ms_blocking();
		blue_off();
		delay_100ms_blocking();

		blue_on();
		delay_100ms_blocking();
		blue_off();
		delay_100ms_blocking();

		blue_on();
		delay_100ms_blocking();
		blue_off();
		delay_100ms_blocking();

		blue_on();
		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();

			
		blue_off();
		delay_100ms_blocking();


		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();

		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();


		}
		else if(sum1>=0.5 && sum1<=1){

			// 0 
		blue_on();
		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();

			
		blue_off();
		delay_100ms_blocking();

		blue_on();
		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();

			
		blue_off();
		delay_100ms_blocking();
			
		blue_on();
		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();

			
		blue_off();
		delay_100ms_blocking();

		blue_on();
		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();

			
		blue_off();
		delay_100ms_blocking();

		blue_on();
		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();

			
		blue_off();
		delay_100ms_blocking();


		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();

		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();


		// 5 
		blue_on();
		delay_100ms_blocking();
		blue_off();
		delay_100ms_blocking();

		blue_on();
		delay_100ms_blocking();
		blue_off();
		delay_100ms_blocking();

		blue_on();
		delay_100ms_blocking();
		blue_off();
		delay_100ms_blocking();

		blue_on();
		delay_100ms_blocking();
		blue_off();
		delay_100ms_blocking();

		blue_on();
		delay_100ms_blocking();
		blue_off();
		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();

		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();

		//V
		blue_on();
		delay_100ms_blocking();
		blue_off();
		delay_100ms_blocking();

		blue_on();
		delay_100ms_blocking();
		blue_off();
		delay_100ms_blocking();

		blue_on();
		delay_100ms_blocking();
		blue_off();
		delay_100ms_blocking();

		blue_on();
		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();

			
		blue_off();
		delay_100ms_blocking();


		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();

		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();





		}
		else if (sum1>=1 && sum1<2){

		//1
		blue_on();
		delay_100ms_blocking();
		blue_off();
		delay_100ms_blocking();
		blue_on();
		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();

		blue_off();
		delay_100ms_blocking();
		blue_on();
		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();

			
		blue_off();
		delay_100ms_blocking();
		blue_on();
		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();

		blue_off();
		delay_100ms_blocking();
		blue_on();
		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();

		blue_off();
		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();

		//V
		blue_on();
		delay_100ms_blocking();
		blue_off();
		delay_100ms_blocking();

		blue_on();
		delay_100ms_blocking();
		blue_off();
		delay_100ms_blocking();

		blue_on();
		delay_100ms_blocking();
		blue_off();
		delay_100ms_blocking();

		blue_on();
		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();

			
		blue_off();
		delay_100ms_blocking();


		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();

		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();

		}
		else if (sum1>=2 && sum1<3){

		//2
		blue_on();
		delay_100ms_blocking();
		blue_off();
		delay_100ms_blocking();

		blue_on();
		delay_100ms_blocking();
		blue_off();
		delay_100ms_blocking();

			
		blue_on();
		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();

			
		blue_off();
		delay_100ms_blocking();

		blue_on();
		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();

			
		blue_off();
		delay_100ms_blocking();

		blue_on();
		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();

			
		blue_off();
		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();

		//V
		blue_on();
		delay_100ms_blocking();
		blue_off();
		delay_100ms_blocking();

		blue_on();
		delay_100ms_blocking();
		blue_off();
		delay_100ms_blocking();

		blue_on();
		delay_100ms_blocking();
		blue_off();
		delay_100ms_blocking();

		blue_on();
		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();

			
		blue_off();
		delay_100ms_blocking();


		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();

		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();

		}

		else if(sum1>=3){

		//3
		blue_on();
		delay_100ms_blocking();
		blue_off();
		delay_100ms_blocking();
			
		blue_on();
		delay_100ms_blocking();
		blue_off();
		delay_100ms_blocking();
			
		blue_on();
		delay_100ms_blocking();
		blue_off();
		delay_100ms_blocking();


		blue_on();
		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();

			
		blue_off();
		delay_100ms_blocking();

		blue_on();
		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();

			
		blue_off();
		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();


		//V
		blue_on();
		delay_100ms_blocking();
		blue_off();
		delay_100ms_blocking();

		blue_on();
		delay_100ms_blocking();
		blue_off();
		delay_100ms_blocking();

		blue_on();
		delay_100ms_blocking();
		blue_off();
		delay_100ms_blocking();

		blue_on();
		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();

			
		blue_off();
		delay_100ms_blocking();


		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();

		delay_100ms_blocking();
		delay_100ms_blocking();
		delay_100ms_blocking();


}

}






