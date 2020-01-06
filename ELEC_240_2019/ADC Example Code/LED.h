#ifndef _LED_H_



#include <stm32f4xx.h>		
#include <stdbool.h>


void Userinputdelay(unsigned int delay);
void whiledelay (void);
void delay (void);
void delay_100ms_blocking(void);
void greenled(void);
void LED_INIT (void);
void red_on(void); // turns red led off
void red_off(void); // turns red led off
void Toggle_Red(void); // toggles red led
void morselibary(float mor); // blue led. morse code
void Toggle_Blue(void); // function that toggles blue led
void blue_on(void); // turns blue led on 
void blue_off(void); // turns blue led off
void Toggle_Green(void); // toggles green led
void green_on(void); // turns green led on 
void green_off(void); // turns green led off
#endif
