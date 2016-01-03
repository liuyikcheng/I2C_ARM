#include "I2C.h"

void configureI2C(I2C_REG *i2c_reg){
	int a;
	i2c_reg->I2C_CR1 &= ~(1<<SWRST);  	//	unreset

	i2c_reg->I2C_CR1 &= ~(1<<NOSTRETCH);	//	clock stretch enable

	a = i2c_reg->I2C_CR1;

	i2c_reg->I2C_CR2 &= ~(63);
	i2c_reg->I2C_CR2 |= (0x2);		//	set clock freq to 4MHz
//	i2c_reg->I2C_CR2 |= (1<<ITBUFEN);  	// ITBUFEN buffer interrupt enable
	i2c_reg->I2C_CR2 |= (1<<ITEVTEN);  	// ITEVTEN event interrupt enable
	i2c_reg->I2C_CR2 |= (1<<ITERREN);  	// ITERREN error interrupt enable


	i2c_reg->I2C_CCR &= ~(1<<FS);	// standard mode
	i2c_reg->I2C_CCR &= ~(4095<<CCR);
	i2c_reg->I2C_CCR |= 0x100;		// Clock control register in Fm/Sm mode as

	i2c_reg->I2C_CR1 |= (1<<ACK);	//	acknowledge enable
	i2c_reg->I2C_CR1 |= (1<<PE);		//	peripheral enable

}

void configureI2C_DMAenable(I2C_REG *i2c_reg){
	i2c_reg->I2C_CR2 |= (1<<DMAEN);
}

void configureI2cAddress(I2C_REG *i2c_reg, int ownAddress, int addr10Bit){

	if(addr10Bit){
		i2c_reg->I2C_OAR1 |= (1<<15);	// 10-bit address mode
		i2c_reg->I2C_OAR1 &= ~(0x3FF);
		i2c_reg->I2C_OAR1 = ownAddress;
	}
	else{
		i2c_reg->I2C_OAR1 &= ~(1<<15);	//	7-bit address mode
		i2c_reg->I2C_OAR1 &= ~(127<<1);
		i2c_reg->I2C_OAR1 |= (ownAddress<<1); // set own address
	}

	int a = i2c_reg->I2C_OAR1;

}

// read data from status register 1
int status1(I2C_REG *i2c_reg, int bit){
	uint32_t stat = ((i2c_reg->I2C_SR1>>bit)&1);
	uint32_t a = i2c_reg->I2C_SR1;
	uint32_t b = i2c_reg->I2C_SR2;
	uint32_t c = I2C_reg->I2C_SR1;
	uint32_t d = I2C_reg->I2C_SR2;
	return stat;
}

// read data from status register 2
int status2(I2C_REG *i2c_reg, int bit){
	uint32_t stat = ((i2c_reg->I2C_SR2>>bit)&1);
	uint32_t a = i2c_reg->I2C_SR2;
	return stat;
}

//To write data to the data register of I2C
void i2cWriteData(int data, I2C_REG *i2c_reg){
  
	while(status1(i2c_reg, TxE) == 0);
	i2c_reg->I2C_DR = data;
}

uint8_t i2cReadData(I2C_REG *i2c_reg){
	while(status1(i2c_reg, RxNE) == 0);
	return i2c_reg->I2C_DR;
}

//generate start condition
void generateStart(I2C_REG *i2c_reg){

	i2c_reg->I2C_CR1 |= (1<<8);
	i2c_reg->I2C_CR2 |= (1<<11);
	while(status1(i2c_reg, SB) == 0); //start bit was sent

}

void sendHeaderForReceive(I2C_REG *i2c_reg, int address){
	int most2Bit = (address>>6);
	int header = ((0xF0|(most2Bit<<2))|1);
	i2c_reg->I2C_DR = header;
	while(status1(i2c_reg, ADDR) == 0);
}

//select the address and decide write or read
void sendAddress(I2C_REG *i2c_reg, int address, int addressMode, int rw){
	int c, d;
	if (addressMode == ADDRESS_10_BIT_MODE){
		int most2Bit = (address>>6);
		int header = (0xF0|(most2Bit<<2));
		int slaveAddress = address&0xFF;

		i2c_reg->I2C_DR = header;

		while(status1(i2c_reg, ADD10) == 0);
		i2c_reg->I2C_DR = slaveAddress;

		while(status1(i2c_reg, ADDR) == 0);

		if(rw == MASTER_RECEIVE){
      
      while(status1(I2C_reg,ADDR) == 0);
      generateStart(i2c_reg);
			sendHeaderForReceive(i2c_reg, I2C1_OWNADDRESS);
      
		}
	}
	else{
		int slaveAddress = ((address<<1)|rw);
		uint32_t a = i2c_reg->I2C_SR1;
		uint32_t b = i2c_reg->I2C_SR2;
		uint32_t c = I2C_reg->I2C_SR1;
		uint32_t d = I2C_reg->I2C_SR2;
    i2c_reg->I2C_DR = slaveAddress;

	}
}

//disable acknowledge to indicate the master want to stop receive data
void masterSendNack(I2C_REG *i2c_reg){
	i2c_reg->I2C_CR1 &= ~(1<<10);
}
//To generate a stop bit
void i2cStop(I2C_REG *i2c_reg){

	i2c_reg->I2C_CR1 |= (1<<9);
}

void dmaRequestEnable(I2C_REG *i2c_reg){
  i2c_reg->I2C_CR2 |= (1<<11);
}

