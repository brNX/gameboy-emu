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

#define Z_FLAG	 0x80	/* Zero				Bit 7 */
#define N_FLAG   0x40	/* Add/Substract	Bit 6 */
#define H_FLAG	 0x20	/* Half Carry		Bit 5 */
#define C_FLAG	 0x10	/* Carry			Bit 4 */

//é 0 ?
//com branch
#define CHECK_Z(val)  F = val ? F & ~Z_FLAG : F|Z_FLAG;

//com lookup
#define CHECK_ZL(val)  F = ZeroLookup[val];

//se houve halfcarry
#define CHECK_H(val) F |= (H_FLAG & ((A ^ (val) ^ opAux.Byte.l) << 1));

//se houve carry (0001 no opAux.Byte.h , logo 0001 << 4 = 0001 0000 = 0x10 = C_FLAG)
#define CHECK_C_ADD(val) F |= (opAux.Byte.h << 4);

//Set if no borrow (0001 no opAux.Byte.h , logo 0001 << 4 = 0001 0000 = 0x10 = C_FLAG)
#define CHECK_C_SUB(val) F |= ((uint8_t) (-(int8_t)opAux.Byte.h) << 4);


#define ADD_A(val) \
	opAux.Word = (uint16_t) A + (uint16_t)val;\
	CHECK_Z(opAux.Byte.l)\
	F &= ~N_FLAG;\
	CHECK_H(opAux.Byte.l)\
	CHECK_C_ADD(val)\
	A=opAux.Byte.l

#define ADC_A(val) \
	opAux.Word = (uint16_t) A + (uint16_t)val + ((uint16_t)(F & C_FLAG) >> 4) ;\
	CHECK_Z(opAux.Byte.l)\
	F &= ~N_FLAG;\
	CHECK_H(opAux.Byte.l)\
	CHECK_C_ADD(val)\
	A=opAux.Byte.l


#define SUB_A(val) \
	opAux.Word = (uint16_t) A - (uint16_t)val;\
	CHECK_Z(opAux.Byte.l)\
	F |= N_FLAG;\
	CHECK_H(opAux.Byte.l)\
	CHECK_C_SUB(val)\
	A=opAux.Byte.l

#define SBC_A(val) \
	opAux.Word = (uint16_t) A - (uint16_t)val - ((uint16_t)(F & C_FLAG) >> 4) ;\
	CHECK_Z(opAux.Byte.l)\
	F |= N_FLAG;\
	CHECK_H(opAux.Byte.l)\
	CHECK_C_SUB(val)\
	A=opAux.Byte.l

#define AND_A(val) \
	A &= val ;\
	/*00100000 = 0x20 ;  10100000 = 0xA0*/ \
	F = val ? 0x20 : 0xA0

#define XOR_A(val) \
	A ^= val ;\
	/*00000000 = 0x0 ;  10000000 = Z_FLAG*/ \
	F = val ? 0x0 : Z_FLAG

#define OR_A(val) \
	A |= val ;\
	/*00000000 = 0x0 ;  10000000 = Z_FLAG*/ \
	F = val ? 0x0 : Z_FLAG

#define CP_A(val) \
	opAux.Word = (uint16_t) A - (uint16_t)val;\
	CHECK_Z(opAux.Byte.l)\
	F |= N_FLAG;\
	CHECK_H(opAux.Byte.l)\
	CHECK_C_SUB(val)

#define INC(val) \
	opAux.Word = (uint16_t)val + 1 ;\
	CHECK_Z(opAux.Byte.l)\
	F &= ~N_FLAG;\
	CHECK_H(opAux.Byte.l)\
	val=opAux.Byte.l

#define DEC(val) \
	opAux.Word = (uint16_t)val - 1 ;\
	CHECK_Z(opAux.Byte.l)\
	F |= N_FLAG;\
	CHECK_H(opAux.Byte.l)\
	val=opAux.Byte.l

/*tmp := a,
if nf then
 if hf or [a AND 0x0f > 9] then tmp -= 0x06
 if cf or [a > 0x99] then tmp -= 0x60
else
 if hf or [a AND 0x0f > 9] then tmp += 0x06
 if cf or [a > 0x99] then tmp += 0x60
endif,
tmp => flags, cf := cf OR [a > 0x99],
hf := a.4 XOR tmp.4, a := tmp
*/

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

	//ZeroLookupTable
	const static int ZeroLookup[256] =
	{ Z_FLAG, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
			, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
			, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
			, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	};

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
			int pause;
			int halt;
	} Z80;
	extern Z80 gbcpu;

	void resetZ80(); //            -> resets the CPU core
	int execute(int nclyces);//   -> the core executes n cycles
	/*Z80 getcontext(); //      -> returns the CPU context
	 void setcontext(Z80 * cpu); //   -> sets the CPU context*/
	void interruptZ80(); //      -> sends an interrupt signal

#ifdef __cplusplus
}
#endif

#endif /* Z80_H_ */
