/*
 * Z80.c
 *
 *  Created on: 2010/06/17
 *      Author: brNX
 */

#define DEBUG

#ifdef _MSC_VER
#include "no_sillywarnings.h"
#endif

#include "Z80.h"
#include "memory.h"

#include "lookuptables.h"
#include <stdio.h>

#ifdef DEBUG
#include "debugcounters.h"
#endif

Z80 gbcpu;


//is 0 ?
//if (val==0) F |= Z_FLAG; else F &= ~Z_FLAG;
#define CHECK_Z(val) \
        F = (F & ~Z_FLAG) | (-(val==0) & Z_FLAG);

//com lookup
#define CHECK_ZL(val)  F |= ZeroLookup[val]

//se houve halfcarry
#define CHECK_H(val) F |= (H_FLAG & ((A ^ (val) ^ opAux.Byte.l) << 1));

//se houve carry (0001 no opAux.Byte.h , logo 0001 << 4 = 0001 0000 = 0x10 = C_FLAG)
#define CHECK_C_ADD(val) F |= (opAux.Byte.h << 4);

//Set if no borrow (0001 no opAux.Byte.h , logo 0001 << 4 = 0001 0000 = 0x10 = C_FLAG)
#define CHECK_C_SUB(val) F |= ((uint8) (-(int8)opAux.Byte.h) << 4);

//se houve halfcarry 16bit
#define CHECK_H16(val) \
        F |= (H_FLAG & ((HL ^ (val) ^ opAux32.W.l) >> 7));

//se houve carry (0001 no opAux32.W.h , logo 0001 << 4 = 0001 0000 = 0x10 = C_FLAG) 16bit
#define CHECK_C_ADD16(val) F |= (uint8)(opAux32.W.h << 4);


#define ADD_A(val) \
        opAux.Word = A + val;\
        F=0;\
        CHECK_ZL(opAux.Byte.l);\
        CHECK_H(val)\
        CHECK_C_ADD(val)\
        A=opAux.Byte.l

#define ADC_A(val) \
        opAux.Word =  A + val + ((F & C_FLAG) >> 4) ;\
        F=0;\
        CHECK_ZL(opAux.Byte.l);\
        CHECK_H(val)\
        CHECK_C_ADD(val)\
        A=opAux.Byte.l

#define SUB_A(val) \
        opAux.Word = A - val;\
        F=N_FLAG;\
        CHECK_ZL(opAux.Byte.l);\
        CHECK_H(val)\
        CHECK_C_SUB(val)\
        A=opAux.Byte.l

#define SBC_A(val) \
        opAux.Word =  A - val - ((F & C_FLAG) >> 4) ;\
        F=N_FLAG;\
        CHECK_ZL(opAux.Byte.l);\
        CHECK_H(val)\
        CHECK_C_SUB(val)\
        A=opAux.Byte.l

#define AND_A(val) \
        A &= val ;\
        F = 0x20; \
        CHECK_ZL(A)

#define XOR_A(val) \
        A ^= val ;\
        F = 0;\
        CHECK_ZL(A)

#define OR_A(val) \
        A |= val ;\
        F = 0;\
        CHECK_ZL(A)

#define CP_A(val) \
        opAux.Word =  A - val;\
        F=N_FLAG;\
        CHECK_ZL(opAux.Byte.l);\
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
        F =(F&Z_FLAG);\
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
        CHECK_ZL(val);\
        F = (val & 0x1) << 4

#define RL(val) \
        F=0;\
        opAux.Byte.l=val;\
        opAux.Byte.h=(F&C_FLAG)>>4;\
        opAux.Word = ((opAux.Word << 1)|(opAux.Word >> 8)) & 0x1FF;\
        val=opAux.Byte.l;\
        F=opAux.Byte.h << 4;\
        CHECK_ZL(val)

#define RRC(val)\
         F=0;\
         F = (val & 0x1) << 4;\
         val = (val >> 1) | (val << 7);\
         CHECK_ZL(val)

