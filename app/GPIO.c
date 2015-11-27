#include "GPIO.h"
#include "stm32f4xx_hal_rcc.h"

void configurePin(int mode, int pinNumber, GPIO *port){
	//GPIO_InitTypeDef gpio;

	//__HAL_RCC_GPIOG_CLK_ENABLE();
	//__HAL_RCC_GPIOB_CLK_ENABLE();
	//__HAL_RCC_GPIOC_CLK_ENABLE();
	gpioUnresetEnableClock(port);

/*	int *ptr = (int*)0x40023810;
	ptr[0] = 0xFFFFFFBF;
	int *enPtr = (int*)0x40023830;
	enPtr[0] = 0x00100040; */

	port->MODER &= ~(3 << (pinNumber * 2));
	port->MODER |= mode << (pinNumber * 2);				// MODE.pin14 = output
	port->OTYPER &= ~(1 << (pinNumber));
	port->OSPEED &= ~(3 << (pinNumber * 2));
	port->OSPEED |= GPIO_HIGH_SPEED << (pinNumber * 2);


/*	int *ptr = (int*)0x40021800;
	int *ptrB = (int*)0x40020400;
	int *ptrC = (int*)0x40020800;

	ptr[0] = 0x14000000;				// MODE.pin14 = output
	ptr[1] = 0;							// OTYPE.pin14 = push-pull
	ptr[2] = 0x20000000;                // OSPEED.pin14 = high speed

	ptrB[0] = 0x04000000;
	ptrB[1] = 0;
	ptrB[2] = 0x08000000;

	ptrC[0] = 0x00000400;
	ptrC[1] = 0;
	ptrC[2] = 0x00000800;*/
//	gpio.Pin = pinNumber;
//	gpio.Mode = direction;
//	gpio.Speed = GPIO_SPEED_MEDIUM;

//	HAL_GPIO_Init(port, &gpio);
}

void configureInputPin(int pinNumber, GPIO *port, int pupdr){
	gpioUnresetEnableClock(port);

	port->MODER &= ~(3 << (pinNumber * 2));
	port->MODER |= GPIO_MODE_INTPUT << (pinNumber * 2);
	port->OTYPER &= ~(1 << (pinNumber));
	port->OSPEED &= ~(3 << (pinNumber * 2));
	port->OSPEED |= GPIO_HIGH_SPEED << (pinNumber * 2);
	port->PUPDR &= ~(3 << (pinNumber * 2));
	port->PUPDR |= pupdr << (pinNumber * 2);

}

void writeOne(uint16_t pinNumber, GPIO_TypeDef *port){
//	HAL_GPIO_WritePin(port, pinNumber, GPIO_PIN_SET);
//	port->ODR |= (1 << (pinNumber));
	port->BSRR = (1 << pinNumber);

}

void writeZero(uint16_t pinNumber, GPIO_TypeDef *port){
//	HAL_GPIO_WritePin(port, pinNumber, GPIO_PIN_RESET);
//	port->ODR &= ~(1 << (pinNumber));
	port->BSRR = (1 << (pinNumber+16));
}

