#include "DMA.h"
#include "stm32f4xx.h"
#include "gpio.h"
#include "RCC.h"


void configDMA(DMA_reg *dma, int channel, int direction) {  // stream 7  channel 0

	DMAUnresetEnableClock();

	 dma->S4.CR &= ~(1 << EN);							//Stream Disable
	uint32_t data =  dma->S4.CR; 	 	 	 	 	  	 	 	 	 	 	 	 	 	// *read-only ->stream (enabled) */

	 dma->S4.CR |= ( 1 << PINC ) | ( 1 << MINC ) | ( 1 << PL0 ) | ( 1 << PL1 ) ;//| ( 1 << TCIE );
	uint32_t data2 =  dma->S4.CR;

	 dma->S4.CR &=  ~(3 << 25);
	 dma->S4.CR |= (channel << 25);  					//select channel

	 dma->S4.CR &= ~(3 << 6);
	 dma->S4.CR |= (direction << 6 );      		//select dma transfer mode


	 dma->S4.CR &= ~(3 << 13);						
	 dma->S4.CR |= (DMA_MemoryDataSize_byte << 13); //set the memory data size as byte

	 dma->S4.CR &= ~(3 << 11);	
	 dma->S4.CR |= (DMA_PeripheralDataSize_byte << 11); //set the peripheral data size as byte

	 dma->S4.CR &= ~(1 << MINC);
	 dma->S4.CR |= (DMA_MemoryInc_Enable << MINC);      //enable the memory increment

	 dma->S4.CR &= ~(1 << PINC);  
	 dma->S4.CR |= (DMA_PeripheralInc_Disable << PINC); //disable the peripheral increment

	 dma->S4.CR &= ~(2 << 23);
	 dma->S4.CR |= (DMA_MemoryBurst_Single << 23);    //set single memory burst


	 dma->S4.CR &= ~(2 << 21);
	 dma->S4.CR |= (DMA_PeripheralBurst_Single << 21); //set single peripheral burst
	uint32_t data3 =  dma->S4.CR;

	dma->S4.FCR = FIFO_DISABLE;               		 	//Disable FIFO

	 dma->S4.CR &= ~(15 << 1);
//	 dma->S4.CR |= (15 << 1);							// enable all interrupt(TC, HT, TE) and EN bit
	 uint32_t dataIn = dma->S4.CR;
}

void DMA_interruptTransfer(DMA_reg *dma){
	dma->S4.CR &= ~(3 << 9);
	dma->S4.CR |= (3 <<  9);
}

// void dmaDirection(DMA_reg *dma, uint32_t pAddr, uint32_t mAddr, unsigned int numOfData, int direction){
  // if (direction == P2M) {
    // dma->S4.PAR =  pAddr;					/* source address */
    // dma->S4.M0AR = (uint32_t)pSrcAddr; 
  // }
// }

void dmaForI2C(DMA_reg *dma, uint32_t mAddr, uint32_t pAddr, int numOfData ){
    														/* As per page 233 this is how to configure a stream */
	uint32_t read ;

	dma->S4.PAR =  pAddr;					//peripheral address
	dma->S4.M0AR = mAddr; 				//memory address
	dma->S4.NDTR = numOfData;     // Number of data items to transfer
  read =  dma->S4.CR;
}

void enableDMA(DMA_reg *dma){
	 dma->S4.CR |= 1;     						// Dma stream Enable

}

