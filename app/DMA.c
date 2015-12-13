#include "DMA.h"
#include "stm32f4xx.h"
#include "gpio.h"
#include "RCC.h"


void configDMAM2M(void) {  // stream 7  channel 0

	DMAUnresetEnableClock();

	dma2->S7.CR &= ~(1 << EN);							//Stream Disable
	uint32_t data = dma2->S7.CR; 	 	 	 	 	  	 	 	 	 	 	 	 	 	// *read-only ->stream (enabled) */

	dma2->S7.CR |= ( 1 << PINC ) | ( 1 << MINC ) | ( 1 << PL0 ) | ( 1 << PL1 ) ;//| ( 1 << TCIE );
	uint32_t data2 = dma2->S7.CR;

	dma2->S7.CR &=  ~(3 << 25);
	dma2->S7.CR |= (channel0 << 25);  					/* CHANNEL 0 */

	dma2->S7.CR &= ~(2 << 6);
	dma2->S7.CR |= (M2M << 6 );      					/* DIRECTION TRANSFER MODE M2M */

	//source and destination data size word=32bit
	dma2->S7.CR &= ~(2 << 13);							/* DMA_MemoryDataSize_Word */
	dma2->S7.CR |= (DMA_MemoryDataSize_byte << 13);

	dma2->S7.CR &= ~(2 << 11);							/* DMA_PeripheralDataSize_Word */
	dma2->S7.CR |= (DMA_PeripheralDataSize_byte << 11);

	//MEMORY AND PERIPHERAL increment disable
	dma2->S7.CR &= ~(1 << MINC);
	dma2->S7.CR |= (DMA_MemoryInc_Enable << MINC);

	dma2->S7.CR &= ~(1 << PINC);
	dma2->S7.CR |= (DMA_PeripheralInc_Enable << PINC);

	dma2->S7.CR &= ~(2 << 23);
	dma2->S7.CR |= (DMA_MemoryBurst_Incr16 << 23);


	dma2->S7.CR &= ~(2 << 21);
	dma2->S7.CR |= (DMA_PeripheralBurst_Single << 21);
	uint32_t data3 = dma2->S7.CR;


	dma2->S7.FCR &= (11 << FTH);
	dma2->S7.FCR |= (Full_FIFO << FTH);

//	dma2->S7.FCR = FIFO_DISABLE;               		 	//Disable FIFO
	int dma5 = dma2->S7.FCR;

	dma2->S7.CR &= ~(15 << 1);
	dma2->S7.CR |= (15 << 1);							// enable all interrupt(TC, HT, TE) and EN bit
	uint32_t dataIn = dma2->S7.CR;
}

void DMA_interruptTransfer(void){
	dma2->S7.CR &= ~(3 << 9);
	dma2->S7.CR |= (3 <<  9);
}

void DMA_memcpy8( uint32_t pDstAddr, uint32_t pSrcAddr, unsigned int uSize ){
    														/* As per page 233 this is how to configure a stream */
	uint32_t read ;
	if( ( dma2->S7.CR & ( 1 << EN ) ) == 1 ){
         dma2->S7.CR &= ~( 1 << EN );  					// 1. If stream is enabled, disable it
         while( ( dma2->S7.CR & ( 1 << EN ) == 1) );
    }
	dma2->S7.PAR =  (uint32_t)pSrcAddr;					/* source address */
	dma2->S7.M0AR = (uint32_t)pDstAddr; 					/* destination address */
    dma2->S7.NDTR = uSize;     							// Number of data items to transfer
    read = dma2->S7.CR;
}

void enableDMA(){
	uint32_t stream2, stream3;
	dma2->S7.CR &= ~1;
	stream2 = dma2->S7.CR;
	dma2->S7.CR |= 1;     						// Stream Enable
	stream3 = dma2->S7.CR;
}







/*void resetTransferCompleteError(){
	uint32_t status;
	status = dma2->DMA_HISR;
	if(status == 1){
		dma2->DMA_HISR &= ~( 1 << 27 );
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
