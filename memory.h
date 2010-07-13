/*
 * memory.h
 *
 *  Created on: 2010/06/18
 *      Author: brNX
 */

#ifndef MEMORY_H_
#define MEMORY_H_

#include "types.h"
#include "cartridge.h"

#ifdef _MSC_VER
    #define INLINE __inline
#else
    #define INLINE inline
#endif


#ifdef __cplusplus
extern "C"
{
#endif

        uint8  * gb_memory;
        Cartridge * gb_cart;

        INLINE uint8 readMem(uint16 address);
        INLINE uint8 readOpcode(uint16 address);
        INLINE void writeMem(uint16 address, uint8 value);



#ifdef __cplusplus
}
#endif

#endif /* MEMORY_H_ */
