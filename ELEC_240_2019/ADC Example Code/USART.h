#ifndef _USART_H_
#define _USART_H_
#include <stm32f4xx.h>

#define USART_MODULE	USART3
#define USART_PORT		GPIOD
#define USART_TX_pin	8
#define USART_RX_pin	9
#define BAUDRATE			9600


void send_usart(float d);         // function to send characters to usart
void init_USART(void);           // set up the USART
unsigned char rec_usart(void);   // function to receive characters from USART
void DisplayVoltageUsart(float	d); // function to dispaly voltage on the USART
char USART_SendString(unsigned char* TX);  //function to send strings to USART 
int TriangleWaveUsart(int d); // function to send triangle wave values to USART
void SquareWaveUsart(int d);  // function to send square wave to USART
void SineWaveUsart(int d); // function to send sine wave to USART
void AnalogueSignalUsart(float d); //shows an analougue on the USART
void UsartMenu(void);         // prints a menu onto 
void UsartInterrupt(void);
void DisplayUsart(char d);


#endif
