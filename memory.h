/*
 * memory.h
 *
 *  Created on: 2010/06/18
 *      Author: brNX
 */

#ifndef MEMORY_H_
#define MEMORY_H_

#include <stdint.h>
#include "types.h"


#ifdef __cplusplus
extern "C"
{
#endif

        uint8 gb_memory[0x10000];

        inline uint8 readMem(uint16 address);
        inline void writeMem(uint16 address, uint8 value);

#ifdef __cplusplus
}
#endif

#endif /* MEMORY_H_ */
