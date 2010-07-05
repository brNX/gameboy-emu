/*
 * memory.c
 *
 *  Created on: 2010/06/18
 *      Author: brNX
 */
#include "memory.h"

//TODO: for now
extern inline uint8_t readMem(uint16_t address)
{
	return (gb_memory[address]);
}

extern inline void writeMem(uint16_t address, uint8_t value)
{
	gb_memory[address] = value;
}
