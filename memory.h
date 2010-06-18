/*
 * memory.h
 *
 *  Created on: 2010/06/18
 *      Author: brNX
 */

#ifndef MEMORY_H_
#define MEMORY_H_

#include <stdint.h>

uint8_t gb_memory[0x10000];

static inline uint8_t ReadMemory(uint16_t address);
static inline void WriteMemory(uint16_t address, uint8_t value);

#endif /* MEMORY_H_ */
