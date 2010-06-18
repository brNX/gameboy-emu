/*
 * Z80.h
 *
 *  Created on: 2010/06/17
 *      Author: brNX
 */

#ifndef Z80_H_
#define Z80_H_

#include <stdint.h>


//union para registo 16bit com accesso 8bit
typedef union
{
  struct { uint8_t h,l; } S;
  uint16_t M;
} reg16bit;

typedef struct
{
		reg16bit AF,BC,DE,HL,SP,PC;
		int cyclecounter;
		uint8_t * memorymap;
}Z80;

void reset(); //            -> resets the CPU core
int execute(int nclyces);//   -> the core executes n cycles
Z80 getcontext(); //      -> returns the CPU context
void setcontext(Z80 * context); //   -> sets the CPU context
void interrupt();  //      -> sends an interrupt signal
uint8_t readOpcode(uint16_t address);

#endif /* Z80_H_ */
