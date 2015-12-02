#include "GPIO.h"
#include "stm32f4xx_hal_rcc.h"

void configurePin(int mode, int pinNumber, GPIO *port){
	//GPIO_InitTypeDef gpio;
	gpioUnresetEnableClock(port);

/*	int *ptr = (int*)0x40023810;
	ptr[0] = 0xFFFFFFBF;
	int *enPtr = (int*)0x40023830;
	enPtr[0] = 0x00100040; */

	port->MODER &= ~(3 << (pinNumber * 2));
	port->MODER |= mode << (pinNumber * 2);
	port->OTYPER |= (1 << (pinNumber));			//open drain
	port->OSPEED &= ~(3 << (pinNumber * 2));
	port->OSPEED |= GPIO_HIGH_SPEED << (pinNumber * 2);
	port->PUPDR &= ~(3 << (pinNumber * 2));
	port->PUPDR |= GPIO_PULL_UP << (pinNumber * 2);


}

void configurePinAF(GPIO *port, int pinNumber, int af){

	port->AFRL &= ~(15 << (pinNumber * 4));
	port->AFRL |=  af << (pinNumber * 4);
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

