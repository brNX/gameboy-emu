/*
 * memory.h
 *
 *  Created on: 2010/06/18
 *      Author: brNX
 */

#ifndef MEMORY_H_
#define MEMORY_H_

//#include <stdint.h>
#include "types.h"
#include "cartridge.h"


#ifdef __cplusplus
extern "C"
{
#endif

        uint8  * gb_memory;
        Cartridge * gb_cart;
#ifdef WIN32
        __inline uint8 readMem(uint16 address);
        __inline uint8 readOpcode(uint16 address);
        __inline void writeMem(uint16 address, uint8 value);
#else
        inline uint8 readMem(uint16 address);
        inline uint8 readOpcode(uint16 address);
        inline void writeMem(uint16 address, uint8 value);
#endif


#ifdef __cplusplus
}
#endif

#endif /* MEMORY_H_ */
