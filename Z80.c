/*
 * Z80.c
 *
 *  Created on: 2010/06/17
 *      Author: brNX
 */

#include "Z80.h"

Z80 gbcpu;

void resetZ80()
{
	gbcpu.pause = 1;
	gbcpu.halt = 0;
	A = 0x01; // 0x01->GB/SGB; 0xFF->GBP; 0x11->GBC
	F = 0xB0; // F=0xB0->Z1 N0 H1 C1
	BC = 0x0013;
	DE = 0x00D8;
	PC = 0x0100;
	SP = 0xFFFE;
	HL = 0x014D;
	gbcpu.cyclecounter = 0;
	SP = 0xFFFE;
}

int execute(int ncycles)
{
	int Counter = ncycles;
	uint8_t pc = PC;

	for (;;)
	{
		uint8_t OpCode = readOpcode(pc++);
		Counter -= Cycles[OpCode];
		gbcpu.cyclecounter += Cycles[OpCode];

		switch (OpCode)
		{

		/*nop*/
		case 0x00:
		case 0x40:
		case 0x49:
		case 0x52: // LD D,D
		case 0x5B: // LD E,E
		case 0x64: // LD H,H
		case 0x6D: // LD L,L
		case 0x7F:
			break;

		/*LD 8 bit*/
		case 0x41://LD B,C
			B=C;
			break;
		case 0x42://LD B,D
			B=D;
			break;
		case 0x43://LD B,E
			B=E;
			break;
		case 0x44://LD B,H
			B=H;
			break;
		case 0x45://LD B,L
			B=L;
			break;
		case 0x47://LD B,A
			B=A;
			break;
		case 0x48: // LD C,B
			C=B;
			break;
		case 0x4A: // LD C,D
			C=D;
			break;
		case 0x4B: // LD C,E
			C=E;
			break;
		case 0x4C: // LD C,H
			C=H;
			break;
		case 0x4D: // LD C,L
			C=L;
			break;
		case 0x4E: // LD C,(HL)
			break;
		case 0x4F: // LD C,A
			C=A;
			break;
		case 0x50: // LD D,B
			D=B;
			break;
		case 0x51: // LD D,C
			D=C;
			break;
		case 0x53: // LD D,E
			D=E;
			break;
		case 0x54: // LD D,H
			D=H;
			break;
		case 0x55: // LD D,L
			D=L;
			break;
		case 0x56: // LD D,(HL)
			break;
		case 0x57: // LD D,A
			D=A;
			break;
		case 0x58: // LD E,B
			E=B;
			break;
		case 0x59: // LD E,C
			E=C;
			break;
		case 0x5A: // LD E,D
			E=D;
			break;
		case 0x5C: // LD E,H
			E=H;
			break;
		case 0x5D: // LD E,L
			E=L;
			break;
		case 0x5E: // LD E,(HL)
			break;
		case 0x5F: // LD E,A
			E=A;
			break;
		case 0x60: // LD H,B
			H=B;
			break;
		case 0x61: // LD H,C
			H=C;
			break;
		case 0x62: // LD H,D
			H=D;
			break;
		case 0x63: // LD H,E
			H=E;
			break;
		case 0x65: // LD H,L
			H=L;
			break;
		case 0x66: // LD H,(HL)
			break;
		case 0x67: // LD H,A
			H=A;
			break;
		case 0x68: // LD L,B
			L=B;
			break;
		case 0x69: // LD L,C
			L=C;
			break;
		case 0x6A: // LD L,D
			L=D;
			break;
		case 0x6B: // LD L,E
			L=E;
			break;
		case 0x6C: //LD L,H
			L=H;
			break;
		case 0x78://LD A,B
			A=B;
			break;
		case 0x79://LD A,C
			A=C;
			break;
		case 0x7A://LD A,D
			A=D;
			break;
		case 0x7B://LD A,E
			A=E;
			break;
		case 0x7C://LD A,H
			A=H;
			break;
		default:
			break;
		}

		if (Counter <= 0)
		{
			//Check for interrupts and do other
			// cyclic tasks here

			Counter += ncycles;
			//if(ExitRequired) break;
		}
	}
	return 0;
}

/*Z80 getcontext(){
 return NULL;
 }*/

/*void setcontext(Z80 * cpu){

 }*/

void interruptZ80()
{

}

inline uint8_t readOpcode(uint16_t address)
{
	//TODO: para ja
	return 0;
}
