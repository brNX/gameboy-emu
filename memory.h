/*
 * memory.h
 *
 *  Created on: 2010/06/18
 *      Author: brNX
 */

#ifndef MEMORY_H_
#define MEMORY_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

	uint8_t gb_memory[0x10000];

	inline uint8_t readMem(uint16_t address);
	inline void writeMem(uint16_t address, uint8_t value);

#ifdef __cplusplus
}
#endif

#endif /* MEMORY_H_ */
