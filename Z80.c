/*
 * Z80.c
 *
 *  Created on: 2010/06/17
 *      Author: brNX
 */

#include "Z80.h"
#include "memory.h"
#include <stdint.h>

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
		uint16_t address;
		uint8_t OpCode = readMem(pc++);
		Counter -= Cycles[OpCode];
		gbcpu.cyclecounter += Cycles[OpCode];

		switch (OpCode)
		{

		/*Ordem opcodes do livro "Z80 Family CPU User Manual" */

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

		/*LD r,r'*/
		case 0x41://LD B,C
			B = C;
			break;
		case 0x42://LD B,D
			B = D;
			break;
		case 0x43://LD B,E
			B = E;
			break;
		case 0x44://LD B,H
			B = H;
			break;
		case 0x45://LD B,L
			B = L;
			break;
		case 0x47://LD B,A
			B = A;
			break;
		case 0x48: // LD C,B
			C = B;
			break;
		case 0x4A: // LD C,D
			C = D;
			break;
		case 0x4B: // LD C,E
			C = E;
			break;
		case 0x4C: // LD C,H
			C = H;
			break;
		case 0x4D: // LD C,L
			C = L;
			break;
		case 0x4F: // LD C,A
			C = A;
			break;
		case 0x50: // LD D,B
			D = B;
			break;
		case 0x51: // LD D,C
			D = C;
			break;
		case 0x53: // LD D,E
			D = E;
			break;
		case 0x54: // LD D,H
			D = H;
			break;
		case 0x55: // LD D,L
			D = L;
			break;
		case 0x57: // LD D,A
			D = A;
			break;
		case 0x58: // LD E,B
			E = B;
			break;
		case 0x59: // LD E,C
			E = C;
			break;
		case 0x5A: // LD E,D
			E = D;
			break;
		case 0x5C: // LD E,H
			E = H;
			break;
		case 0x5D: // LD E,L
			E = L;
			break;
		case 0x5F: // LD E,A
			E = A;
			break;
		case 0x60: // LD H,B
			H = B;
			break;
		case 0x61: // LD H,C
			H = C;
			break;
		case 0x62: // LD H,D
			H = D;
			break;
		case 0x63: // LD H,E
			H = E;
			break;
		case 0x65: // LD H,L
			H = L;
			break;
		case 0x67: // LD H,A
			H = A;
			break;
		case 0x68: // LD L,B
			L = B;
			break;
		case 0x69: // LD L,C
			L = C;
			break;
		case 0x6A: // LD L,D
			L = D;
			break;
		case 0x6B: // LD L,E
			L = E;
			break;
		case 0x6C: //LD L,H
			L = H;
			break;
		case 0x78://LD A,B
			A = B;
			break;
		case 0x79://LD A,C
			A = C;
			break;
		case 0x7A://LD A,D
			A = D;
			break;
		case 0x7B://LD A,E
			A = E;
			break;
		case 0x7C://LD A,H
			A = H;
			break;
		case 0x7D://LD A,L
			A = L;
			break;

		/*LD r,n*/
		case 0x06: //LD B,n
			B = readMem(pc++);
			break;
		case 0x0E: //LD C,n
			C = readMem(pc++);
			break;
		case 0x16: //LD D,n
			D = readMem(pc++);
			break;
		case 0x1E: //LD E,n
			E = readMem(pc++);
			break;
		case 0x26: //LD H,n
			H = readMem(pc++);
			break;
		case 0x2E: //LD L,n
			L = readMem(pc++);
			break;
		case 0x3E: //LD A,n
			A = readMem(pc++);
			break;

		/*LD r,(HL)*/
		case 0x46: // LD B,(HL)
			B = readMem(HL);
			break;
		case 0x4E: // LD C,(HL)
			C = readMem(HL);
			break;
		case 0x56: // LD D,(HL)
			D = readMem(HL);
			break;
		case 0x5E: // LD E,(HL)
			E = readMem(HL);
			break;
		case 0x66: // LD H,(HL)
			H = readMem(HL);
			break;
		case 0x6E: // LD L,(HL)
			L = readMem(HL);
			break;
		case 0x7E: // LD A,(HL)
			A = readMem(HL);
			break;

		/*gameboy sem instrucoes DD e FD (registo IX e IY) */

		/*LD (HL),r*/
		case 0x70: //LD (HL),B
			writeMem(HL, B);
			break;
		case 0x71://LD (HL),C
			writeMem(HL, C);
			break;
		case 0x72://LD (HL),D
			writeMem(HL, D);
			break;
		case 0x73://LD (HL),E
			writeMem(HL, E);
			break;
		case 0x74://LD (HL),H
			writeMem(HL, H);
			break;
		case 0x75://LD (HL),L
			writeMem(HL, L);
			break;
		case 0x77://LD (HL),A
			writeMem(HL, A);
			break;

		/*gameboy sem instrucoes DD e FD (registo IX e IY) */

		/*LD (HL), n*/
		case 0x36:
			writeMem(HL, readMem(pc++));
			break;

		/*gameboy sem instrucoes DD e FD (registo IX e IY) */

		/*LD A,(BC)*/
		case 0x0A:
			A = readMem(BC);
			break;
		/*LD A,(DE)*/
		case 0x1A:
			A = readMem(DE);
			break;

		/*LD(BC),A*/
		case 0x02:
			writeMem(BC, A);
			break;
		/*LD(DE),A*/
		case 0x12:
			writeMem(DE, A);
			break;

		/*gameboy sem instrucoes DD e FD (registo IX e IY) */

		/*instrucoes especificas gameboy*/

		/*opcode      Z80             GMB    */
		/*3A      LD   A,(nn)     LDD  A,(HL)*/
		/*ldd  A,(HL)      3A         8 ---- A=(HL), HL=HL-1*/
		case 0x3A://LDD A,(HL)
			A = readMem(HL);
			HL--;
			break;

		/*opcode      Z80             GMB    */
		/*32      LD   (nn),A     LDD  (HL),A*/
		/*ldd  (HL),A      32         8 ---- (HL)=A, HL=HL-1*/
		case 0x32:
			writeMem(HL, A);
			HL--;
			break;

		/*opcode      Z80             GMB    */
		/* EA      JP   PE,nn      LD   (nn),A*/
		/*ld   (nn),A      EA        16 ----*/
		case 0xEA:
			address= readMem(pc++);
			address= address | (readMem(pc++)<<8);
			writeMem(address,A);
			break;

		/*opcode      Z80             GMB    */
		/*FA      JP   M,nn       LD   A,(nn)*/
		/*ld   A,(nn)      FA        16 ----*/
		case 0xFA:
			address= readMem(pc++);
			address=address | (readMem(pc++)<<8);
			A=readMem(address);
			break;

		/*opcode      Z80             GMB    */
		/*E0      RET  PO         LD   (FF00+n),A*/
		/*ld   (FF00+n),A  E0 nn     12 ---- write to io-port n (memory FF00+n)*/
		case 0xE0:
			writeMem(0xFF00+readMem(pc++),A);
			break;

		/*opcode      Z80             GMB    */
		/*F0      RET  P          LD   A,(FF00+n)*/
		/*ld   A,(FF00+n)  F0 nn     12 ---- read from io-port n (memory FF00+n)*/
		case 0xF0:
			A=readMem(0xFF00+readMem(pc++));
			break;

		/*opcode      Z80             GMB    */
		/*E2      JP   PO,nn      LD   (FF00+C),A*/
		/*ld   (FF00+C),A  E2         8 ---- write to io-port C (memory FF00+C)*/
		case 0xE2:
			writeMem(0xFF00+C,A);
			break;

		/*opcode      Z80             GMB    */
		/*F2      JP   P,nn       LD   A,(FF00+C*/
		/*ld   A,(FF00+C)  F2         8 ---- read from io-port C (memory FF00+C)*/
		case 0xF2:
			A=readMem(0xFF00+C);
			break;

		/*opcode      Z80             GMB    */
		/*22      LD   (nn),HL    LDI  (HL),A*/
		/*ldi  (HL),A      22         8 ---- (HL)=A, HL=HL+1*/
		case 0x22:
			writeMem(HL,A);
			HL++;
			break;

		/*opcode      Z80             GMB    */
		/*2A      LD   HL,(nn)    LDI  A,(HL)*/
		/*ldi  A,(HL)      2A         8 ---- A=(HL), HL=HL+1*/
		case 0x2A:
			A=readMem(HL);
			HL++;
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
