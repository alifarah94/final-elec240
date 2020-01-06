#include <stm32f4xx.h>
#include "LED.h"
#include <stdbool.h>


bool press = false;



// switch bounce function
void pressed(void){
	// when pressed turns press boolean to true and waits 100ms
	if (press == false) {
			press = true;
			delay_100ms_blocking();	
	}
	// when button is let go press is turned to false and another delay is activated to prevent double bounce 
	else if (press == true ){
		press = false;
		delay_100ms_blocking();
		
	}
	
}