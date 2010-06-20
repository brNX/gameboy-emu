/*
 * Z80.c
 *
 *  Created on: 2010/06/17
 *      Author: brNX
 */

#include "Z80.h"
int Cycles[]={4,4,6,4,7};

	void reset(Z80 * cpu){
		  cpu->pause = 1;
		  cpu->halt = 0;
		  cpu->AF.S.h=0x01; // 0x01->GB/SGB; 0xFF->GBP; 0x11->GBC
		  cpu->AF.S.l=0xB0; // F=0xB0->Z1 N0 H1 C1
		  cpu->BC.M=0x0013;
		  cpu->DE.M=0x00D8;
		  cpu->PC.M=0x0100;
		  cpu->SP.M=0xFFFE;
		  cpu->HL.M=0x014D;
		  cpu->cyclecounter=0;
		  cpu->SP.M=0xFFFE;
	}

	int execute(Z80 * cpu,int ncycles){
		int Counter=ncycles;
		uint8_t PC=cpu->PC.M;

		for(;;)
		{
		  uint8_t OpCode=readOpcode(PC++);
		  Counter-=Cycles[OpCode];

		  switch(OpCode)
		  {
		    case 0x00:
		    	break;
		    case 0x01:
		    	break;
		    default:
		    	break;
		  }

		  if(Counter<=0)
		  {
		    //Check for interrupts and do other
		    // cyclic tasks here

		    Counter+=ncycles;
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

	void interrupt(Z80 * cpu){

	}

	inline uint8_t readOpcode(uint16_t address){
		//TODO: para ja
		return 0;
	}
