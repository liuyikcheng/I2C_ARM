#include "I2C.h"

void configureI2C(){

	I2C_reg->I2C_CR1 |= 1;  //peripheral enable
	I2C_reg->I2C_CR1 &= ~(1<<15);  //unreset
	I2C_reg->I2C_CR2 |= (1<<10);  // ITBUFEN buffer interrupt enable
	I2C_reg->I2C_CR2 |= (1<<9);  // ITEVTEN event interrupt enable
	I2C_reg->I2C_CR2 |= (1<<8);  // ITERREN error interrupt enable

}

//To generate start bit and select an address and determine wheater write or read data
void i2cStart(int address, int rw){

    // wait until I2C1 is not busy anymore
    while ((I2C_reg->I2C_SR2)&2 != 0){

    // Send I2C1 START condition
    I2C_reg->I2C_CR1 |= (1<<8);
    }

    if((I2C_reg->I2C_SR1)&1 == 1) // if start bit was sent (master)
        //handle

    // Send slave Address for write
    I2C_reg->I2C_DR = ((address<<1)|rw);  // rw = 0 send data, rw = 1 receive data

    //EV6
    if((I2C_reg->I2C_SR1)&2 == 1) //if address was sent (master)
      //handle

    //EV8_1
    while((I2C_reg->I2C_SR1)&0x80 == 1); //wait for data write to DR

}

//To write data to the data register of I2C
void i2cWriteData(uint8 data){

	I2C_reg->I2C_DR = data;
}

//To generate a stop bit
void i2cStop(){

	I2C_reg->I2C_CR1 |= (1<<9);

}


