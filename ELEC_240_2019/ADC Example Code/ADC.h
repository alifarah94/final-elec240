#ifndef _ADC_H
#define _ADC_H
#include <stm32f4xx.h>

#define ADC_input_port		GPIOC
#define ADC_input_pin			0
#define ADC_Channel				10

void init_ADC(void); // initisalises ADC
unsigned short read_adc(void); // holds adc value
void ActualVoltage(int volt); // function that turns the adv value to a readable number
void AnalogueSignal(float d); //displays a representation of the voltage
#endif 
