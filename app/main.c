#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "I2C.h"
#include "RCC.h"
#include "GPIO.h"
#include "DMA.h"
#include <stdint.h>

#define I2C1_OWNADDRESS		0x10

uint8_t buffer[] = {23,12};


void I2C1_EV_IRQHandler(void){

	int readData, sr1, sr2;

	if (((I2C_reg->I2C_SR1>>RxNE)&1) == 1)
		readData = i2cReadData(I2C_reg);
	else if (((I2C_reg->I2C_SR1>>ADDR)&1) == 1){
		sr1 = I2C_reg->I2C_SR1;
		sr2 = I2C_reg->I2C_SR2;
	}
	else if (((I2C_reg->I2C_SR1>>STOPF)&1) == 1){
		sr1 = I2C_reg->I2C_SR1;
		//I2C_reg->I2C_CR1 = ;
	}
	else if (((I2C_reg->I2C_SR1>>TxE)&1) == 1){
		I2C_reg->I2C_DR = 0x50;
	}


}

void delay(int time){
	while(time != 0)
		time--;
}

int main(void){

	int a, b, c, d, e, f, data;

//	HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
//GPIO_NO_PULL_UP_DOWN GPIO_PULL_UP

	configurePin(GPIO_MODE_ALTFUNC, PIN_6, PORTB, GPIO_NO_PULL_UP_DOWN); //PB6 as SCL for I2C1
	configurePin(GPIO_MODE_ALTFUNC, PIN_7, PORTB, GPIO_NO_PULL_UP_DOWN); //PB7 as SDA for I2C1
  
	configurePin(GPIO_MODE_ALTFUNC, PIN_8, PORTA, GPIO_NO_PULL_UP_DOWN); //PA8 as SCL for I2C3
	configurePin(GPIO_MODE_ALTFUNC, PIN_9, PORTC, GPIO_NO_PULL_UP_DOWN); //PC9 as SDA for I2C3

	configDMAM2M(dma1, channel3, M2P);
	DMA_interruptTransfer(dma1);
	DMA_memcpy8(dma1,buffer,&(I2C3_reg->I2C_DR),2);

	unresetEnableI2cClock();

	configureI2cAddress(I2C_reg, I2C1_OWNADDRESS, ADDRESS_7_BIT_MODE);

	configurePinAFRL(PORTB, PIN_6, AF4);
	configurePinAFRL(PORTB, PIN_7, AF4);
	configurePinAFRH(PORTA, PIN_8, AF4);
	configurePinAFRH(PORTC, PIN_9, AF4);

	I2C3_reg->I2C_CR2 |= (1<<11); //enable dma request

	configureI2C(I2C_reg);
	configureI2C(I2C3_reg);



	enableDMA(dma1);


	a = dma1->S4.CR;


			generateStart(I2C3_reg);
			sendAddress(I2C3_reg, I2C1_OWNADDRESS, ADDRESS_7_BIT_MODE, MASTER_TRANSMIT);
			//while(status1(I2C3_reg, TxE) == 0);

			a = dma1->LISR;
			b = dma1->HISR;
			c = I2C3_reg->I2C_DR;
			d = I2C_reg->I2C_DR;
			a = dma1->LISR;
			b = dma1->HISR;
			c = I2C3_reg->I2C_DR;
			d = I2C_reg->I2C_DR;

			i2cStop(I2C3_reg);

/*
			a = dma1->LISR;
			b = dma1->HISR;
			c = I2C3_reg->I2C_SR1;
			d = I2C3_reg->I2C_SR1;
			sendAddress(I2C3_reg, I2C1_OWNADDRESS, ADDRESS_7_BIT_MODE, MASTER_TRANSMIT);
			while(status1(I2C_reg,1) == 0); //wait for slave to match address

		//	generateStart(I2C3_reg);
		//	sendHeaderForReceive(I2C3_reg, I2C1_OWNADDRESS);

			if(status1(I2C_reg,8) == 1){
				sendAddress(I2C3_reg, I2C1_OWNADDRESS, 1, MASTER_TRANSMIT);
			}
		//	d = I2C_reg->I2C_SR1;
		//	e = I2C_reg->I2C_SR2;
		//	a = I2C_reg->I2C_CR1;
		//	i2cWriteData(0x46, I2C_reg);
			//data = i2cReadData(I2C3_reg);


			i2cWriteData(0x21, I2C3_reg);
		//	data = i2cReadData(I2C_reg);

		//	masterSendNack(I2C3_reg);
		//	i2cWriteData(0x18, I2C_reg);
			//data = i2cReadData(I2C3_reg);

			i2cStop(I2C3_reg);
			d = I2C_reg->I2C_SR1;

			while(1);

*/

}
