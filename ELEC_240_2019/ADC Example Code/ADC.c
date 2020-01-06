#include "ADC.h"
#include "LCD.h"
#include "string.h"
#include "stdio.h"


void init_ADC(void)
{
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOCEN;	//GPIOC clock enable
	ADC_input_port->MODER|=(3u<<(2*ADC_input_pin));	//ADC input pin is analogue mode
	
	RCC->APB2ENR|=RCC_APB2ENR_ADC1EN;		//ADC clock enable
	ADC1->SQR1&=~ADC_SQR1_L;						//set number of conversions per sequence to 1
	ADC1->SQR3&=~ADC_SQR3_SQ1;					//clear channel select bits
	ADC1->SQR3|=ADC_Channel;						//set channel
	ADC1->CR2|=ADC_CR2_ADON;						//enable ADC
	ADC1->CR1|= ~(0x3UL) << ADC_CR1_RES_Pos; // set sampling resoultion to 12 bit
}

unsigned short read_adc(void)
{
	ADC1->CR2|=ADC_CR2_SWSTART;				//start ADC conversion
	while((ADC1->SR&ADC_SR_EOC)==0){__NOP();}	//wait for ADC conversion complete
	return ADC1->DR;									//return converted value
}


void ActualVoltage(int volt)
{
    int i; // counter 
		char str[32]; // str is a variable that that will hold the actual voltage
		float sum = (volt*3.3)/4095; // sum is the actual voltage. To get the actual voltage you must multiply the value given by the max voltage and then divde by the max value
	
		sprintf(str, "%.3f", sum); // sprintf takes sum and turns it to a float number with 3 decimal places and stores it in the buffer str
		cmdLCD(LCD_LINE1); // this line sets the texts the 
	
		// if else statment to assert upper and lower bounds 
		if (sum >= 3.29)
			{
			sprintf(str, "%.3f", 3.300);
			}
		else if (sum<=0.004)
		{
			sprintf(str, "%.3f", 0.000);
		
		}
		
		for(i=0; i<strlen(str);i++) //this For loops goes throught the array and prints it on the LCD
		{
		    putLCD(str[i]);
		}
		
		
}


void AnalogueSignal(float d)
{
		
		int i; // counter 
    float divider = 255; 
		int sum = d; // sum is functions argument divided by the pre-set diver. I use this to set the counter for the For loop to print out the progression bar
		int sumsave; // variable to save the last value of sum
	  cmdLCD(LCD_LINE2); // this line makes text print on the second line of the 	Lcd
	

		// if statment that checks if variable has been changed.
		// incased in the if statment is a if-else statment that checks the boundrays and then prints out the amount of bars representing voltage on the lcd
		// I chose this long method because I wanted to avoid loops
		// 16 spaces. 4095/16 = 255
		if (sum != sumsave)	{	
        if (sum>0 && sum<=5){
				    cmdLCD(0x0);
		        sumsave = sum;
	  }
			 else if(sum>5 && sum<=255){
					 cmdLCD(0x0);
		       cmdLCD(LCD_LINE2);
		       putLCD(0xFF);
			     sumsave = sum;
		}
			 else if(sum>255 && sum<=510){
					 cmdLCD(0x0);
					 cmdLCD(LCD_LINE2);
					 putLCD(0xFF);
					 putLCD(0xFF);
					 sumsave = sum;
	  }
	     else if(sum>510 && sum<=765){
			    cmdLCD(0x0);
			    cmdLCD(LCD_LINE2);
		      putLCD(0xFF);
			    putLCD(0xFF);
			    putLCD(0xFF);
			    sumsave = sum;
		}
	    else if(sum>765 && sum<=1020){
					cmdLCD(0x0);
					cmdLCD(LCD_LINE2);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					sumsave = sum;
	  }
			else if(sum>1020 && sum<=1275){
					cmdLCD(0x0);
					cmdLCD(LCD_LINE2);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					sumsave = sum;
		}
	    else if(sum>1275 && sum<=1530){
					cmdLCD(0x0);
					cmdLCD(LCD_LINE2);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					sumsave = sum;
	  }
			else if(sum>1530 && sum<=1785){
					cmdLCD(0x0);
					cmdLCD(LCD_LINE2);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					sumsave = sum;
		}
			else if(sum>1785 && sum<=2040){
					cmdLCD(0x0);
					cmdLCD(LCD_LINE2);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					sumsave = sum;
			
	  }
			else if(sum>2040 && sum<=2295){
					cmdLCD(0x0);
					cmdLCD(LCD_LINE2);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					sumsave = sum;
		}
			else if(sum>2295 && sum<=2550){
					cmdLCD(0x0);
					cmdLCD(LCD_LINE2);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					sumsave = sum;
	  }
			else if(sum>2550 && sum<=2805){
					cmdLCD(0x0);
					cmdLCD(LCD_LINE2);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					sumsave = sum;
		}
			else if(sum>2805 && sum<=3060){
					cmdLCD(0x0);
					cmdLCD(LCD_LINE2);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					sumsave = sum;
	  }
			else if(sum>3060 && sum<=3315){
					cmdLCD(0x0);
					cmdLCD(LCD_LINE2);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					sumsave = sum;
		}
			else if(sum>3315 && sum<=3570){
					cmdLCD(0x0);
					cmdLCD(LCD_LINE2);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					sumsave = sum;
	  }
			else if(sum>3570 && sum<=3825){
					cmdLCD(0x0);
					cmdLCD(LCD_LINE2);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					sumsave = sum;
		}
			
			else if(sum>3825){
					cmdLCD(0x0);
					cmdLCD(LCD_LINE2);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					putLCD(0xFF);
					sumsave = sum;
	  }
			else{
					cmdLCD(0x0);
					cmdLCD(LCD_LINE2);
					putLCD(0xFF);
		}
				
	}

}
