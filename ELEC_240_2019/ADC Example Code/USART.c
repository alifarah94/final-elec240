#include "usart.h"
#include "stdio.h"
#include "string.h"
#include "lcd.h"
#include "math.h"
#include "Interrupts.h"
#include "ADC.H"
#include "LED.h"


#define radian_per_degree              0.0174532925


void send_usart(float	d)
{
	
	unsigned char value;
	while(!(USART_MODULE->SR&USART_SR_TC));		//wait for transmission complete
	USART_MODULE->DR=d;		//write byte to usart data register
	}



unsigned char rec_usart(void)
{
	
	while(!(USART_MODULE->SR&USART_SR_RXNE));  // waits for read data register not to be empty
	return USART_MODULE->DR; // returns what ever has been typed on the USART
	
}



void init_USART(void)
{
	unsigned char i1,i2;
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIODEN;		//usart port clock enable
	
	USART_PORT->MODER&=~(				//clear pin function bits
		(3u<<(2*USART_TX_pin))
		|(3u<<(2*USART_RX_pin))
			);
	USART_PORT->MODER|=(			//reset pin function bits (alternate function)
		(2u<<(2*USART_TX_pin))
		|(2u<<(2*USART_RX_pin))
			);
	
	i1=USART_TX_pin/8;
	i2=USART_RX_pin/8;

		// ALTERNATE FUNCTION SELECT BITS
	USART_PORT->AFR[i1]&=~(0x0f<<(4*(USART_TX_pin-(i1*8))));
	USART_PORT->AFR[i1]|=(0x07<<(4*(USART_TX_pin-(i1*8))));
	USART_PORT->AFR[i2]&=~(0x0f<<(4*(USART_RX_pin-(i2*8))));
	USART_PORT->AFR[i2]|=(0x07<<(4*(USART_RX_pin-(i2*8))));
	

	
	RCC->APB1ENR|=RCC_APB1ENR_USART3EN;		//usart clock enable
	USART_MODULE->CR1|=(		//USART CONFIG
			USART_CR1_TE		//transmit enable
			|USART_CR1_RE		//receive enable
			|USART_CR1_UE		//usart main enable bit
			|USART_CR1_RXNEIE // read data register not empty enable
			|(0x0u<<USART_CR1_M_Pos) //setting M to 0 will give 1 Start bit, 8 Data bits, n Stop bit
			//|USART_CR1_PCE // 	parity control enabled 
			|(0x0UL << USART_CR1_PS_Pos) // parity selection enabled. EVEN parity
				);
		
	USART_MODULE->BRR=0x187;		//set baud rate to 115200
}

	

void DisplayVoltageUsart(float d)
{
		int i;
		char str[32]; // str is a variable that that will hold the actual voltage
		 float sum = (d*3.3)/4095; // sum is the actual voltage. To get the actual voltage you must multiply the value given by the max voltage and then divde by the max value
			sprintf(str, "%.3f", sum); // sprintf takes some and turns it a float number with 3 decimal places and stores it in the buffer str

	//this For loops goes throught the array and prints it on the USART
		for (i=0; i<strlen(str);i++){
				send_usart(str[i]); // this displays each element of the array on to the USART
			
		
}
			send_usart(0x20); // display a space on the USART
		Toggle_Green();
}




char USART_SendString(unsigned char* TX)
{
			int i = 0; // i is used a a counter
	    // this while loop goes through TX and prints it on the USART
			while(TX[i] != '\0') // this condition says that it will leave the while loop when it has reached the end of line
	{
						send_usart(TX[i]);
						i++;
	}
	
	
	
}

