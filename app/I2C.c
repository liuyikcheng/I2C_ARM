#include "I2C.h"

void configureI2C(int OwnAddress){

	I2C_reg->I2C_CR1 &= ~(1<<15);  	//	unreset

	I2C_reg->I2C_OAR1 |= (1<<15);	//	7-bit address
	I2C_reg->I2C_OAR1 &= ~(127<<1);
	I2C_reg->I2C_OAR1 |= (OwnAddress<<1); // set own address

	I2C_reg->I2C_CR2 &= ~(63);
	I2C_reg->I2C_CR2 |= (2);		//	set clock freq to 2MHz
	I2C_reg->I2C_CR2 |= (1<<10);  	// ITBUFEN buffer interrupt enable
	I2C_reg->I2C_CR2 |= (1<<9);  	// ITEVTEN event interrupt enable
	I2C_reg->I2C_CR2 |= (1<<8);  	// ITERREN error interrupt enable

	I2C_reg->I2C_CCR &= ~(1<<15);	// standard mode
	I2C_reg->I2C_CCR &= ~(4095);
	I2C_reg->I2C_CCR |= 0x28;

	I2C_reg->I2C_CR1 |= 1;  		//	peripheral enable
}

//To generate start bit and select an address and determine whether write or read data
void i2cStart(int address, int rw){

    // wait until I2C1 is not busy anymore
    //while ((I2C_reg->I2C_SR2)&2 != 0){
	int b;

    // Send I2C1 START condition
    I2C_reg->I2C_CR1 |= (1<<8);
    //}

	if((I2C_reg->I2C_SR1)&1 == 1)// if start bit was sent (master)
		b = I2C_reg->I2C_CR2;

    // Send slave Address for write/read
    I2C_reg->I2C_DR = ((address<<1)|rw); // rw = 0 send data, rw = 1 receive data
    //}


    //EV6
    if((I2C_reg->I2C_SR1)&2 == 1) {//if address was sent (master)
    	b = I2C_reg->I2C_SR1;
    }

    //EV8_1
    while((I2C_reg->I2C_SR1)&0x80 == 1); //wait for data write to DR

}

//To write data to the data register of I2C
void i2cWriteData(int data){

	I2C_reg->I2C_DR = data;
}

//To generate a stop bit
void i2cStop(){

	I2C_reg->I2C_CR1 |= (1<<9);

}


