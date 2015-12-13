#include "I2C.h"

void configureI2C(I2C_REG *i2c_reg){
	int a;
	i2c_reg->I2C_CR1 &= ~(1<<15);  	//	unreset

	i2c_reg->I2C_CR1 &= ~(1<<7);	//	clock stretch enable

	a = i2c_reg->I2C_CR1;
/*
	i2c_reg->I2C_OAR1 &= ~(1<<15);	//	7-bit address
	i2c_reg->I2C_OAR1 &= ~(127<<1);
	i2c_reg->I2C_OAR1 |= (OwnAddress<<1); // set own address
*/
	i2c_reg->I2C_CR2 &= ~(63);
	i2c_reg->I2C_CR2 |= (0x2);		//	set clock freq to 4MHz
	i2c_reg->I2C_CR2 |= (1<<10);  	// ITBUFEN buffer interrupt enable
	i2c_reg->I2C_CR2 |= (1<<9);  	// ITEVTEN event interrupt enable
	i2c_reg->I2C_CR2 |= (1<<8);  	// ITERREN error interrupt enable

	i2c_reg->I2C_CCR &= ~(1<<15);	// standard mode
	i2c_reg->I2C_CCR &= ~(4095);
	i2c_reg->I2C_CCR |= 0x100;		// Clock control register in Fm/Sm mode as

	i2c_reg->I2C_TRISE &= ~(0x3F);
	i2c_reg->I2C_TRISE |= 0x2;

	i2c_reg->I2C_FLTR |= (1<<4);	// enable analog filter
	i2c_reg->I2C_FLTR &= ~(15);
	i2c_reg->I2C_FLTR |= (1);

	i2c_reg->I2C_CR1 |= 1;  		//	peripheral enable
	i2c_reg->I2C_CR1 |= (1<<10);	//	acknowledge enable
	a = i2c_reg->I2C_CR1;
	a = i2c_reg->I2C_OAR1;

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

//To generate start bit and select an address and determine whether write or read data
void i2cStart(int address, int rw, I2C_REG *i2c_reg){

	int a, b, c, d, e, f;

    // wait until I2C1 is not busy anymore
    while ((i2c_reg->I2C_SR2)&2 != 0);

    // Send I2C1 START condition
	i2c_reg->I2C_CR1 |= (1<<8);

	if((i2c_reg->I2C_SR1)&1 == 1){// if start bit was sent (master)
		a = 0;
	//	i2c_reg->I2C_DR = ((address<<1)|rw); // rw = 0 send data, rw = 1 receive data
	}

    // Send slave Address for write/read

	i2c_reg->I2C_DR = ((address<<1)|rw); // rw = 0 send data, rw = 1 receive data

//	while(((I2C_reg->I2C_SR1>>8)&1) == 1){
	//	I2C_reg->I2C_SR1 &= ~(1<<8); //clrea BERR bit
	//	i2c_reg->I2C_DR = ((address<<1)|rw); // rw = 0 send data, rw = 1 receive data
//	}


	c = i2c_reg->I2C_SR1;
	b = i2c_reg->I2C_SR2;
	d = I2C_reg->I2C_SR1;
	e = I2C_reg->I2C_SR2;

	a = i2c_reg->I2C_DR;

    //EV6
	//while((i2c_reg->I2C_SR1>>1)&1 == 0);//if address was sent (master)


    //EV8_1
    //while((i2c_reg->I2C_SR1)&0x80 == 1); //wait for data write to DR

}



// read data from status register 1
int status1(I2C_REG *i2c_reg, int bit){
	uint32_t stat = ((i2c_reg->I2C_SR1>>bit)&1);
	uint32_t a = i2c_reg->I2C_SR1;
	uint32_t b = i2c_reg->I2C_SR2;
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
//	int c = I2C_reg->I2C_SR1;
//	int d = I2C_reg->I2C_SR1;
	i2c_reg->I2C_DR = data;
//	int a = i2c_reg->I2C_SR1;
//	int b = i2c_reg->I2C_SR2;
//	c = I2C_reg->I2C_SR1;
//	d = I2C_reg->I2C_SR2;
}

uint8_t i2cReadData(I2C_REG *i2c_reg){
	while(status1(i2c_reg, RxNE) == 0);
	return i2c_reg->I2C_DR;
}

//generate start condition
void generateStart(I2C_REG *i2c_reg){

	i2c_reg->I2C_CR1 |= (1<<8);

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

	if (addressMode == ADDRESS_10_BIT_MODE){
		int most2Bit = (address>>6);
		int header = (0xF0|(most2Bit<<2));
		int slaveAddress = address&0xFF;

		i2c_reg->I2C_DR = header;

		while(status1(i2c_reg, ADD10) == 0);
		i2c_reg->I2C_DR = slaveAddress;

		while(status1(i2c_reg, ADDR) == 0);

		if(rw == MASTER_RECEIVE){

		}
	}
	else{
		int slaveAddress = ((address<<1)|rw);
		i2c_reg->I2C_DR = slaveAddress;
		while(status1(i2c_reg, ADDR) == 0);
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


