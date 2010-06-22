/*
 * Z80.h
 *
 *  Created on: 2010/06/17
 *      Author: brNX
 */

#ifndef Z80_H_
#define Z80_H_

//macros para aceder facilmente ao cpu
#define A gbcpu.af.Byte.h
#define F gbcpu.af.Byte.l
#define B gbcpu.bc.Byte.h
#define C gbcpu.bc.Byte.l
#define D gbcpu.de.Byte.h
#define E gbcpu.de.Byte.l
#define H gbcpu.hl.Byte.h
#define L gbcpu.hl.Byte.l
#define AF gbcpu.af.Word
#define BC gbcpu.bc.Word
#define DE gbcpu.de.Word
#define HL gbcpu.hl.Word
#define SP gbcpu.sp.Word
#define PC gbcpu.pc.Word

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

	//numero de ciclos correspondentes a cada opcode
	const static int Cycles[256] =
	{ 4, 12, 8, 8, 4, 4, 8, 4, 20, 8, 8, 8, 4, 4, 8, 4, 4, 12, 8, 8, 4, 4, 8,
			4, 12, 8, 8, 8, 4, 4, 8, 4, 12, 12, 8, 8, 4, 4, 8, 4, 12, 8, 8, 8,
			4, 4, 8, 4, 12, 12, 8, 8, 4, 12, 12, 12, 12, 8, 8, 8, 4, 4, 8, 4,

			4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4,
			8, 4, 4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4,
			4, 4, 8, 4, 8, 8, 8, 8, 8, 8, 4, 8, 4, 4, 4, 4, 4, 4, 8, 4,

			4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4,
			8, 4, 4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4,
			4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4,

			20, 12, 16, 16, 24, 16, 8, 16, 20, 16, 16, 4, 24, 24, 8, 16, 20,
			12, 16, 0, 24, 16, 8, 16, 20, 16, 16, 0, 24, 0, 8, 16, 12, 12, 8,
			0, 0, 16, 8, 16, 16, 4, 16, 0, 0, 0, 8, 16, 12, 12, 8, 4, 0, 16, 8,
			16, 12, 8, 16, 4, 0, 0, 8, 16, };

	//union para registo 16bit com accesso 8bit
	typedef union
	{
			struct
			{
#ifdef BIG_ENDIAN
					uint8_t l,h; /* ...in low-endian architecture */
#else
					uint8_t h, l; /* ...in high-endian architecture */
#endif
			} Byte;
			uint16_t Word;
	} reg16bit;

	typedef struct
	{
			reg16bit af, bc, de, hl, sp, pc;
			int cyclecounter;
			uint8_t * memorymap;
			int pause;
			int halt;
	} Z80;
	extern Z80 gbcpu;

	void resetZ80(); //            -> resets the CPU core
	int execute(int nclyces);//   -> the core executes n cycles
	/*Z80 getcontext(); //      -> returns the CPU context
	 void setcontext(Z80 * cpu); //   -> sets the CPU context*/
	void interruptZ80(); //      -> sends an interrupt signal
	inline uint8_t readOpcode(uint16_t address);

#ifdef __cplusplus
}
#endif

#endif /* Z80_H_ */
