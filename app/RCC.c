#include "RCC.h"
//#include "GPIO.h"



void unresetEnableRngClock(){

	RCC_reg->AHB2RSTR &= ~(1<<6);
	RCC_reg->AHB2ENR |= (1<<6);
}


void unresetEnableI2cClock(){

	RCC_reg->APB1RSTR &= ~(1<<21);
	RCC_reg->APB1ENR &= (1<<21);
}
