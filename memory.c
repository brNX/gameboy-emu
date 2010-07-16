/*
 * memory.c
 *
 *  Created on: 2010/06/18
 *      Author: brNX
 */
#include "memory.h"
#include <stdio.h>

//0000-3FFF   16KB ROM Bank 00     (in cartridge, fixed at bank 00)
//4000-7FFF   16KB ROM Bank 01..NN (in cartridge, switchable bank number)
//8000-9FFF   8KB Video RAM (VRAM) (switchable bank 0-1 in CGB Mode)
//A000-BFFF   8KB External RAM     (in cartridge, switchable bank, if any)
//C000-CFFF   4KB Work RAM Bank 0 (WRAM)
//D000-DFFF   4KB Work RAM Bank 1 (WRAM)  (switchable bank 1-7 in CGB Mode)
//E000-FDFF   Same as C000-DDFF (ECHO)    (typically not used)
//FE00-FE9F   Sprite Attribute Table (OAM)
//FEA0-FEFF   Not Usable
//FF00-FF7F   I/O Ports
//FF80-FFFE   High RAM (HRAM)
//FFFF        Interrupt Enable Register

//TODO: for now
extern INLINE uint8 readMem(uint16 address)
{
	return (gb_memory[address]);
}


extern INLINE uint8 readOpcode(uint16 address)
{
        return (gb_memory[address]);
}


extern INLINE void writeMem(uint16 address, uint8 value)
{
	uint16 x;
        uint8 addr;
        uint8 change;

        switch (address >> 12){

        case 0x0:
            break;
        case 0x1:
            break;

        //rom bank switching
        //2000<= adress <= 3FFF
        case 0x2:
        case 0x3:

            x = address - 0x2000;
            switch (gb_cart->type.index){

            //MBC1
            case 0x1:
            case 0x2:
            case 0x3:
                //00 -> 01, 20 -> 21 , 40 -> 41 , 60 -> 61
                addr = value&0x1F;
                addr+=(addr==0)?1:0;
                gb_cart->rombank=(gb_cart->rombank&0xE0) | addr;
                break;

            //MBC2
            case 0x5:
            case 0x6:
                gb_cart->rombank=value&0xF;
                break;

            //MBC3
            case 0xF:
            case 0x10:
            case 0x11:
            case 0x12:
            case 0x13:
                addr = value&0x7F;
                addr+=(addr==0)?1:0;
                gb_cart->rombank=value;
                break;

            default :
                break;

            }

            break;

        /*4000-5FFF - RAM Bank Number (MBC 1/3) - or - Upper Bits of ROM Bank Number (Write Only) (MBC 1)
        -or - RTC Register Select (Write Only) (MBC 3)*/
        case 0x4:
        case 0x5:


            //MBC1
            /*0x1 <= index <= 0x3*/
            x= gb_cart->type.index - 0x1;
            if (x <= 0x3){

                change = value&0x3; //2 bit register

                /*if rom mode*/
                if (gb_cart->mbc1mode==0)
                    gb_cart->rombank=(gb_cart->rombank&0x1F) | (change<<5);
                else
                   gb_cart->rambank= change;
                return;
            }

            //MBC3
            /*0xF <= index <= 0x13*/
            x= gb_cart->type.index - 0xF;
            if (x <= 0x13){
                change = value & 0xF;
                switch(change){

                    /*ram bank change*/
                case 0x0:
                case 0x1:
                case 0x2:
                case 0x3:
                    gb_cart->rambank= change;
                    break;

                /*rtc*/
                case 0x8:
                case 0x9:
                case 0xA:
                case 0xB:
                case 0xC:
                    gb_cart->mbc3rtc=change;
                    break;

                default:
                    break;
                }
                return;
            }

            break;

        case 0x6:
            break;
        case 0x7:
            break;
        case 0x8:
            break;
        case 0x9:
            break;
        case 0xA:
            break;
        case 0xB:
            break;

        /*C000-CFFF   4KB Work RAM Bank 0 (WRAM)
          D000-DFFF   4KB Work RAM Bank 1 (WRAM)  (switchable bank 1-7 in CGB Mode)*/
        case 0xC:
            gb_memory[address] = value;
            gb_memory[0XE000+(address & 0xFFF)] = value;
            break;
        case 0xD:
            gb_memory[address] = value;
            x = address & 0xFFF;
            if (x <= 0xDFF) gb_memory[0XF000+x] = value;
            break; 

        /*E000-FDFF   Same as C000-DDFF (ECHO)    (typically not used)*/
        case 0xE:
            gb_memory[address] = value;
            gb_memory[0XC000+(address & 0xFFF)] = value;
            break;
        case 0xF:
            gb_memory[address] = value;
            x = address & 0xFFF;
            if (x <= 0xDFF) gb_memory[0XD000+x] = value;
            break;

     default:
            break;
        }


    }
