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
#define I2C2_REG_ADDRESS	0x40005800
#define I2C3_REG_ADDRESS	0x40005C00

#define I2C_reg		((I2C_REG *)I2C_REG_ADDRESS)
#define I2C2_reg	((I2C_REG *)I2C2_REG_ADDRESS)
#define I2C3_reg	((I2C_REG *)I2C3_REG_ADDRESS)

/********** control register 1 **********/
#define PE			  0
#define SMBUS		  1
//RESERVED			  2
#define SMBTYPE		3
#define ENARP		  4
#define	ENPEC		  5
#define ENGC		  6
#define NOSTRETCH	7
#define START		  8
#define STOP		  9
#define ACK			  10
#define POS			  11
#define PEC			  12
#define ALERT		  13
//RESERVED			  14
#define SWRST		  15

/********** control register 2 **********/
#define ITERREN		8
#define ITEVTEN		9
#define ITBUFEN		10
#define DMAEN		11
#define LAST		12

/********** status register 1 **********/
#define SB		0
#define ADDR	1
#define BTF		2
#define ADD10	3
#define STOPF	4
//Reserved 		5
#define RxNE	6
#define TxE		7

/********** status register 2 **********/
#define	MSL		0
#define	BUSY	1
#define TRA		2
//RESERVED		3

/********** Clock Control Register************/
#define CCR   0
#define DUTY  14
#define FS   15

#define	MASTER_TRANSMIT		0
#define MASTER_RECEIVE		1

#define ADDRESS_7_BIT_MODE	0
#define ADDRESS_10_BIT_MODE	1

void configureI2cAddress(I2C_REG *i2c_reg, int ownAddress, int addr10Bit);

void configureI2C(I2C_REG *i2c_reg);

void generateStart(I2C_REG *i2c_reg);

void sendHeaderForReceive(I2C_REG *i2c_reg, int address);

void sendAddress(I2C_REG *i2c_reg, int address, int addressMode, int rw);

void i2cWriteData(int data, I2C_REG *i2c_reg);

uint8_t i2cReadData(I2C_REG *i2c_reg);

void masterSendNack(I2C_REG *i2c_reg);

void i2cStop(I2C_REG *i2c_reg);

int status1(I2C_REG *i2c_reg, int bit);

int status2(I2C_REG *i2c_reg, int bit);

void dmaRequestEnable(I2C_REG *i2c_reg);

#endif // __I2C_H__
