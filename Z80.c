/*
 * Z80.c
 *
 *  Created on: 2010/06/17
 *      Author: brNX
 */

#ifdef _MSC_VER
#include "no_sillywarnings.h"
#endif

#include "Z80.h"
#include "memory.h"
#include "lcd.h"

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
        F = (H_FLAG & ((SP ^ (val) ^ opAux32.W.l) >> 7));\
        CHECK_C_ADD16(val);\
        SP=opAux32.W.l

#define LD_HLSP(val) \
        opAux32.DW = SP + val;\
        F = (H_FLAG & ((SP ^ (val) ^ opAux32.W.l) >> 7));\
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

#define PUSHPC()\
        writeMem(SP-2,gbcpu.pc.Byte.l,gbcpu.mem);\
        writeMem(SP-1,gbcpu.pc.Byte.h,gbcpu.mem);\
        SP-=2



void resetZ80(Memory * mem,LCD * lcd)
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

    gbcpu.ime=0;
    gbcpu.set_ime=0;

    gbcpu.mem=mem;
    gbcpu.lcd=lcd;

    //time for 1 line
    lcd->scanlinecyclecounter=456;

    mem->IO[0x05] = 0x00   ;// TIMA
    mem->IO[0x06] = 0x00   ;// TMA
    mem->IO[0x07] = 0x00   ;// TAC
    //mem->IO[0x0F] = 0x01   ;// IF
    mem->IO[0x10] = 0x80   ;// NR10
    mem->IO[0x11] = 0xBF   ;// NR11
    mem->IO[0x12] = 0xF3   ;// NR12
    mem->IO[0x14] = 0xBF   ;// NR14
    mem->IO[0x16] = 0x3F   ;// NR21
    mem->IO[0x17] = 0x00   ;// NR22
    mem->IO[0x19] = 0xBF   ;// NR24
    mem->IO[0x1A] = 0x7F   ;// NR30
    mem->IO[0x1B] = 0xFF   ;// NR31
    mem->IO[0x1C] = 0x9F   ;// NR32
    mem->IO[0x1E] = 0xBF   ;// NR33
    mem->IO[0x20] = 0xFF   ;// NR41
    mem->IO[0x21] = 0x00   ;// NR42
    mem->IO[0x22] = 0x00   ;// NR43
    mem->IO[0x23] = 0xBF   ;// NR30
    mem->IO[0x24] = 0x77   ;// NR50
    mem->IO[0x25] = 0xF3   ;// NR51
    mem->IO[0x26] = 0xF1   ;// -GB, $F0-SGB ; NR52
    mem->IO[0x40] = 0x91   ;// LCDC
    //mem->IO[0x41] = 0x84   ;// STAT
    mem->IO[0x42] = 0x00   ;// SCY
    mem->IO[0x43] = 0x00   ;// SCX
    mem->IO[0x44] = 0x00   ;// LY
    mem->IO[0x45] = 0x00   ;// LYC
    mem->IO[0x47] = 0xFC   ;// BGP
    mem->IO[0x48] = 0xFF   ;// OBP0
    mem->IO[0x49] = 0xFF   ;// OBP1
    mem->IO[0x4A] = 0x00   ;// WY
    mem->IO[0x4B]= 0;   // WX
    mem->ie=0;          // IE
}

