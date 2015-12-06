#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "I2C.h"
#include "RCC.h"
#include "GPIO.h"
#include <stdint.h>

void delay(int time){
	while(time != 0)
		time--;
}

int main(void){

	int a;

	configurePin(GPIO_MODE_ALTFUNC, PIN_6, PORTB, GPIO_NO_PULL_UP_DOWN); //PB6 as SCL
	configurePin(GPIO_MODE_ALTFUNC, PIN_7, PORTB, GPIO_NO_PULL_UP_DOWN); //PB7 as SDA

	unresetEnableI2cClock();
	configureI2C(2);

	configurePinAF(PORTB, PIN_6, AF4);
	configurePinAF(PORTB, PIN_7, AF4);

		i2cStart(7,1);

		i2cWriteData(3);

	//	i2cWriteData(5);

		while(1){
			i2cWriteData(5);
		}

}
