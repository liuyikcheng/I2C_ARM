#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "RNG.h"
#include "RCC.h"
#include <stdint.h>



void HASH_RNG_IRQHandler(){
	RNG_reg->RNG_CR &= ~(1<<2);
}

int main(void){

	int a = 0;

	unresetEnableRngClock();
	rngConfigure();
	rngInterruptConfigure();

	HAL_NVIC_EnableIRQ(HASH_RNG_IRQn);

	while(1){
		if(RNG_reg->RNG_SR = 1)
			a = RNG_reg->RND_DR;
	}
}
