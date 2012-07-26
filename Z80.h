/*
 * Z80.h
 *
 *  Created on: 2010/06/17
 *      Author: brNX
 */

#ifndef Z80_H_
#define Z80_H_

#include "types.h"
#include "memory.h"
#include "lcd.h"

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

/*LCD and timer registers*/
#define STAT gbcpu.mem->IO[0x41]
#define LYC gbcpu.mem->IO[0x45]
#define LY gbcpu.mem->IO[0x44]
#define LCDC gbcpu.mem->IO[0x40]
#define DIV gbcpu.mem->IO[0x04]
#define TIMA gbcpu.mem->IO[0x05]
#define TMA gbcpu.mem->IO[0x06]
#define TAC gbcpu.mem->IO[0x07]
#define SCY gbcpu.mem->IO[0x42]
#define SCX gbcpu.mem->IO[0x43]
#define WY gbcpu.mem->IO[0x4A]
#define WX gbcpu.mem->IO[0x4B]
#define BGP gbcpu.mem->IO[0x47]
#define OBP0 gbcpu.mem->IO[0x48]
#define OBP1 gbcpu.mem->IO[0x49]

/*joypad register*/
#define JOYP gbcpu.mem->IO[00]

/*interupts registers*/
#define IME gbcpu.ime
#define SET_IME gbcpu.set_ime
#define IE  gbcpu.mem->rie
#define IF  gbcpu.mem->rif

#define Z_FLAG	 0x80	/* Zero				Bit 7 */
#define N_FLAG   0x40	/* Add/Substract	Bit 6 */
#define H_FLAG	 0x20	/* Half Carry		Bit 5 */
#define C_FLAG	 0x10	/* Carry			Bit 4 */

#define I_V_BLANK   0
#define I_LCD_STAT  1
#define I_TIMER     2
#define I_SERIAL    3
#define I_JOYPAD    4

#ifdef __cplusplus
extern "C"
{
#endif

    //union para registo 16bit com accesso 8bit
    typedef union
    {
        struct
        {
#ifndef B_ENDIAN
            uint8 l,h; /* ...in little-endian architecture */
#else
            uint8 h, l; /* ...in big-endian architecture */
#endif
        } Byte;
        uint16 Word;
    } reg16bit;

    typedef union
    {
        struct
        {
#ifndef B_ENDIAN
            uint16 l,h; /* ...in little-endian architecture */
#else
            uint16 h, l; /* ...in big-endian architecture */
#endif
        } W;
        uint32 DW;
    } reg32bit;

    typedef struct _Z80
    {
        reg16bit af, bc, de, hl, sp, pc;
        int ime;
        int set_ime;
        int cyclecounter;
        int pause;
        int halt;
        Memory * mem;
        LCD * lcd;
        uint8 joypad;

        int forcequit;

    } Z80;
    extern Z80 gbcpu;

    void resetZ80(Memory * mem,LCD * lcd); //      -> resets the CPU core
    int execute(int nclyces);//   -> the core executes n cycles
    void interruptZ80(int type); //      -> sends an interrupt signal
    void printStatusZ80();
    void execOpcode(uint8 opcode);

    INLINE void updatetimers(int cycles);
    INLINE void LY_LYC();
    INLINE void updateLCDStatus(int cycles);


#ifdef __cplusplus
}
#endif

#endif /* Z80_H_ */
