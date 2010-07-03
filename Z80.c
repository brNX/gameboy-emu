/*
 * Z80.c
 *
 *  Created on: 2010/06/17
 *      Author: brNX
 */

#include "Z80.h"
#include "memory.h"

#include "lookuptables.h"
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

		/**********************8 bit Loads*****************/

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

		/*LD (HL), n*/
		case 0x36:
			writeMem(HL, readMem(pc++));
			break;

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
			address = readMem(pc+1);
			address = address << 8;
			address = address | readMem(pc);
			writeMem(address,A);
			pc+=2;
			break;

		/*opcode      Z80             GMB    */
		/*FA      JP   M,nn       LD   A,(nn)*/
		/*ld   A,(nn)      FA        16 ----*/
		case 0xFA:
			address = readMem(pc+1);
			address = address << 8;
			address=address | readMem(pc);
			A=readMem(address);
			pc+=2;
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

		/**********************16 bit Loads*****************/

		/*LD rr,nn*/
		case 0x01 ://LD BC,nn
			C=readMem(pc++);
			B=readMem(pc++);
			break;
		case 0x11 : //LD DE,nn
			E=readMem(pc++);
			D=readMem(pc++);
			break;
		case 0x21: //LD HL,nn
			L=readMem(pc++);
			H=readMem(pc++);
			break;
		case 0x31: //LD SP,nn
			gbcpu.sp.Byte.l = readMem(pc++);
			gbcpu.sp.Byte.h = readMem(pc++);
			break;

		/*  ld   SP,HL */
		case 0xF9:
			SP=HL;
			break;
		/*LD (nn),SP */
		case 0x08:
			address = readMem(pc+1);
			address = address << 8;
			address=address | readMem(pc);
			writeMem(address,gbcpu.sp.Byte.l);
			writeMem(address+1,gbcpu.sp.Byte.h);
			break;

		/*push rr*/
		case 0xF5 ://PUSH AF
			writeMem(SP-2,F);
			writeMem(SP-1,A);
			SP-=2;
			break;
		case 0xC5 ://PUSH BC
			writeMem(SP-2,C);
			writeMem(SP-1,B);
			SP-=2;
			break;
		case 0xD5 ://PUSH DE
			writeMem(SP-2,E);
			writeMem(SP-1,D);
			SP-=2;
			break;
		case 0xE5 ://PUSH HL
			writeMem(SP-2,L);
			writeMem(SP-1,H);
			SP-=2;
			break;

		/*pop  rr*/
		case 0xF1: //POP AF
			F=readMem(SP);
			A=readMem(SP+1);
			SP+=2;
			break;
		case 0xC1: //POP BC
			C=readMem(SP);
			B=readMem(SP+1);
			SP+=2;
			break;
		case 0xD1: //POP DE
			E=readMem(SP);
			D=readMem(SP+1);
			SP+=2;
			break;
		case 0xE1: //POP HL
			L=readMem(SP);
			H=readMem(SP+1);
			SP+=2;
			break;

		/*****************GMB 8bit-Arithmetic/logical Commands*********************/

		/*add  A,r*/
		case 0x80: //ADD A,B
			ADD_A(B);
			break;
		case 0x81: // ADD A,C
			ADD_A(C);
			break;
		case 0x82: // ADD A,D
			ADD_A(D);
			break;
		case 0x83: // ADD A,E
			ADD_A(E);
			break;
		case 0x84: // ADD A,H
			ADD_A(H);
			break;
		case 0x85: // ADD A,L
			ADD_A(L);
			break;
		case 0x87: // ADD A,A
			ADD_A(A);
			break;

		/*add A,n*/
		case 0xC6:
			ADD_A(readMem(pc++));
			break;
		/*add A,(HL)*/
		case 0x86:
			ADD_A(readMem(HL));
			break;

		/*ADC A,r*/
		case 0x8F: //ADC A,A
			ADC_A(A);
			break;
		case 0x88: //ADC A,B
			ADC_A(B);
			break;
		case 0x89: //ADC A,C
			ADC_A(C);
			break;
		case 0x8A: //ADC A,D
			ADC_A(D);
			break;
		case 0x8B: //ADC A,E
			ADC_A(E);
			break;
		case 0x8C: //ADC A,H
			ADC_A(H);
			break;
		case 0x8D: //ADC A,L
			ADC_A(L);
			break;

		/*ADC A,n*/
		case 0xCE:
			ADC_A(readMem(pc++));
			break;

		/*ADC A,(HL)*/
		case 0x8E:
			ADC_A(readMem(HL));
			break;

		/*SUB A,r */
		case 0x90: //SUB B
			SUB_A(B);
			break;
		case 0x91: //SUB C
			SUB_A(C);
			break;
		case 0x92: //SUB D
			SUB_A(D);
			break;
		case 0x93: //SUB E
			SUB_A(E);
			break;
		case 0x94: //SUB H
			SUB_A(H);
			break;
		case 0x95: //SUB L
			SUB_A(L);
			break;
		case 0x97: //SUB A
			SUB_A(A);
			break;

		/*SUB A,(HL) */
		case 0x96:
			SUB_A(readMem(HL));
			break;
		/*SUB A,n*/
		case 0xD6:
			SUB_A(readMem(pc++));
			break;

		/*SBC A,r*/
		case 0x98: //SBC B
			SBC_A(B);
			break;
		case 0x99: //SBC C
			SBC_A(C);
			break;
		case 0x9A: //SBC D
			SBC_A(D);
			break;
		case 0x9B: //SBC E
			SBC_A(E);
			break;
		case 0x9C: //SBC H
			SBC_A(H);
			break;
		case 0x9D: //SBC L
			SBC_A(L);
			break;
		case 0x9F: //SBC A
			SBC_A(A);
			break;

		/*SBC A,(HL) */
		case 0x9E:
			SBC_A(readMem(HL));
			break;
		/*SBC A,n*/
		case 0xDE:
			SBC_A(readMem(pc++));
			break;

		/*AND A,r */
		case 0xA0: //AND B
			AND_A(B);
			break;
		case 0xA1: //AND C
			AND_A(C);
			break;
		case 0xA2: //AND D
			AND_A(D);
			break;
		case 0xA3: //AND E
			AND_A(E);
			break;
		case 0xA4: //AND H
			AND_A(H);
			break;
		case 0xA5: //AND L
			AND_A(L);
			break;
		case 0xA7: //AND A
			AND_A(A);
			break;

		/*AND A,(HL) */
		case 0xA6:
			AND_A(readMem(HL));
			break;
		/*AND A,n*/
		case 0xE6:
			AND_A(readMem(pc++));
			break;

		/*XOR A,r */
		case 0xA8: //XOR B
			XOR_A(B);
			break;
		case 0xA9: //XOR C
			XOR_A(C);
			break;
		case 0xAA: //XOR D
			XOR_A(D);
			break;
		case 0xAB: //XOR E
			XOR_A(E);
			break;
		case 0xAC: //XOR H
			XOR_A(H);
			break;
		case 0xAD: //XOR L
			XOR_A(L);
			break;
		case 0xAF: //XOR A
			XOR_A(A);
			break;

		/*XOR A,(HL) */
		case 0xAE:
			XOR_A(readMem(HL));
			break;
		/*XOR A,n*/
		case 0xEE:
			XOR_A(readMem(pc++));
			break;

		/*OR A,r */
		case 0xB0: //OR B
			OR_A(B);
			break;
		case 0xB1: //OR C
			OR_A(C);
			break;
		case 0xB2: //OR D
			OR_A(D);
			break;
		case 0xB3: //OR E
			OR_A(E);
			break;
		case 0xB4: //OR H
			OR_A(H);
			break;
		case 0xB5: //OR L
			OR_A(L);
			break;
		case 0xB7: //OR A
			OR_A(A);
			break;

		/*OR A,(HL) */
		case 0xB6:
			OR_A(readMem(HL));
			break;
		/*OR A,n*/
		case 0xF6:
			OR_A(readMem(pc++));
			break;

		/*CP A,r */
		case 0xB8: //CP B
			CP_A(B);
			break;
		case 0xB9: //CP C
			CP_A(C);
			break;
		case 0xBA: //CP D
			CP_A(D);
			break;
		case 0xBB: //CP E
			CP_A(E);
			break;
		case 0xBC: //CP H
			CP_A(H);
			break;
		case 0xBD: //CP L
			CP_A(L);
			break;
		case 0xBF: //CP A
			CP_A(A);
			break;

		/*CP A,(HL) */
		case 0xBE:
			CP_A(readMem(HL));
			break;
		/*CP A,n*/
		case 0xFE:
			CP_A(readMem(pc++));
			break;

		/*INC r */
		case 0x04: //INC B
			INC(B);
			break;
		case 0x0C: //INC C
			INC(C);
			break;
		case 0x14: //INC D
			INC(D);
			break;
		case 0x1C: //INC E
			INC(E);
			break;
		case 0x24: //INC H
			INC(H);
			break;
		case 0x2C: //INC L
			INC(L);
			break;
		case 0x3C: //INC A
			INC(A);
			break;

		/*INC (HL) */
		case 0x34:
			tempbyte=readMem(HL);
			INC(tempbyte);
			writeMem(HL,tempbyte);
			break;

		/*DEC r */
		case 0x05: //DEC B
			DEC(B);
			break;
		case 0x0D: //DEC C
			DEC(C);
			break;
		case 0x15: //DEC D
			DEC(D);
			break;
		case 0x1D: //DEC E
			DEC(E);
			break;
		case 0x25: //DEC H
			DEC(H);
			break;
		case 0x2D: //DEC L
			DEC(L);
			break;
		case 0x3D: //DEC A
			DEC(A);
			break;

		/*DEC (HL) */
		case 0x35:
			tempbyte=readMem(HL);
			DEC(tempbyte);
			writeMem(HL,tempbyte);
			break;

		/*DAA */
		case 0x27:
			//TODO: verificar valor
			opAux.Byte.h = (F & 0x70) >> 4;
			opAux.Byte.l = A;
			AF= DAALookup[opAux.Word];
			break;
		/*CPL*/
		case 0x2F:
			A = A ^ 0xFF;
			F |= H_FLAG;
			F |= N_FLAG;
			break;

	 /*****************GMB 16bit-Arithmetic/logical Commands*********************/

		/*ADD HL,rr*/
		case 0x09: // ADD HL,BC
			ADD_HL(BC);
			break;
		case 0x19: // ADD HL,DE
			ADD_HL(DE);
			break;
		case 0x29: // ADD HL,HL
			ADD_HL(HL);
			break;
		case 0x39: // ADD HL,SP
			ADD_HL(SP);
			break;

		/*ADD SP,n */
		//TODO: por verificar (signed byte)
		case 0xE8:
			signedtempbyte = readMem(pc++);
			ADD_SP(signedtempbyte);
			break;

		/*INC rr*/
		case 0x03: //INC BC
			BC+=1;
			break;
		case 0x13: //INC DE
			DE+=1;
			break;
		case 0x23: //INC HL
			HL+=1;
			break;
		case 0x33: //INC SP
			SP+=1;
			break;

		/*DEC rr*/
		case 0x0B: //DEC BC
			BC-=1;
			break;
		case 0x1B: //DEC DE
			DE-=1;
			break;
		case 0x2B: //DEC HL
			HL-=1;
			break;
		case 0x3B: //DEC SP
			SP-=1;
			break;

		/*LD HL,SP+n*/
		//TODO: por verificar (signed byte)
		case 0xF8:
			signedtempbyte=readMem(pc++);
			LD_HLSP(signedtempbyte);
			break;

		/*****************GMB Rotate- , Shift- and Singlebit Operation Commands*********************/

		case 0x07: //RLCA
			F = (A & 0x80) >> 3;
			A = (A << 1) | (A >> 7);
			break;

		case 0x17: //RLA
			opAux.Byte.l=A;
			opAux.Byte.h=(F&C_FLAG)>>4;
			opAux.Word = ((opAux.Word << 1)|(opAux.Word >> 8)) & 0x1FF;
			A=opAux.Byte.l;
			F=opAux.Byte.h << 4;
			break;

		case 0x0F: //RRCA
			F = (A & 0x1) << 4;
			A = (A >> 1) | (A << 7);
			break;

		case 0x1F: //RRA
			opAux.Word =  (A << 1) | ((F & C_FLAG) >> 4);
			opAux.Word = ((opAux.Word >> 1) | (opAux.Word << 8)) & 0x1FF;
			F = (opAux.Word & 0x1) << 4 ;
			A = opAux.Word >> 1;
			break;

		/*rotate and shifts CB Opcodes */
		case 0xCB:
			OpCode= readMem(pc++);
                        Counter -= CyclesCB[OpCode];
                        gbcpu.cyclecounter += CyclesCB[OpCode];
			switch (OpCode) {

				/*RLC  r*/
				case 0x00: //RLC B
					RLC(B);
					break;

				case 0x01://RLC C
					RLC(C);
					break;

				case 0x02://RLC D
					RLC(D);
					break;

				case 0x03://RLC E
					RLC(E);
					break;

				case 0x04://RLC H
					RLC(H);
					break;

				case 0x05://RLC L
					RLC (L);
					break;

				case 0x06://RLC (HL)
					tempbyte=readMem(HL);
					RLC(tempbyte);
					writeMem(HL,tempbyte);
					break;

				case 0x07: //RLC A
					RLC (A);
					break;

				/*RL   r*/
				case 0x10: //RL B
					RL(B);
					break;

				case 0x11://RL C
					RL(C);
					break;

				case 0x12://RL D
					RL(D);
					break;

				case 0x13://RL E
					RL(E);
					break;

				case 0x14://RL H
					RL(H);
					break;

				case 0x15://RL L
					RL(L);
					break;

				case 0x16://RL (HL)
					tempbyte=readMem(HL);
					RL(tempbyte);
					writeMem(HL,tempbyte);
					break;

				case 0x17://RL A
					RL(A);
					break;

			   /*RRC r*/
				case 0x08: //RRC B
					RRC(B);
					break;

				case 0x09://RRC C
					RRC(C);
					break;

				case 0x0A://RRC D
					RRC(D);
					break;

				case 0x0B://RRC E
					RRC(E);
					break;

				case 0x0C://RRC H
					RRC(H);
					break;

				case 0x0D://RRC L
					RRC (L);
					break;

				case 0x0E://RRC (HL)
					tempbyte=readMem(HL);
					RRC(tempbyte);
					writeMem(HL,tempbyte);
					break;

				case 0x0F: //RRC A
					RRC (A);
					break;


			   /*RR r*/
				case 0x18: //RR B
					RR(B);
					break;

				case 0x19://RR C
					RR(C);
					break;

				case 0x1A://RR D
					RR(D);
					break;

				case 0x1B://RR E
					RR(E);
					break;

				case 0x1C://RR H
					RR(H);
					break;

				case 0x1D://RR L
					RR (L);
					break;

				case 0x1E://RR (HL)
					tempbyte=readMem(HL);
					RR(tempbyte);
					writeMem(HL,tempbyte);
					break;

				case 0x1F: //RR A
					RR (A);
					break;

			   /*SLA r*/
				case 0x20: //SLA B
					SLA(B);
					break;

				case 0x21://SLA C
					SLA(C);
					break;

				case 0x22://SLA D
					SLA(D);
					break;

				case 0x23://SLA E
					SLA(E);
					break;

				case 0x24://SLA H
					SLA(H);
					break;

				case 0x25://SLA L
					SLA (L);
					break;

				case 0x26://SLA (HL)
					tempbyte=readMem(HL);
					SLA(tempbyte);
					writeMem(HL,tempbyte);
					break;

				case 0x27: //SLA A
					SLA (A);
					break;

				/*SRA r*/
				case 0x28: //SRA B
					SRA(B);
					break;

				case 0x29://SRA C
					SRA(C);
					break;

				case 0x2A://SRA D
					SRA(D);
					break;

				case 0x2B://SRA E
					SRA(E);
					break;

				case 0x2C://SRA H
					SRA(H);
					break;

				case 0x2D://SRA L
					SRA (L);
					break;

				case 0x2E://SRA (HL)
					tempbyte=readMem(HL);
					SRA(tempbyte);
					writeMem(HL,tempbyte);
					break;

				case 0x2F: //SRA A
					SRA (A);
					break;

				/*SRL r*/
				case 0x38: //SRL B
					SRL(B);
					break;

				case 0x39://SRL C
					SRL(C);
					break;

				case 0x3A://SRL D
					SRL(D);
					break;

				case 0x3B://SRL E
					SRL(E);
					break;

				case 0x3C://SRL H
					SRL(H);
					break;

				case 0x3D://SRL L
					SRL (L);
					break;

				case 0x3E://SRL (HL)
					tempbyte=readMem(HL);
					SRL(tempbyte);
					writeMem(HL,tempbyte);
					break;

				case 0x3F: //SRL A
					SRL (A);
					break;

				/*SWAP r*/
				case 0x30: //SWAP B
					SWAP(B);
					break;

				case 0x31://SWAP C
					SWAP(C);
					break;

				case 0x32://SWAP D
					SWAP(D);
					break;

				case 0x33://SWAP E
					SWAP(E);
					break;

				case 0x34://SWAP H
					SWAP(H);
					break;

				case 0x35://SWAP L
					SWAP (L);
					break;

				case 0x36://SWAP (HL)
					tempbyte=readMem(HL);
					SWAP(tempbyte);
					writeMem(HL,tempbyte);
					break;

				case 0x37: //SWAP A
					SWAP (A);
					break;

				/***bit opcodes**/

				/*BIT b,r*/
				case 0x40: //BIT 0,B
  					BIT(0,B);
					break;
				case 0x41: //BIT 0,C
  					BIT(0,C);
					break;
				case 0x42: // BIT 0,D
  					BIT(0,D);
					break;
				case 0x43: // BIT 0,E
  					BIT(0,E);
					break;
				case 0x44: // BIT 0,H
  					BIT(0,H);
					break;
				case 0x45: // BIT 0,L
  					BIT(0,L);
					break;
				case 0x47: // BIT 0,A
  					BIT(0,A);
					break;
				case 0x48: // BIT 1,B
  					BIT(1,B);
					break;
				case 0x49: // BIT 1,C
  					BIT(1,C);
					break;
				case 0x4A: // BIT 1,D
  					BIT(1,D);
					break;
				case 0x4B: // BIT 1,E
  					BIT(1,E);
					break;
				case 0x4C: // BIT 1,H
  					BIT(1,H);
					break;
				case 0x4D: // BIT 1,L
  					BIT(1,L);
					break;
				case 0x4F: // BIT 1,A
  					BIT(1,A);
					break;
				case 0x50: // BIT 2,B
  					BIT(2,B);
					break;
				case 0x51: // BIT 2,C
  					BIT(2,C);
					break;
				case 0x52: // BIT 2,D
  					BIT(2,D);
					break;
				case 0x53: // BIT 2,E
  					BIT(2,E);
					break;
				case 0x54: // BIT 2,H
  					BIT(2,H);
					break;
				case 0x55: // BIT 2,L
  					BIT(2,L);
					break;
				case 0x57: // BIT 2,A
  					BIT(2,A);
					break;
				case 0x58: // BIT 3,B
  					BIT(3,B);
					break;
				case 0x59: // BIT 3,C
  					BIT(3,C);
					break;
				case 0x5A: // BIT 3,D
  					BIT(3,D);
					break;
				case 0x5B: // BIT 3,E
  					BIT(3,E);
					break;
				case 0x5C: // BIT 3,H
  					BIT(3,H);
					break;
				case 0x5D: // BIT 3,L
  					BIT(3,L);
					break;
				case 0x5F: // BIT 3,A
  					BIT(3,A);
					break;
				case 0x60: // BIT 4,B
  					BIT(4,B);
					break;
				case 0x61: // BIT 4,C
  					BIT(4,C);
					break;
				case 0x62: // BIT 4,D
  					BIT(4,D);
					break;
				case 0x63: // BIT 4,E
  					BIT(4,E);
					break;
				case 0x64: // BIT 4,H
  					BIT(4,H);
					break;
				case 0x65: // BIT 4,L
  					BIT(4,L);
					break;
				case 0x67: // BIT 4,A
  					BIT(4,A);
					break;
				case 0x68: // BIT 5,B
  					BIT(5,B);
					break;
				case 0x69: // BIT 5,C
  					BIT(5,C);
					break;
				case 0x6A: // BIT 5,D
  					BIT(5,D);
					break;
				case 0x6B: // BIT 5,E
  					BIT(5,E);
					break;
				case 0x6C: // BIT 5,H
  					BIT(5,H);
					break;
				case 0x6D: // BIT 5,L
  					BIT(5,L);
					break;
				case 0x6F: // BIT 5,A
  					BIT(5,A);
					break;
				case 0x70: // BIT 6,B
  					BIT(6,B);
					break;
				case 0x71: // BIT 6,C
  					BIT(6,C);
					break;
				case 0x72: // BIT 6,D
  					BIT(6,D);
					break;
				case 0x73: // BIT 6,E
  					BIT(6,E);
					break;
				case 0x74: // BIT 6,H
  					BIT(6,H);
					break;
				case 0x75: // BIT 6,L
  					BIT(6,L);
					break;
				case 0x77: // BIT 6,A
  					BIT(6,A);
					break;
				case 0x78: // BIT 7,B
  					BIT(7,B);
					break;
				case 0x79: // BIT 7,C
  					BIT(7,C);
					break;
				case 0x7A: // BIT 7,D
  					BIT(7,D);
					break;
				case 0x7B: // BIT 7,E
  					BIT(7,E);
					break;
				case 0x7C: // BIT 7,H
  					BIT(7,H);
					break;
				case 0x7D: // BIT 7,L
  					BIT(7,L);
					break;
				case 0x7F: // BIT 7,A
					BIT(7,A);
					break;

				case 0x46: // BIT 0,(HL)
  					tempbyte=readMem(HL);
					BIT(0,tempbyte);
					writeMem(HL,tempbyte);
					break;
				case 0x4E: // BIT 1,(HL)
  					tempbyte=readMem(HL);
					BIT(1,tempbyte);
					writeMem(HL,tempbyte);
					break;
				case 0x56: // BIT 2,(HL)
  					tempbyte=readMem(HL);
					BIT(2,tempbyte);
					writeMem(HL,tempbyte);
					break;
				case 0x5E: // BIT 3,(HL)
  					tempbyte=readMem(HL);
					BIT(3,tempbyte);
					writeMem(HL,tempbyte);
					break;
				case 0x66: // BIT 4,(HL)
  					tempbyte=readMem(HL);
					BIT(4,tempbyte);
					writeMem(HL,tempbyte);
					break;
				case 0x6E: // BIT 5,(HL)
  					tempbyte=readMem(HL);
					BIT(5,tempbyte);
					writeMem(HL,tempbyte);
					break;
				case 0x76: // BIT 6,(HL)
  					tempbyte=readMem(HL);
					BIT(6,tempbyte);
					writeMem(HL,tempbyte);
					break;
				case 0x7E: // BIT 7,(HL)
  					tempbyte=readMem(HL);
					BIT(7,tempbyte);
					writeMem(HL,tempbyte);
					break;

				/*SET b,r */
				case  0xC0:// SET 0,B
  					SET(0,B);
					break;
				case  0xC1:// SET 0,C
  					SET(0,C);
					break;
				case  0xC2:// SET 0,D
  					SET(0,D);
					break;
				case  0xC3:// SET 0,E
  					SET(0,E);
					break;
				case  0xC4:// SET 0,H
  					SET(0,H);
					break;
				case  0xC5:// SET 0,L
  					SET(0,L);
					break;
				case  0xC6:// SET 0,(HL)
  					tempbyte=readMem(HL);
					SET(0,tempbyte);
					writeMem(HL,tempbyte);
					break;
				case  0xC7:// SET 0,A
  					SET(0,A);
					break;
				case  0xC8:// SET 1,B
  					SET(1,B);
					break;
				case  0xC9:// SET 1,C
  					SET(1,C);
					break;
				case  0xCA:// SET 1,D
  					SET(1,D);
					break;
				case  0xCB:// SET 1,E
  					SET(1,E);
					break;
				case  0xCC:// SET 1,H
  					SET(1,H);
					break;
				case  0xCD:// SET 1,L
  					SET(1,L);
					break;
				case  0xCE:// SET 1,(HL)
  					tempbyte=readMem(HL);
					SET(1,tempbyte);
					writeMem(HL,tempbyte);
					break;
				case  0xCF:// SET 1,A
  					SET(1,A);
					break;
				case  0xD0:// SET 2,B
  					SET(2,B);
					break;
				case  0xD1:// SET 2,C
  					SET(2,C);
					break;
				case  0xD2:// SET 2,D
  					SET(2,D);
					break;
				case  0xD3:// SET 2,E
  					SET(2,E);
					break;
				case  0xD4:// SET 2,H
  					SET(2,H);
					break;
				case  0xD5:// SET 2,L
  					SET(2,L);
					break;
				case  0xD6:// SET 2,(HL)
  					tempbyte=readMem(HL);
					SET(2,tempbyte);
					writeMem(HL,tempbyte);
					break;
				case  0xD7:// SET 2,A
  					SET(2,A);
					break;
				case  0xD8:// SET 3,B
  					SET(3,B);
					break;
				case  0xD9:// SET 3,C
  					SET(3,C);
					break;
				case  0xDA:// SET 3,D
  					SET(3,D);
					break;
				case  0xDB:// SET 3,E
  					SET(3,E);
					break;
				case  0xDC:// SET 3,H
  					SET(3,H);
					break;
				case  0xDD:// SET 3,L
  					SET(3,L);
					break;
				case  0xDE:// SET 3,(HL)
  					tempbyte=readMem(HL);
					SET(3,tempbyte);
					writeMem(HL,tempbyte);
					break;
				case  0xDF:// SET 3,A
  					SET(3,A);
					break;
				case  0xE0:// SET 4,B
  					SET(4,B);
					break;
				case  0xE1:// SET 4,C
  					SET(4,C);
					break;
				case  0xE2:// SET 4,D
  					SET(4,D);
					break;
				case  0xE3:// SET 4,E
  					SET(4,E);
					break;
				case  0xE4:// SET 4,H
  					SET(4,H);
					break;
				case  0xE5:// SET 4,L
  					SET(4,L);
					break;
				case  0xE6:// SET 4,(HL)
  					tempbyte=readMem(HL);
					SET(4,tempbyte);
					writeMem(HL,tempbyte);
					break;
				case  0xE7:// SET 4,A
  					SET(4,A);
					break;
				case  0xE8:// SET 5,B
  					SET(5,B);
					break;
				case  0xE9:// SET 5,C
  					SET(5,C);
					break;
				case  0xEA:// SET 5,D
  					SET(5,D);
					break;
				case  0xEB:// SET 5,E
  					SET(5,E);
					break;
				case  0xEC:// SET 5,H
  					SET(5,H);
					break;
				case  0xED:// SET 5,L
  					SET(5,L);
					break;
				case  0xEE:// SET 5,(HL)
  					tempbyte=readMem(HL);
					SET(5,tempbyte);
					writeMem(HL,tempbyte);
					break;
				case  0xEF:// SET 5,A
  					SET(5,A);
					break;
				case  0xF0:// SET 6,B
  					SET(6,B);
					break;
				case  0xF1:// SET 6,C
  					SET(6,C);
					break;
				case  0xF2:// SET 6,D
  					SET(6,D);
					break;
				case  0xF3:// SET 6,E
  					SET(6,E);
					break;
				case  0xF4:// SET 6,H
  					SET(6,H);
					break;
				case  0xF5:// SET 6,L
  					SET(6,L);
					break;
				case  0xF6:// SET 6,(HL)
  					tempbyte=readMem(HL);
					SET(6,tempbyte);
					writeMem(HL,tempbyte);
					break;
				case  0xF7:// SET 6,A
  					SET(6,A);
					break;
				case  0xF8:// SET 7,B
  					SET(7,B);
					break;
				case  0xF9:// SET 7,C
  					SET(7,C);
					break;
				case  0xFA:// SET 7,D
  					SET(7,D);
					break;
				case  0xFB:// SET 7,E
  					SET(7,E);
					break;
				case  0xFC:// SET 7,H
  					SET(7,H);
					break;
				case  0xFD:// SET 7,L
  					SET(7,L);
					break;
				case  0xFE:// SET 7,(HL)
  					tempbyte=readMem(HL);
					SET(7,tempbyte);
					writeMem(HL,tempbyte);
					break;
				case  0xFF:// SET 7,A
  					SET(7,A);
					break;

				/*RES b,r*/
				case 0x80:// RES 0,B
  					RES(0,B);
					break;
				case 0x81:// RES 0,C
  					RES(0,C);
					break;
				case 0x82:// RES 0,D
  					RES(0,D);
					break;
				case 0x83:// RES 0,E
  					RES(0,E);
					break;
				case 0x84:// RES 0,H
  					RES(0,H);
					break;
				case 0x85:// RES 0,L
  					RES(0,L);
					break;
				case 0x86:// RES 0,(HL)
  					tempbyte=readMem(HL);
					RES(0,tempbyte);
					writeMem(HL,tempbyte);
					break;
				case 0x87:// RES 0,A
  					RES(0,A);
					break;
				case 0x88:// RES 1,B
  					RES(1,B);
					break;
				case 0x89:// RES 1,C
  					RES(1,C);
					break;
				case 0x8A:// RES 1,D
  					RES(1,D);
					break;
				case 0x8B:// RES 1,E
  					RES(1,E);
					break;
				case 0x8C:// RES 1,H
  					RES(1,H);
					break;
				case 0x8D:// RES 1,L
  					RES(1,L);
					break;
				case 0x8E:// RES 1,(HL)
  					tempbyte=readMem(HL);
					RES(1,tempbyte);
					writeMem(HL,tempbyte);
					break;
				case 0x8F:// RES 1,A
  					RES(1,A);
					break;
				case 0x90:// RES 2,B
  					RES(2,B);
					break;
				case 0x91:// RES 2,C
  					RES(2,C);
					break;
				case 0x92:// RES 2,D
  					RES(2,D);
					break;
				case 0x93:// RES 2,E
  					RES(2,E);
					break;
				case 0x94:// RES 2,H
  					RES(2,H);
					break;
				case 0x95:// RES 2,L
  					RES(2,L);
					break;
				case 0x96:// RES 2,(HL)
  					tempbyte=readMem(HL);
					RES(2,tempbyte);
					writeMem(HL,tempbyte);
					break;
				case 0x97:// RES 2,A
  					RES(2,A);
					break;
				case 0x98:// RES 3,B
  					RES(3,B);
					break;
				case 0x99:// RES 3,C
  					RES(3,C);
					break;
				case 0x9A:// RES 3,D
  					RES(3,D);
					break;
				case 0x9B:// RES 3,E
  					RES(3,E);
					break;
				case 0x9C:// RES 3,H
  					RES(3,H);
					break;
				case 0x9D:// RES 3,L
  					RES(3,L);
					break;
				case 0x9E:// RES 3,(HL)
  					tempbyte=readMem(HL);
					RES(3,tempbyte);
					writeMem(HL,tempbyte);
					break;
				case 0x9F:// RES 3,A
  					RES(3,A);
					break;
				case 0xA0:// RES 4,B
  					RES(4,B);
					break;
				case 0xA1:// RES 4,C
  					RES(4,C);
					break;
				case 0xA2:// RES 4,D
  					RES(4,D);
					break;
				case 0xA3:// RES 4,E
  					RES(4,E);
					break;
				case 0xA4:// RES 4,H
  					RES(4,H);
					break;
				case 0xA5:// RES 4,L
  					RES(4,L);
					break;
				case 0xA6:// RES 4,(HL)
  					tempbyte=readMem(HL);
					RES(4,tempbyte);
					writeMem(HL,tempbyte);
					break;
				case 0xA7:// RES 4,A
  					RES(4,A);
					break;
				case 0xA8:// RES 5,B
  					RES(5,B);
					break;
				case 0xA9:// RES 5,C
  					RES(5,C);
					break;
				case 0xAA:// RES 5,D
  					RES(5,D);
					break;
				case 0xAB:// RES 5,E
  					RES(5,E);
					break;
				case 0xAC:// RES 5,H
  					RES(5,H);
					break;
				case 0xAD:// RES 5,L
  					RES(5,L);
					break;
				case 0xAE:// RES 5,(HL)
  					tempbyte=readMem(HL);
					RES(5,tempbyte);
					writeMem(HL,tempbyte);
					break;
				case 0xAF:// RES 5,A
  					RES(5,A);
					break;
				case 0xB0:// RES 6,B
  					RES(6,B);
					break;
				case 0xB1:// RES 6,C
  					RES(6,C);
					break;
				case 0xB2:// RES 6,D
  					RES(6,D);
					break;
				case 0xB3:// RES 6,E
  					RES(6,E);
					break;
				case 0xB4:// RES 6,H
  					RES(6,H);
					break;
				case 0xB5:// RES 6,L
  					RES(6,L);
					break;
				case 0xB6:// RES 6,(HL)
  					tempbyte=readMem(HL);
					RES(6,tempbyte);
					writeMem(HL,tempbyte);
					break;
				case 0xB7:// RES 6,A
  					RES(6,A);
					break;
				case 0xB8:// RES 7,B
  					RES(7,B);
					break;
				case 0xB9:// RES 7,C
  					RES(7,C);
					break;
				case 0xBA:// RES 7,D
  					RES(7,D);
					break;
				case 0xBB:// RES 7,E
  					RES(7,E);
					break;
				case 0xBC:// RES 7,H
  					RES(7,H);
					break;
				case 0xBD:// RES 7,L
  					RES(7,L);
					break;
				case 0xBE:// RES 7,(HL)
  					tempbyte=readMem(HL);
					RES(7,tempbyte);
					writeMem(HL,tempbyte);
					break;
				case 0xBF:// RES 7,A
  					RES(7,A);
					break;
				default:
					break;
			}
			break;

		/*****************GMB Jumpcommands*********************/

		/*JP nn*/
		case 0xC3:
			//TODO: mudar para gbcpu.pc provavelmente
			opAux.Byte.l=readMem(pc++);
			opAux.Byte.h= readMem(pc);
			pc=opAux.Word;
			break;

		/* JP (HL) */
		case 0xE9:
			pc=HL;
			break; 

		//TODO : verificar pc++
		/*JP cc,nn*/
		case 0xC2: // JP  NZ,nn
			if ((F & Z_FLAG)==0 ) {
			  opAux.Byte.l=readMem(pc++);
			  opAux.Byte.h= readMem(pc++);
			  pc=opAux.Word;
			}else pc+=2;
			break;

		case 0xCA: // JP  Z,nn
			if ((F & Z_FLAG)==1 ) {
			  opAux.Byte.l=readMem(pc++);
			  opAux.Byte.h= readMem(pc++);
			  pc=opAux.Word;
			}else pc+=2;
			break;

		case 0xD2: // JP  NC,nn
			if ((F & C_FLAG)==0 ) {
			  opAux.Byte.l=readMem(pc++);
			  opAux.Byte.h= readMem(pc++);
			  pc=opAux.Word;
			}else pc+=2;
			break;

		case 0xDA: // JP  C,nn
			if ((F & C_FLAG)==1 ){ 
			  opAux.Byte.l=readMem(pc++);
			  opAux.Byte.h= readMem(pc++);
			  pc=opAux.Word;
			}else pc+=2;
			break;

		/*JR PC+dd*/
		//TODO: verificar range (pc++)
		case 0x18:
			signedtempbyte = readMem(pc++);
			pc += signedtempbyte;
			break;

		/*JR   f,PC+dd*/
		case 0x20://JR NZ,dd
			if ((F & Z_FLAG)==0 ) {
				signedtempbyte=readMem(pc++);
				pc+=signedtempbyte;
			}else pc++;
			break;
		case 0x28://JR Z,dd
			if ((F & Z_FLAG)==1 ) {
				signedtempbyte=readMem(pc++);
				pc+=signedtempbyte;
			}else pc++;
			break;
		case 0x30://JR NC,dd
			if ((F & C_FLAG)==0 ) {
				signedtempbyte=readMem(pc++);
				pc+=signedtempbyte;
			}else pc++;
			break;
		case 0x38://JR C,dd
			if ((F & C_FLAG)==1 ){
				signedtempbyte=readMem(pc++);
				pc+=signedtempbyte;
			}else pc++;
			break;

		/*CALL nn*/
		//TODO: mudar para PC provavelmente
		case 0xCD:
			opAux.Byte.l = readMem(pc++);
			opAux.Byte.h = readMem(pc++);
                        writeMem(SP-1,((pc&0xFF00)>>8));
                        writeMem(SP-2,(pc&0xFF));
			SP-=2;
			pc=opAux.Word;
			break;

                case 0xC4://CALL NZ,nn
                    if ((F & Z_FLAG)==0 ) {
                        opAux.Byte.l = readMem(pc++);
                        opAux.Byte.h = readMem(pc++);
                        writeMem(SP-1,((pc&0xFF00)>>8));
                        writeMem(SP-2,(pc&0xFF));
                        SP-=2;
                        pc=opAux.Word;
                    }else pc+=2;
                    break;

		case 0xCC://CALL Z,nn
                    if ((F & Z_FLAG)==1 ) {
                        opAux.Byte.l = readMem(pc++);
                        opAux.Byte.h = readMem(pc++);
                        writeMem(SP-1,((pc&0xFF00)>>8));
                        writeMem(SP-2,(pc&0xFF));
                        SP-=2;
                        pc=opAux.Word;
                    }else pc+=2;
                    break;

		case 0xD4://CALL NC,nn
                    if ((F & C_FLAG)==0 ) {
                        opAux.Byte.l = readMem(pc++);
                        opAux.Byte.h = readMem(pc++);
                        writeMem(SP-1,((pc&0xFF00)>>8));
                        writeMem(SP-2,(pc&0xFF));
                        SP-=2;
                        pc=opAux.Word;
                    }else pc+=2;
                    break;

		case 0xDC://CALL C,nn
                    if ((F & C_FLAG)==1 ) {
                        opAux.Byte.l = readMem(pc++);
                        opAux.Byte.h = readMem(pc++);
                        writeMem(SP-1,((pc&0xFF00)>>8));
                        writeMem(SP-2,(pc&0xFF));
                        SP-=2;
                        pc=opAux.Word;
                    }else pc+=2;
                    break;

                /*RET*/
                case 0xC9:
                    opAux.Byte.l = readMem(SP);
                    opAux.Byte.h = readMem(SP+1);
                    SP+=2;
                    pc=opAux.Word;
                    break;

                /*RET cc*/
                case 0xC0://RET NZ
                        if ((F & Z_FLAG)==0 ) {
                            opAux.Byte.l = readMem(SP);
                            opAux.Byte.h = readMem(SP+1);
                            SP+=2;
                            pc=opAux.Word;
                        }
                        break;
                case 0xC8://RET Z
                        if ((F & Z_FLAG)==1 ) {
                            opAux.Byte.l = readMem(SP);
                            opAux.Byte.h = readMem(SP+1);
                            SP+=2;
                            pc=opAux.Word;
                        }
                        break;
                case 0xD0://RET NC
                        if ((F & C_FLAG)==0 ) {
                            opAux.Byte.l = readMem(SP);
                            opAux.Byte.h = readMem(SP+1);
                            SP+=2;
                            pc=opAux.Word;
                        }
                        break;
                case 0xD8://RET C
                        if ((F & C_FLAG)==1 ){
                            opAux.Byte.l = readMem(SP);
                            opAux.Byte.h = readMem(SP+1);
                            SP+=2;
                            pc=opAux.Word;
                        }
                        break;

                /*RETI*/
                case 0xD9:
                        IME=1;
                        opAux.Byte.l = readMem(SP);
                        opAux.Byte.h = readMem(SP+1);
                        SP+=2;
                        pc=opAux.Word;
                        break;

                /*RST n*/
                case 0xC7://RST 0x0
                    writeMem(SP-1,((pc&0xFF00)>>8));
                    writeMem(SP-2,(pc&0xFF));
                    SP-=2;
                    pc=0;
                    break;
                case 0xD7://RST 0x10
                    writeMem(SP-1,((pc&0xFF00)>>8));
                    writeMem(SP-2,(pc&0xFF));
                    SP-=2;
                    pc=0x10;
                    break;
                case 0xDF://RST 0x18
                    writeMem(SP-1,((pc&0xFF00)>>8));
                    writeMem(SP-2,(pc&0xFF));
                    SP-=2;
                    pc=0x18;
                    break;
                case 0xE7://RST 0x20
                    writeMem(SP-1,((pc&0xFF00)>>8));
                    writeMem(SP-2,(pc&0xFF));
                    SP-=2;
                    pc=0x20;
                    break;
                case 0xEF://RST 0x28
                    writeMem(SP-1,((pc&0xFF00)>>8));
                    writeMem(SP-2,(pc&0xFF));
                    SP-=2;
                    pc=0x28;
                    break;
                case 0xF7://RST 0x30
                    writeMem(SP-1,((pc&0xFF00)>>8));
                    writeMem(SP-2,(pc&0xFF));
                    SP-=2;
                    pc=0x30;
                    break;
                case 0xFF://RST 0x38
                    writeMem(SP-1,((pc&0xFF00)>>8));
                    writeMem(SP-2,(pc&0xFF));
                    SP-=2;
                    pc=0x38;
                    break;
                case 0xCF://RST 0x8
                    writeMem(SP-1,((pc&0xFF00)>>8));
                    writeMem(SP-2,(pc&0xFF));
                    SP-=2;
                    pc=0x8;
                    break;

              /*****************GMB CPU-Controlcommands*********************/


                case 0x3F: //CCF
                    F = (F &(Z_FLAG|C_FLAG))^C_FLAG;
                    break;
                case 0x37: //SCF
                    F = (F&Z_FLAG)|C_FLAG;
                    break;
                case 0x76://HALT
                    //TODO: fazer algo ou nao
                    break;
                case 0x10://STOP
                    //TODO: fazer algo ou nao
                    pc++;
                    break;
                case 0xF3: //DI
                    IME=0;
                    break;
                case 0xFB: //EI
                    IME=1;


		default:
			break;
		}

		if (Counter <= 0)
		{
			//Check for interrupts and do other
			// cyclic tasks here

			Counter += ncycles;
			break;
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