#define RR(val)\
        F=0;\
        opAux.Word =  (val << 1) | ((F & C_FLAG) >> 4);\
        opAux.Word = ((opAux.Word >> 1) | (opAux.Word << 8)) & 0x1FF; \
        F = (opAux.Word & 0x1) << 4 ; \
        val = opAux.Word >> 1; \
        CHECK_ZL(val)

#define SLA(val)\
        F=(val&0x80)>>3;\
        val = val << 1;\
        CHECK_ZL(val)

#define SRA(val)\
         F=(val&0x1)<<4;\
         val = (val & 0x80 ) |  (val >> 1);\
         CHECK_ZL(val)

#define SRL(val)\
        F=(val&0x1)<<4;\
        val = val >> 1;\
        CHECK_ZL(val)

#define SWAP(val)\
        F = 0;\
        val = (val >>4) | (val << 4);\
        CHECK_ZL(val)

#define BIT(n,val)\
        F=(F&C_FLAG) | H_FLAG;\
        F = (F & ~Z_FLAG) | (-(((0x1 << n) & val)==0) & Z_FLAG)

#define SET(n,val)\
        val |= (0x1 << n)

#define RES(n,val)\
        val &= ~(0x1 << n)



void resetZ80(Memory * mem)
{
    gbcpu.pause = 1;
    gbcpu.halt = 0;
    A = 0x01; //0x01->GB/SGB; 0xFF->GBP; 0x11->GBC
    F = 0xB0; //F=0xB0->Z1 N0 H1 C1
    BC = 0x0013;
    DE = 0x00D8;
    PC = 0x0100;
    SP = 0xFFFE;
    HL = 0x014D;
    gbcpu.cyclecounter = 0;
    SP = 0xFFFE;
    //todo: verificar
    gbcpu.ime=1;
    gbcpu.mem=mem;
}

int execute(int ncycles)
{
    int Counter = ncycles;
    uint16 pc = PC;

    //emulation loop
    for (;;)
    {
        //variaveis temporarias para operacoes(não existe no processador)
        reg16bit opAux;
        uint16 address;
        uint8 tempbyte;
        int8 signedtempbyte;
        reg32bit opAux32;
        uint8 OpCode;

#ifdef DEBUG
        printStatusZ80();
        printf("**************************\n");
        printf("pc:%04x\n",pc);
        printf("**************************\n");
#endif

        OpCode = readOpcode(pc++, gbcpu.mem);
	Counter -= Cycles[OpCode];
	gbcpu.cyclecounter += Cycles[OpCode];

#ifdef DEBUG
	printf("opcode:%02x ",OpCode);
	CyclesCount[OpCode]++;
#endif

	switch (OpCode)
	{

        #include "Opcodes.h"

        default:
            break;
        }

#ifdef DEBUG
	printf("Press <ENTER> to Continue\n\n");
	for(;;){
	    char c=getchar();
	    if (c == '\n')
		break;
	}
#endif

	if (Counter <= 0)
	{
	    //Check for interrupts and do other
	    //cyclic tasks here

	    Counter += ncycles;
	    break;
	}
    }
    return 0;
}


void execOpcode(uint8 OpCode){


        //variaveis temporarias para operacoes(não existe no processador)
        reg16bit opAux;
        uint16 address;
        uint8 tempbyte;
        int8 signedtempbyte;
        reg32bit opAux32;
        int Counter = 0;
        uint16 pc = PC;

	switch (OpCode)
	{

	#include "Opcodes.h"

	default:
		break;
	}

}

void interruptZ80()
{

}

void printStatusZ80(){
    printf("*******Z80 Status*********\n");
    printf("ZF:%d NF:%d HF:%d CF:%d\n",(F>>7),(F&N_FLAG)>>6,(F&H_FLAG)>>5,(F&C_FLAG)>>4);
    printf("AF:%04x BC:%04x DE:%04x HL:%04x PC:%04x SP:%04x\n",AF,BC,DE,HL,PC,SP);
    printf("IME: %d\n",IME);
    printf("**************************\n");

}
