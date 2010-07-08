/*
 * Z80.c
 *
 *  Created on: 2010/06/17
 *      Author: brNX
 */

#define DEBUG
#include "Z80.h"
#include "memory.h"

#include "lookuptables.h"
#include <stdint.h>
#include <stdio.h>

#ifdef DEBUG
#include "debugcounters.h"
#endif

Z80 gbcpu;


void resetZ80()
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
}

int execute(int ncycles)
{
    int Counter = ncycles;
    uint16_t pc = PC;

    //emulation loop
    for (;;)
    {
        //variaveis temporarias para operacoes(não existe no processador)
        reg16bit opAux;
        uint16_t address;
        uint8_t tempbyte;
        int8_t signedtempbyte;
        reg32bit opAux32;

#ifdef DEBUG
        printStatusZ80();
        printf("**************************\n");
        printf("pc:%04x\n",pc);
        printf("**************************\n");
#endif

	uint8_t OpCode = readMem(pc++);
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


void execOpcode(uint8_t OpCode){


        //variaveis temporarias para operacoes(não existe no processador)
        reg16bit opAux;
        uint16_t address;
        uint8_t tempbyte;
        int8_t signedtempbyte;
        reg32bit opAux32;
        int Counter = 0;
        uint16_t pc = PC;

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