int TriangleWaveUsart(int d){
	
		
	int wave = 0; // this variable is used as the posistion of the triangle wave

do{

				wave+=0x05; // increment by 5
				DAC->DHR12R2 = wave; // put in the DAC
				USART_SendString((unsigned char*)"\033[8;15H"); // Starts a new line ont he 8th row on the USART
				DisplayVoltageUsart(wave); // Display the actual voltage on the USART
				AnalogueSignalUsart(wave); // displays an visual signal of the value to USART
	Toggle_Green();// TOOGLES GREEN LED
} while (wave<d); // Do while the triangle waves position is lower than the functions argument

do{

				wave-=0x05; // decrement by 5
				DAC->DHR12R2 = wave;  // put in the DAC
				USART_SendString((unsigned char*)"\033[8;15H"); // Starts a new line ont he 8th row on the USART
				DisplayVoltageUsart(wave); // Display the actual voltage on the USART
				AnalogueSignalUsart(wave); // displays an visual signal of the value to USART
	Toggle_Green();// TOOGLES GREEN LED
} while (wave>0); // Do while the triangle waves position is above 0




}
void SquareWaveUsart(int d){





DAC->DHR12R2 = d; // put the argument of the function into the DAC
USART_SendString((unsigned char*)"\033[8;15H"); // escape code to start writing text on the  8th row and the 15th coloum
DisplayVoltageUsart(d);
	AnalogueSignalUsart(d); // Display it on the USART
	ActualVoltage(d);
lcd_delayus(4000); // WAITS 4ms
DAC->DHR12R2 = 0; // writes a 0 into the DAC
	Toggle_Green(); // TOOGLES GREEN LED 
USART_SendString((unsigned char*)"\033[8;15H"); // escape code to start writing text on the  8th row and the 15th coloum
DisplayVoltageUsart(0x30); // writes a 0 onto the 0
ActualVoltage(0x30);
AnalogueSignalUsart(d); // adds a progression bar onto the 	USART
lcd_delayus(2000);
Toggle_Green(); // TOOGLES GREEN LED 
}

void SineWaveUsart(int d){


	  
     signed int temp2 = 0;  // this variable is the position of the sinewave
     unsigned int degree = 0; // the variable degree will be used as the counter
	
// This FOR loop goes around 360 times to emulate a full cycle
	Toggle_Green();// TOOGLES GREEN LED
for(degree = 0; degree < 360; degree++)
         {
						
             temp2 = ((d/2) * sin(radian_per_degree * degree));
             temp2 = ((d/2) - temp2);
             DAC->DHR12R2 = ((unsigned int)temp2);
					   USART_SendString((unsigned char*)"\033[8;15H");  // escape code to start writing text on the  8th row and the 15th coloum
					   DisplayVoltageUsart(((unsigned int)temp2)); // the position of the sine wave is put onto the USART
							AnalogueSignalUsart(temp2); // adds a progression bar on USART
					   lcd_delayus(6000);// waits for 6 ms
	
           
				}
				 
}

void AnalogueSignalUsart(float d){
int i;
float divider = 255;
int sum = d/divider; // sum is functions argument divided by the pre-set diver. I use this to set the counter for the For loop to print out the progression bar


	
	USART_SendString((unsigned char*)"\033[9;1H"); // this is a escape code that writes to the 9th row and the first coloum
	for( i = 0; i<=sum; i++){
		if (i==sum){
		send_usart(' '); // if sum is lower than i then print nothing else place a block
		}
		else
		send_usart(0xFF); // print blocks 
	}
}


void UsartMenu(void){
// this function prints a menu on to the USART informing the users about there coices
  	USART_SendString((unsigned char*)"\033[1;1H");
		USART_SendString((unsigned char*)"Type the number for the mode you would like to use: ");
		USART_SendString((unsigned char*)"\033[2;1H");
	USART_SendString((unsigned char*)"\033[1;34;40m");
		USART_SendString((unsigned char*)"DC MODE");
USART_SendString((unsigned char*)"\033[0;0;0m");
		USART_SendString((unsigned char*)"\033[3;1H");
		USART_SendString((unsigned char*)"1. Show DC measerment");
		USART_SendString((unsigned char*)"\033[4;1H");
	USART_SendString((unsigned char*)"\033[1;31;40m");
		USART_SendString((unsigned char*)"AC MODE");
	USART_SendString((unsigned char*)"\033[0;0;0m");
		USART_SendString((unsigned char*)"\033[5;1H");
		USART_SendString((unsigned char*)"2. Square");
		USART_SendString((unsigned char*)"\033[6;1H");
		USART_SendString((unsigned char*)"3. Triangle");
		USART_SendString((unsigned char*)"\033[7;1H");
		USART_SendString((unsigned char*)"4. Sine");
}
