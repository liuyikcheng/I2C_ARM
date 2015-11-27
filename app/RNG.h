#ifndef __RNG_H__
#define __RNG_H__

#include <stdint.h>



typedef struct RNG_t RNG_REG;
struct RNG_t{
	uint32_t RNG_CR;
	uint32_t RNG_SR;
	uint32_t RND_DR;

};

void rngConfigure();

#define RNG_REG_ADDRESS		0x50060800

#define RNG_reg		((RNG_REG *)RNG_REG_ADDRESS)

#endif // __RNG_H__
