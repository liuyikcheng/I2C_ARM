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


int main(void){

	int a, b, c, d, e, f, data;

  /* Enable the interrupt handle */
//	HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
//	HAL_NVIC_EnableIRQ(DMA1_Stream4_IRQn);
	HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);
//GPIO_NO_PULL_UP_DOWN GPIO_PULL_UP

	/* Configure the GPIO pins as alternative function for I2C1  */
  configurePin(GPIO_MODE_ALTFUNC, PIN_6, PORTB, GPIO_NO_PULL_UP_DOWN);//PB6 as SCL for I2C1
  configurePin(GPIO_MODE_ALTFUNC, PIN_7, PORTB, GPIO_NO_PULL_UP_DOWN);//PB7 as SDA for I2C1

  /* Configure the GPIO pins as alternative function for I2C3 */
  configurePin(GPIO_MODE_ALTFUNC, PIN_8, PORTA, GPIO_NO_PULL_UP_DOWN); //PA8 as SCL for I2C3
  configurePin(GPIO_MODE_ALTFUNC, PIN_9, PORTC, GPIO_NO_PULL_UP_DOWN); //PC9 as SDA for I2C3

  /* Connect GPIO pins with the SCL and SDA pin from I2C*/
  configurePinAFRL(PORTB, PIN_6, AF4);
  configurePinAFRL(PORTB, PIN_7, AF4);
  configurePinAFRH(PORTA, PIN_8, AF4);
  configurePinAFRH(PORTC, PIN_9, AF4);

  /* Unreset and enable I2C clock */
  unresetEnableI2cClock();
  /* Set the own address of I2C1  */
  configureI2cAddress(I2C_reg, I2C1_OWNADDRESS, ADDRESS_7_BIT_MODE);

  /* configure DMA with according stream */
	configDMAstream(&(dma1->S4), channel3, M2P);
	configDMAstream(&(dma1->S5), channel1, P2M);

  /* set the Peripheral address and the memory address to the DMA */
	connectDMAnI2C(&(dma1->S4), transmitBuffer, &(I2C3_reg->I2C_DR), 5);
	connectDMAnI2C(&(dma1->S5), receiveBuffer, &(I2C_reg->I2C_DR), 5);

  /* enable DMA request in I2C */
  dmaRequestEnable(I2C3_reg);
  dmaRequestEnable(I2C_reg);

  /* enable DMA */
	enableDMA(&(dma1->S4));
	enableDMA(&(dma1->S5));

  /* Configure the the I2C interface and enable the peripheral */
	configureI2C(I2C_reg);
	configureI2C(I2C3_reg);




			generateStart(I2C3_reg);
			sendAddress(I2C3_reg, I2C1_OWNADDRESS, ADDRESS_7_BIT_MODE, MASTER_TRANSMIT);
	
			while(1){

				e = I2C3_reg->I2C_SR1;
				e = I2C3_reg->I2C_SR2;
				f = I2C_reg->I2C_SR1;
				f = I2C_reg->I2C_SR2;

			}


}
