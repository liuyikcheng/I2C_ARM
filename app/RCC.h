#ifndef __RCC_H__
#define __RCC_H__

#include "stm32f4xx_hal_gpio.h"

typedef struct RCC_t RCC_REG;
struct RCC_t{
	uint32_t CR;
	uint32_t PLLCFGR;
	uint32_t CFGR;
	uint32_t CIR;
	uint32_t AHB1RSTR;
	uint32_t AHB2RSTR;
	uint32_t AHB3RSTR;
	uint32_t Reserved1;
	uint32_t APB1RSTR;
	uint32_t APB2RSTR;
	uint32_t Reserved2;
	uint32_t Reserved3;
	uint32_t AHB1ENR;
	uint32_t AHB2ENR;
	uint32_t AHB3ENR;
	uint32_t Reserved4;
	uint32_t APB1ENR;
	uint32_t APB2ENR;
};


#define RCC_REG_ADDRESS		0x40023800

#define RCC_reg		((RCC_REG *)RCC_REG_ADDRESS)

void unresetEnableRngClock();

#endif // __RCC_H__
