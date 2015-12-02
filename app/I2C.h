#ifndef __I2C_H__
#define __I2C_H__

#include "stm32f4xx_hal.h"

typedef struct I2C_t I2C_REG;


struct I2C_t{

	uint32_t I2C_CR1;
	uint32_t I2C_CR2;
	uint32_t I2C_OAR1;
	uint32_t I2C_OAR2;
	uint32_t I2C_DR;
	uint32_t I2C_SR1;
	uint32_t I2C_SR2;
	uint32_t I2C_CCR;
	uint32_t I2C_TRISE;
	uint32_t I2C_FLTR;
};

#define I2C_REG_ADDRESS		0x40005400

#define I2C_reg		((I2C_REG *)I2C_REG_ADDRESS)

void configureI2C(int OwnAddress);

void i2cStart(int address, int rw);

void i2cWriteData(int data);

void i2cStop();


#endif // __I2C_H__
