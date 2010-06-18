/*
 * memory.c
 *
 *  Created on: 2010/06/18
 *      Author: brNX
 */
#include "memory.h"

//TODO: for now
static inline uint8_t ReadMemory(uint16_t address)
{
	return (gb_memory[address]);
}

static inline void WriteMemory(uint16_t address, uint8_t value)
{
	gb_memory[address] = value;
}
