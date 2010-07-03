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
#define IME gbcpu.ime

#define Z_FLAG	 0x80	/* Zero				Bit 7 */
#define N_FLAG   0x40	/* Add/Substract	Bit 6 */
#define H_FLAG	 0x20	/* Half Carry		Bit 5 */
#define C_FLAG	 0x10	/* Carry			Bit 4 */

//is 0 ?
//if (val==0) F |= Z_FLAG; else F &= ~Z_FLAG;
#define CHECK_Z(val) \
	F = (F & ~Z_FLAG) | (-(val==0) & Z_FLAG);

//com lookup
#define CHECK_ZL(val)  F = ZeroLookup[val];

//se houve halfcarry
#define CHECK_H(val) F |= (H_FLAG & ((A ^ (val) ^ opAux.Byte.l) << 1));

//se houve carry (0001 no opAux.Byte.h , logo 0001 << 4 = 0001 0000 = 0x10 = C_FLAG)
#define CHECK_C_ADD(val) F |= (opAux.Byte.h << 4);

//Set if no borrow (0001 no opAux.Byte.h , logo 0001 << 4 = 0001 0000 = 0x10 = C_FLAG)
#define CHECK_C_SUB(val) F |= ((uint8_t) (-(int8_t)opAux.Byte.h) << 4);

//se houve halfcarry 16bit
#define CHECK_H16(val) \
	opAux.Word = opAux32.W.l; \
	F |= (H_FLAG & ((H ^ ((val)>>8)^ opAux.Byte.h) << 1));

//se houve carry (0001 no opAux32.W.h , logo 0001 << 4 = 0001 0000 = 0x10 = C_FLAG) 16bit
#define CHECK_C_ADD16(val) F |= (uint8_t)(opAux32.W.h << 4);


#define ADD_A(val) \
	opAux.Word = A + val;\
	F=0x0;\
	CHECK_Z(opAux.Byte.l)\
	CHECK_H(val)\
	CHECK_C_ADD(val)\
	A=opAux.Byte.l

#define ADC_A(val) \
	opAux.Word =  A + val + ((F & C_FLAG) >> 4) ;\
	F=0x0;\
	CHECK_Z(opAux.Byte.l)\
	CHECK_H(val)\
	CHECK_C_ADD(val)\
	A=opAux.Byte.l

#define SUB_A(val) \
	opAux.Word = A - val;\
	F=N_FLAG;\
	CHECK_Z(opAux.Byte.l)\
	CHECK_H(val)\
	CHECK_C_SUB(val)\
	A=opAux.Byte.l

#define SBC_A(val) \
	opAux.Word =  A - val - ((F & C_FLAG) >> 4) ;\
	F=N_FLAG;\
	CHECK_Z(opAux.Byte.l)\
	CHECK_H(val)\
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
	opAux.Word =  A - val;\
	F=N_FLAG;\
	CHECK_Z(opAux.Byte.l)\
	CHECK_H(val)\
	CHECK_C_SUB(val)

#define INC(val) \
	opAux.Word = val + 1 ;\
        val=opAux.Byte.l;\
        F=(F&C_FLAG) | INCLookup[val]

#define DEC(val) \
	opAux.Word = val - 1 ;\
        val=opAux.Byte.l;\
        F=(F&C_FLAG) | DECLookup[val]

#define ADD_HL(val) \
	opAux32.DW = HL + val;\
	F &= ~N_FLAG;\
	CHECK_H16(val);\
	CHECK_C_ADD16(val);\
	HL=opAux32.W.l

#define ADD_SP(val) \
	opAux32.DW = SP + val;\
	F = 0;\
	CHECK_H16(val);\
	CHECK_C_ADD16(val);\
	SP=opAux32.W.l

#define LD_HLSP(val) \
	opAux32.DW = SP + val;\
	F = 0;\
	CHECK_H16(val);\
	CHECK_C_ADD16(val);\
	HL=opAux32.W.l

#define RLC(val) \
		F=0;\
		val = (val << 1) | (val >> 7);\
		CHECK_Z(val)\
		F = (val & 0x1) << 4

#define RL(val) \
		F=0;\
		opAux.Byte.l=val;\
		opAux.Byte.h=(F&C_FLAG)>>4;\
		opAux.Word = ((opAux.Word << 1)|(opAux.Word >> 8)) & 0x1FF;\
		val=opAux.Byte.l;\
		F=opAux.Byte.h << 4;\
		F = (F & ~Z_FLAG) | (-(val==0) & Z_FLAG)

#define RRC(val)\
	    F=0;\
		F = (val & 0x1) << 4;\
		val = (val >> 1) | (val << 7);\
		F = (F & ~Z_FLAG) | (-(val==0) & Z_FLAG)

#define RR(val)\
	    F=0;\
	    opAux.Word =  (val << 1) | ((F & C_FLAG) >> 4);\
		opAux.Word = ((opAux.Word >> 1) | (opAux.Word << 8)) & 0x1FF; \
		F = (opAux.Word & 0x1) << 4 ; \
		val = opAux.Word >> 1; \
		F = (F & ~Z_FLAG) | (-(val==0) & Z_FLAG)

#define SLA(val)\
	    F=(val&0x80)>>3;\
	    val = val << 1;\
		F = (F & ~Z_FLAG) | (-(val==0) & Z_FLAG)

#define SRA(val)\
	    F=(val&0x1)<<4;\
	    val = (val & 0x80 ) |  (val >> 1);\
		F = (F & ~Z_FLAG) | (-(val==0) & Z_FLAG)

#define SRL(val)\
	    F=(val&0x1)<<4;\
	    val = val >> 1;\
		F = (F & ~Z_FLAG) | (-(val==0) & Z_FLAG)

#define SWAP(val)\
	F = 0;\
	val = (val >>4) | (val << 4);\
	F = (F & ~Z_FLAG) | (-(val==0) & Z_FLAG)

#define BIT(n,val)\
	if(((0x1 << n) & val)==0)\
		F |= Z_FLAG;\
	else \
		F &= ~Z_FLAG; \
	F &= ~N_FLAG;\
	F |= H_FLAG

#define SET(n,val)\
	val |= (0x1 << n)

#define RES(n,val)\
	val &= ~(0x1 << n)



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
				#ifndef BIG_ENDIAN
				uint8_t l,h; /* ...in little-endian architecture */
				#else
				uint8_t h, l; /* ...in big-endian architecture */
				#endif
			} Byte;
			uint16_t Word;
	} reg16bit;

	typedef union
	{
		struct
		{
			#ifndef BIG_ENDIAN
			uint16_t l,h; /* ...in little-endian architecture */
			#else
			uint16_t h, l; /* ...in big-endian architecture */
			#endif
		} W;
		uint32_t DW;
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
	/*Z80 getcontext(); //      -> returns the CPU context
	 void setcontext(Z80 * cpu); //   -> sets the CPU context*/
	void interruptZ80(); //      -> sends an interrupt signal
	void printStatusZ80();

#ifdef __cplusplus
}
#endif

#endif /* Z80_H_ */
