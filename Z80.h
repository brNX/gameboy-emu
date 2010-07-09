/*
 * Z80.h
 *
 *  Created on: 2010/06/17
 *      Author: brNX
 */

#ifndef Z80_H_
#define Z80_H_

#include "types.h"

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
#define IME gbcpu.ime

#define Z_FLAG	 0x80	/* Zero				Bit 7 */
#define N_FLAG   0x40	/* Add/Substract	Bit 6 */
#define H_FLAG	 0x20	/* Half Carry		Bit 5 */
#define C_FLAG	 0x10	/* Carry			Bit 4 */

#ifdef __cplusplus
extern "C"
{
#endif

	//union para registo 16bit com accesso 8bit
	typedef union
	{
			struct
			{
                                #ifndef B_ENDIAN
                                uint8 l,h; /* ...in little-endian architecture */
				#else
                                uint8 h, l; /* ...in big-endian architecture */
				#endif
			} Byte;
                        uint16 Word;
	} reg16bit;

	typedef union
	{
		struct
		{
                        #ifndef B_ENDIAN
                        uint16 l,h; /* ...in little-endian architecture */
			#else
                        uint16 h, l; /* ...in big-endian architecture */
			#endif
		} W;
                uint32 DW;
	} reg32bit;

	typedef struct
	{
			reg16bit af, bc, de, hl, sp, pc;
                        int ime;
			int cyclecounter;
			int pause;
			int halt;
	} Z80;
	extern Z80 gbcpu;

	void resetZ80(); //            -> resets the CPU core
	int execute(int nclyces);//   -> the core executes n cycles
	void interruptZ80(); //      -> sends an interrupt signal
	void printStatusZ80();
        void execOpcode(uint8 opcode);


#ifdef __cplusplus
}
#endif

#endif /* Z80_H_ */
