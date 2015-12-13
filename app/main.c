#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "I2C.h"
#include "RCC.h"
#include "GPIO.h"
#include <stdint.h>

#define I2C1_OWNADDRESS		0x26F



void delay(int time){
	while(time != 0)
		time--;
}

int main(void){

	int a, b, c, d, e, f, data;
//GPIO_NO_PULL_UP_DOWN GPIO_PULL_UP

	configurePin(GPIO_MODE_ALTFUNC, PIN_6, PORTB, GPIO_NO_PULL_UP_DOWN); //PB6 as SCL for I2C1
	configurePin(GPIO_MODE_ALTFUNC, PIN_7, PORTB, GPIO_NO_PULL_UP_DOWN); //PB7 as SDA for I2C1
  
	//configurePin(GPIO_MODE_ALTFUNC, PIN_11, PORTB, GPIO_NO_PULL_UP_DOWN); //PB11 as SDA for I2C2
	//configurePin(GPIO_MODE_ALTFUNC, PIN_10, PORTB, GPIO_NO_PULL_UP_DOWN); //PB10 as SCL for I2C2

	configurePin(GPIO_MODE_ALTFUNC, PIN_8, PORTA, GPIO_NO_PULL_UP_DOWN); //PA8 as SCL for I2C3
	configurePin(GPIO_MODE_ALTFUNC, PIN_9, PORTC, GPIO_NO_PULL_UP_DOWN); //PC9 as SDA for I2C3

	unresetEnableI2cClock();

	configureI2cAddress(I2C_reg, I2C1_OWNADDRESS, ADDRESS_10_BIT_MODE);

	configureI2C(I2C_reg);
	//configureI2C(0x30, I2C2_reg);
	configureI2C(I2C3_reg);

	configurePinAFRL(PORTB, PIN_6, AF4);
	configurePinAFRL(PORTB, PIN_7, AF4);
	//configurePinAFRH(PORTB, PIN_11, AF4);
	//configurePinAFRH(PORTB, PIN_10, AF4);
	configurePinAFRH(PORTA, PIN_8, AF4);
	configurePinAFRH(PORTC, PIN_9, AF4);


		//while(1){

			generateStart(I2C3_reg);

			sendAddress(I2C3_reg, I2C1_OWNADDRESS, ADDRESS_10_BIT_MODE, MASTER_RECEIVE);
			while(status1(I2C_reg,1) == 0); //wait for slave to match address

			generateStart(I2C3_reg);
			sendHeaderForReceive(I2C3_reg, I2C1_OWNADDRESS);

			if(status1(I2C_reg,8) == 1){
				sendAddress(I2C3_reg, I2C1_OWNADDRESS, 1, MASTER_RECEIVE);
			}
		//	d = I2C_reg->I2C_SR1;
		//	e = I2C_reg->I2C_SR2;
		//	a = I2C_reg->I2C_CR1;
			i2cWriteData(0x46, I2C_reg);
			data = i2cReadData(I2C3_reg);


		//	i2cWriteData(0x21, I2C3_reg);
		//	data = i2cReadData(I2C_reg);

			masterSendNack(I2C3_reg);
			i2cWriteData(0x18, I2C_reg);
			data = i2cReadData(I2C3_reg);

			i2cStop(I2C3_reg);
			d = I2C_reg->I2C_SR1;

			while(1);
		//}

}
