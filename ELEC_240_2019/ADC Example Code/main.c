#include <stm32f4xx.h>
#include "PLL_Config.c"
#include "ADC.h"
#include "DAC.h"
#include "lcd.h"
#include "Interrupts.h"
#include "USART.h"
#include "LED.h"
unsigned short ADC_DATA;
int main(void)
{
	PLL_Config();
	SystemCoreClockUpdate();
	
	init_ADC();		//config ADC
	init_DAC();		//config DAC
	initLCD();    // config LCD
	Timer2setup(); // config timer 2
	button2();     // config for button
	LED_INIT();    // config LED
	init_USART();  // config USART
	UsartMenu();   // uart menu
	UsartInterrupt();
	Timer3setup();
	
	while(1)
	{
		__WFI;  // keeps board on low power, waits for interrupt
		
		
	}
}

