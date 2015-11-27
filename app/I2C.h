#ifndef __I2C_H__
#define __I2C_H__

typedef struct I2C_t I2C_REG;

struct I2C_t{

	uint32_t I2C_CR1;
	uint32_t I2C_CR2;
	uint32_t I2C_OAR1;
	uint32_t I2C_OAR2;
	uint32_t I2C_DR;
	uint32_t I2C_SR1;
	uint32_t I2C_SR2;
	uint32_t I2C_CCR
	uint32_t I2C_TRISE;
	uint32_t I2C_FLTR;
}

#define I2C_REG_ADDRESS		0x40005400

#define I2C_reg		((I2C_REG *)I2C_REG_ADDRESS)

#endif // __I2C_H__
