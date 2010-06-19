/*
 * Z80.h
 *
 *  Created on: 2010/06/17
 *      Author: brNX
 */

#ifndef Z80_H_
#define Z80_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

	//union para registo 16bit com accesso 8bit
	typedef union
	{
			struct
			{
					uint8_t h, l;
			} S;
			uint16_t M;
	} reg16bit;

	typedef struct
	{
			reg16bit AF, BC, DE, HL, SP, PC;
			int cyclecounter;
			uint8_t * memorymap;
			int pause;
			int halt;
	} Z80;

	void reset(Z80 * cpu); //            -> resets the CPU core
	int execute(Z80 * cpu,int nclyces);//   -> the core executes n cycles
	/*Z80 getcontext(); //      -> returns the CPU context
	void setcontext(Z80 * cpu); //   -> sets the CPU context*/
	void interrupt(Z80 * cpu); //      -> sends an interrupt signal
	uint8_t readOpcode(uint16_t address);

#ifdef __cplusplus
}
#endif

#endif /* Z80_H_ */
