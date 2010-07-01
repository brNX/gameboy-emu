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
}

int execute(int ncycles)
{
	int Counter = ncycles;
	uint8_t pc = PC;




	for (;;)
	{
		//variaveis temporarias para operacoes(não existe no processador)
		reg16bit opAux;
		uint16_t address;
		uint8_t tempbyte;
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
		case 0xE8:
			ADD_SP(readMem(pc++));
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
		case 0xF8:
			LD_HLSP(readMem(pc++));
			break;

		/*****************GMB Rotate- and Shift-Commands*********************/

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
			//TODO: get  and add ticks to counter
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
				default:
					break;
			}



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
