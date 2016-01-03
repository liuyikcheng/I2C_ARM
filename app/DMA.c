#include "DMA.h"
#include "stm32f4xx.h"
#include "gpio.h"
#include "RCC.h"


void connectDMAnI2C(Stream_t *stream, uint32_t mAddr, uint32_t pAddr, int numOfData){

	stream->PAR =  pAddr;					//peripheral address
	stream->M0AR = mAddr; 				//memory address
	stream->NDTR = numOfData;     // Number of data items to transfer

}

void configDMAstream(Stream_t *stream, int channel, int direction){
	DMAUnresetEnableClock();

		 stream->CR &= ~(1 << EN);							//Stream Disable
		uint32_t data =  stream->CR; 	 	 	 	 	  	 	 	 	 	 	 	 	 	// *read-only ->stream (enabled) */

		stream->CR |= ( 1 << PINC ) | ( 1 << MINC ) | ( 1 << PL0 ) | ( 1 << PL1 ) ;//| ( 1 << TCIE );
		uint32_t data2 =  stream->CR;

		stream->CR &=  ~(3 << 25);
		stream->CR |= (channel << 25);  					//select channel

		stream->CR &= ~(3 << 6);
		stream->CR |= (direction << 6 );      		//select dma transfer mode


		stream->CR &= ~(3 << 13);
		stream->CR |= (DMA_MemoryDataSize_byte << 13); //set the memory data size as byte

		stream->CR &= ~(3 << 11);
		stream->CR |= (DMA_PeripheralDataSize_byte << 11); //set the peripheral data size as byte

		stream->CR &= ~(1 << MINC);
		stream->CR |= (DMA_MemoryInc_Enable << MINC);      //enable the memory increment

		stream->CR &= ~(1 << PINC);
		stream->CR |= (DMA_PeripheralInc_Disable << PINC); //disable the peripheral increment

		stream->CR &= ~(2 << 23);
		stream->CR |= (DMA_MemoryBurst_Single << 23);    //set single memory burst


		stream->CR &= ~(2 << 21);
		stream->CR |= (DMA_PeripheralBurst_Single << 21); //set single peripheral burst
		uint32_t data3 =  stream->CR;

		stream->FCR = FIFO_DISABLE;               		 	//Disable FIFO

		stream->CR &= ~(15 << 1);
		stream->CR |= (15 << 1);							// enable all interrupt(TC, HT, TE) and EN bit
		 uint32_t dataIn = stream->CR;
	}


void enableDMA(Stream_t *stream){
	stream->CR |= 1;     						// Dma stream Enable

}

void checkEvent(DMA_reg *dma, int flag){
	int bit = ((dma->HISR)>>flag)&1;
	while(bit == 0 ){
		bit = ((dma->HISR)>>flag)&1;
		bit = dma->HIFCR;
	}
	dma->HIFCR |= (1<<flag);
}

