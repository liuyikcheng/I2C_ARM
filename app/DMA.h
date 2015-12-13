#ifndef	__DMA_H__
#define	__DMA_H__
#include <stdint.h>

typedef struct DMA_Type DMA_reg;
typedef struct{
	  volatile uint32_t CR;
	  volatile uint32_t NDTR;
	  volatile uint32_t PAR;
	  volatile uint32_t M0AR;
	  volatile uint32_t M1AR;
	  volatile uint32_t FCR;
}Stream_t;

struct DMA_Type{
  volatile uint32_t LISR;
  volatile uint32_t HISR;
  volatile uint32_t LIFCR;
  volatile uint32_t HIFCR;
  Stream_t	S0;
  Stream_t	S1;
  Stream_t	S2;
  Stream_t	S3;
  Stream_t	S4;
  Stream_t	S5;
  Stream_t	S6;
  Stream_t	S7;
};

#define dma1   ((DMA_reg*)0x40026000)
#define dma2   ((DMA_reg*)0x40026400)





typedef enum {FAILED = 0,
			PASSED = !FAILED
			} TestStatus;


#define channel0	0
#define channel1	1
#define channel2	2
#define channel3	3
#define channel4	4
#define channel5	5
#define channel6	6
#define channel7	7

#define P2M	0
#define M2P	1
#define M2M	2

#define Priority_Low		0
#define Priority_Medium		1
#define Priority_High		2
#define Priority_VeryHigh	3

#define DMA_PeripheralInc_Enable	1
#define DMA_PeripheralInc_Disable	0

#define DMA_MemoryInc_Enable		1
#define DMA_MemoryInc_Disable		0

#define DMA_MemoryBurst_Single	0
#define DMA_MemoryBurst_Incr4	1
#define DMA_MemoryBurst_Incr8	2
#define DMA_MemoryBurst_Incr16	3

#define DMA_PeripheralBurst_Single	0
#define DMA_PeripheralBurst_Incr4	1
#define DMA_PeripheralBurst_Incr8	2
#define DMA_PeripheralBurst_Incr16	3



#define DMA_MemoryDataSize_byte 	0
#define DMA_MemoryDataSize_halfword 1
#define DMA_MemoryDataSize_Word 	2
#define DMA_MemoryDataSize_reserved 3

#define DMA_PeripheralDataSize_byte		0
#define DMA_PeripheralDataSize_halfword	1
#define DMA_PeripheralDataSize_Word 	2
#define DMA_PeripheralDataSize_reserved	3

#define TC_interrupt_disabled 0
#define TC_interrupt_enabled  1

#define Quater_full_FIFO		0
#define Half_full_FIFO			1
#define	ThreeperFour_full_FIFO	2
#define Full_FIFO				3

#define FTH		0

#define EN		0
#define PINC	9
#define MINC	10
#define PL0		16
#define PL1		17
#define TCIE	4

#define CHTIF7	26
#define CTCIF7	27

#define PINC	9
#define MINC	10

#define DMAx_EN			1
#define FIFO_DISABLE	0

#define ARRAYSIZE 800
#define DMA_STREAM_IRQHANDLER    DMA2_Stream0_IRQHandler

void configDMAM2M();
void DMA_memcpy8( uint32_t pDstAddr, uint32_t pSrcAddr, unsigned int uSize );
void enableDMA();
void DMA_interruptTransfer();
//int* getSourceData();
//int* getDestinationData();
//TestStatus Buffercmp(const uint32_t* pBuffer, uint32_t* pBuffer1, uint16_t BufferLength);
//int* getADC1Data();
//void resetTransferCompleteError();
//int getStatus();
//void enableDMA();

#endif	//__DMA_H__