int execute(int ncycles)
{
    int Counter = ncycles;

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
        int usedcycles=0;

#ifdef DEBUG
        printStatusZ80();
        printf("Counter: %u \n",Counter);
        printf("**************************\n");
        printMEMStatus(gbcpu.mem);
        /*misc*/
        printf("lcd cyclecounter: %d\n",gbcpu.lcd->scanlinecyclecounter);
        printf("**************************\n");
#endif

        /*interupts*/
       if (IME && (IE & IF)){

           //v-sync
           if (IE & IF & 0x1){
               IME=0;
               IF&= ~(0x1);
               PUSHPC();
               PC=0x40;
               gbcpu.halt=0;
           }else
           //LCD STAT
           if (IE & IF & 0x2){
               IME=0;
               IF&= ~(0x2);
               PUSHPC();
               PC=0x48;
               gbcpu.halt=0;
           }else
           //Timer
           if (IE & IF & 0x4){
               IME=0;
               IF&= ~(0x4);
               PUSHPC();
               PC=0x50;
               gbcpu.halt=0;
           }else
           //Serial
           if (IE & IF & 0x8){
                IME=0;
                IF&= ~(0x8);
                PUSHPC();
                PC=0x58;
                gbcpu.halt=0;
           }else
           //Joypad
           if (IE & IF & 0x10){
                IME=0;
                IF&= ~(0x10);
                PUSHPC();
                PC=0x60;
                gbcpu.halt=0;
            }
       }

       if (SET_IME){
        IME=1;
        SET_IME=0;
       }


       if(!gbcpu.halt){

        OpCode = readMem(PC, gbcpu.mem);
        PC++;
        usedcycles += Cycles[OpCode];

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
    }else
        //halt
        usedcycles=4;

#ifdef DEBUG
        /*printf("Press <ENTER> to Continue\n\n");
        for(;;){
            char c=getchar();
	    if (c == '\n')
		break;
        }*/
#endif

        //update timers,lcd status and cyclecount
        Counter-=usedcycles;
        gbcpu.cyclecounter += usedcycles;

        updatetimers(usedcycles);
        updateLCDStatus(usedcycles);
        LY_LYC();


	if (Counter <= 0)
	{
            return 0;
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
        int usedcycles=0;

	switch (OpCode)
	{

	#include "Opcodes.h"

	default:
		break;
	}

}

INLINE void updatetimers(int cycles){

    //DIV
    gbcpu.timer1 += cycles;

    if (gbcpu.timer1 >= 256 ){
        gbcpu.timer1=0;
        DIV++;
    }

    //TIMA
    if (TAC & 0x4){

        gbcpu.timer2 += cycles;

        if( gbcpu.timer2 >= TACCycles[TAC&0x3]){

            gbcpu.timer2=0;
            TIMA++;

            //overflow
            if (TIMA==0){
                interruptZ80(I_TIMER);
                TIMA=TMA;
            }
        }
    }
}


INLINE void LY_LYC(){

    //LY=LYC?
    if (LY == LYC){
        //STAT
        STAT |= 0x4;
        if (STAT & 0x40)
            interruptZ80(I_LCD_STAT);
    }else{
        STAT &= ~0x4;
    }
}

//update lcdstatus
INLINE void updateLCDStatus(int cycles){

    //lcd enabled
    if (LCDC&0x80){

        gbcpu.lcd->scanlinecyclecounter -= cycles;

        //setting modes and requesting interrupts when switching
        if(LY>=144){
            //set mode to 1
            STAT=(STAT&0xFC) | 0x1;
        }else{

            int previousmode = STAT & 0x3;
            int requestinterrupt = 0;

            if (gbcpu.lcd->scanlinecyclecounter >= 376)
            {
                //set mode to 2 (OAM-RAM search)
                STAT=(STAT&0xFC) | 0x2; 
                requestinterrupt  = STAT & 0x20;
            }
            else if(gbcpu.lcd->scanlinecyclecounter >= 204)
            {
                //set mode to 3 (Data Transfer)
                STAT=(STAT&0xFC) | 0x3;
            }
            else
            {
                //set to mode 0 (H-Blank)
                STAT&=0xFC;
                requestinterrupt  = STAT & 0x8;
            }

            //request interrupt when mode changed for the 1st time
            if (requestinterrupt && (previousmode != (STAT & 0x3)))
                interruptZ80(I_LCD_STAT);

        }

        //move to next scanline
        if (gbcpu.lcd->scanlinecyclecounter <=0)
        {
            LY+=1;
            gbcpu.lcd->scanlinecyclecounter=456;

            //starting vsync period
            if (LY==144){

                //request vblank
                interruptZ80(I_V_BLANK);

                //set mode to 1
                STAT=(STAT&0xFC) | 0x1;
                return;
            }

            if(LY <144){
               drawScanline();
            }

            LY=LY%154;

        }

    }else{
        //set mode to 1
        STAT=(STAT&0xFC) | 0x1;
        //reset counter
        gbcpu.lcd->scanlinecyclecounter=456;
        //reset LY
        LY=0;
    }
}



void interruptZ80(int type)
{
    switch(type){
    case I_V_BLANK:
        IF |= 0x1;
        break;
    case I_LCD_STAT:
        IF |= 0x2;
        break;
    case I_TIMER:
        IF |= 0x4;
        break;
    case I_SERIAL:
        IF |= 0x8;
        break;
    case I_JOYPAD:
        IF |= 0x10;
        break;
    }

}


void printStatusZ80(){
    printf("*******Z80 Status*********\n");
    printf("ZF:%d NF:%d HF:%d CF:%d\n",(F>>7),(F&N_FLAG)>>6,(F&H_FLAG)>>5,(F&C_FLAG)>>4);
    printf("AF:%04x BC:%04x DE:%04x HL:%04x PC:%04x SP:%04x\n",AF,BC,DE,HL,PC,SP);
    printf("IME: %d\n",IME);
    printf("**************************\n");

}
