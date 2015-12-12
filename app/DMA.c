#include "DMA.h"
#include "stm32f4xx.h"
#include "gpio.h"
#include "RCC.h"


void configDMAM2M(DMA_reg *dma, int channel, int direction) {  // stream 7  channel 0

	DMAUnresetEnableClock();

	 dma->S4.CR &= ~(1 << EN);							//Stream Disable
	uint32_t data =  dma->S4.CR; 	 	 	 	 	  	 	 	 	 	 	 	 	 	// *read-only ->stream (enabled) */

	 dma->S4.CR |= ( 1 << PINC ) | ( 1 << MINC ) | ( 1 << PL0 ) | ( 1 << PL1 ) ;//| ( 1 << TCIE );
	uint32_t data2 =  dma->S4.CR;

	 dma->S4.CR &=  ~(3 << 25);
	 dma->S4.CR |= (channel << 25);  					/* CHANNEL */

	 dma->S4.CR &= ~(3 << 6);
	 dma->S4.CR |= (direction << 6 );      					/* DIRECTION TRANSFER MODE M2M */

	//source and destination data size word=32bit
	 dma->S4.CR &= ~(3 << 13);							/* DMA_MemoryDataSize_Word */
	 dma->S4.CR |= (DMA_MemoryDataSize_byte << 13);

	 dma->S4.CR &= ~(3 << 11);							/* DMA_PeripheralDataSize_Word */
	 dma->S4.CR |= (DMA_PeripheralDataSize_byte << 11);

	//MEMORY AND PERIPHERAL increment disable
	 dma->S4.CR &= ~(1 << MINC);
	 dma->S4.CR |= (DMA_MemoryInc_Enable << MINC);

	 dma->S4.CR &= ~(1 << PINC);
	 dma->S4.CR |= (DMA_PeripheralInc_Disable << PINC);

	 dma->S4.CR &= ~(2 << 23);
	 dma->S4.CR |= (DMA_MemoryBurst_Single << 23);


	 dma->S4.CR &= ~(2 << 21);
	 dma->S4.CR |= (DMA_PeripheralBurst_Single << 21);
	uint32_t data3 =  dma->S4.CR;


	 //dma->S4.FCR &= (11 << FTH);
	 //dma->S4.FCR |= (Full_FIFO << FTH);

	dma->S4.FCR = FIFO_DISABLE;               		 	//Disable FIFO
	int dma5 =  dma->S4.FCR;

	 dma->S4.CR &= ~(15 << 1);
//	 dma->S4.CR |= (15 << 1);							// enable all interrupt(TC, HT, TE) and EN bit
	 uint32_t dataIn = dma->S4.CR;
}

void DMA_interruptTransfer(DMA_reg *dma){
	dma->S4.CR &= ~(3 << 9);
	dma->S4.CR |= (3 <<  9);
}

void DMA_memcpy8(DMA_reg *dma, uint32_t pSrcAddr, uint32_t pDstAddr, unsigned int uSize ){
    														/* As per page 233 this is how to configure a stream */
	uint32_t read ;
	if( (  dma->S4.CR & ( 1 << EN ) ) == 1 ){
		dma->S4.CR &= ~( 1 << EN );  					// 1. If stream is enabled, disable it
         while( (  dma->S4.CR & ( 1 << EN ) == 1) );
    }
	dma->S4.PAR =  (uint32_t)pDstAddr;					/* source address */
	dma->S4.M0AR = (uint32_t)pSrcAddr; 					/* destination address */
	dma->S4.NDTR = uSize;     							// Number of data items to transfer
    read =  dma->S4.CR;
}

void enableDMA(DMA_reg *dma){
	uint32_t stream2, stream3;
	 dma->S4.CR |= 1;     						// Stream Enable
	stream3 =  dma->S4.CR;

}







/*void resetTransferCompleteError(){
	uint32_t status;
	status =  DMA_HISR;
	if(status == 1){
		 DMA_HISR &= ~( 1 << 27 );
	}

/*TestStatus Buffercmp(const uint32_t* pBuffer, uint32_t* pBuffer1, uint16_t BufferLength)
{
  while(BufferLength--)
  {
    if(*pBuffer != *pBuffer1)
    {
      return FAILED;
    }

    pBuffer++;
    pBuffer1++;
  }

  return PASSED;
}

*/
