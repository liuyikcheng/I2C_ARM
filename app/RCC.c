#include "RCC.h"
#include "GPIO.h"


void gpioUnresetEnableClock(GPIO *port){
	int shift = (((int)port) - 0x40020000) / 0x400;
	RCC_reg->AHB1RSTR &= ~(1 << (shift));
	RCC_reg->AHB1ENR |= (1 << (shift));
}

void unresetEnableI2cClock(){

	RCC_reg->APB1RSTR &= ~(1<<21); //unreset enable I2C1
	RCC_reg->APB1ENR |= (1<<21);

	RCC_reg->APB1RSTR &= ~(1<<22); //unreset enable I2C2
	RCC_reg->APB1ENR |= (1<<22);

	RCC_reg->APB1RSTR &= ~(1<<23); //unreset enable I2C3
	RCC_reg->APB1ENR |= (1<<23);
	uint32_t data1 = RCC_reg->APB1ENR ;

}

void DMAUnresetEnableClock(){
	//only DMA2 streams are able to perform memory-to-memory transfers

	RCC_reg->AHB1RSTR  &= ~(1 << 21); 	//DMA1RST
	uint32_t data = RCC_reg->AHB1RSTR ;
	RCC_reg->AHB1ENR  |= (1 << 21);		//DMA1EN	Clock the DMA1 for configuration change
	uint32_t data1 = RCC_reg->AHB1ENR ;
}
