#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "I2C.h"
#include "RCC.h"
#include "GPIO.h"
#include "DMA.h"
#include <stdint.h>

#define I2C1_OWNADDRESS		0x10

uint8_t transmitBuffer[] = "HELLO";
uint8_t receiveBuffer[100];

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

void DMA1_Stream4_IRQHandler(void){

	int flag = dma1->HISR;
	int data = I2C_reg->I2C_DR;
	data = I2C3_reg->I2C_SR1;
	data = I2C3_reg->I2C_SR2;
			data = I2C_reg->I2C_SR1;
			data = I2C_reg->I2C_SR2;
	if ((((flag>>5)&1) == 1)&&(((flag>>4)&1) == 1)){
		dma1->HIFCR |= (1<<5);
		dma1->HIFCR |= (1<<4);
		flag = dma1->HISR;
		i2cStop(I2C3_reg);
	}

}

void DMA1_Stream5_IRQHandler(void){

	int flag = dma1->HISR;
	int data = receiveBuffer[0];
		data = I2C_reg->I2C_SR1;
		data = I2C_reg->I2C_SR2;
		data = I2C_reg->I2C_DR;

	if ((((flag>>11)&1) == 1)&&(((flag>>10)&1) == 1)){
		dma1->HIFCR |= (1<<11);
		dma1->HIFCR |= (1<<10);
		data = I2C_reg->I2C_DR;
		i2cStop(I2C3_reg);
	}

}

void delay(int time){
	while(time != 0)
		time--;
}

int main(void){

	int a, b, c, d, e, f, data;

//	HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
//	HAL_NVIC_EnableIRQ(DMA1_Stream4_IRQn);
	HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);
//GPIO_NO_PULL_UP_DOWN GPIO_PULL_UP

	configurePin(GPIO_MODE_ALTFUNC, PIN_6, PORTB, GPIO_NO_PULL_UP_DOWN); //PB6 as SCL for I2C1
	configurePin(GPIO_MODE_ALTFUNC, PIN_7, PORTB, GPIO_NO_PULL_UP_DOWN); //PB7 as SDA for I2C1
  
	configurePin(GPIO_MODE_ALTFUNC, PIN_8, PORTA, GPIO_NO_PULL_UP_DOWN); //PA8 as SCL for I2C3
	configurePin(GPIO_MODE_ALTFUNC, PIN_9, PORTC, GPIO_NO_PULL_UP_DOWN); //PC9 as SDA for I2C3

	configDMAstream(&(dma1->S4), channel3, M2P);
	configDMAstream(&(dma1->S5), channel1, P2M);

	b = dma1->S4.CR;
	a = dma1->S5.CR;

//	DMA_interruptTransfer(&(dma1->S4));
//	DMA_interruptTransfer(&(dma1->S5));


	connectDMAnI2C(&(dma1->S4), transmitBuffer, &(I2C3_reg->I2C_DR), 5);
	connectDMAnI2C(&(dma1->S5), receiveBuffer, &(I2C_reg->I2C_DR), 5);

	unresetEnableI2cClock();

	configureI2cAddress(I2C_reg, I2C1_OWNADDRESS, ADDRESS_7_BIT_MODE);

	configurePinAFRL(PORTB, PIN_6, AF4);
	configurePinAFRL(PORTB, PIN_7, AF4);
	configurePinAFRH(PORTA, PIN_8, AF4);
	configurePinAFRH(PORTC, PIN_9, AF4);

	I2C3_reg->I2C_CR2 |= (1<<11); //enable dma request
	I2C_reg->I2C_CR2 |= (1<<11); //enable dma request

	enableDMA(&(dma1->S4));
	enableDMA(&(dma1->S5));

	configureI2C(I2C_reg);
	configureI2C(I2C3_reg);




			generateStart(I2C3_reg);
			sendAddress(I2C3_reg, I2C1_OWNADDRESS, ADDRESS_7_BIT_MODE, MASTER_TRANSMIT);
			//while(status1(I2C3_reg, TxE) == 0);

		/*	a = dma1->LISR;
			b = dma1->HISR;
			c = I2C3_reg->I2C_DR;
			d = I2C_reg->I2C_DR;
			e = I2C3_reg->I2C_SR1;
			f = I2C3_reg->I2C_SR1;
			checkEvent(dma1,5);
			checkEvent(dma1,4);
			checkEvent(dma1,10);
			checkEvent(dma1,11);*/
			while(1){

				e = I2C3_reg->I2C_SR1;
				e = I2C3_reg->I2C_SR2;
				f = I2C_reg->I2C_SR1;
				f = I2C_reg->I2C_SR2;

			}
	//		i2cStop(I2C3_reg);

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
