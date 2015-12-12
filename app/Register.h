#ifndef __Register_H__
#define __Register_H__

#include <stdint.h>

#ifndef HOST
#define RCC_REG_ADDRESS		0x40023800

#else

#include "HostRcc.h"

#define RCC_REG_ADDRESS (&HostRcc)

//#error I am trying to be genius

#endif // HOST

#endif // __Register_H__
