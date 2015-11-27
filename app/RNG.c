#include "RNG.h"



void rngConfigure(){

	RNG_reg->RNG_CR |= 4;
}


void rngInterruptConfigure(){

	RNG_reg->RNG_CR |= 8;
}


