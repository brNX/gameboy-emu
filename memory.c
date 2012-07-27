/*
 * memory.c
 *
 *  Created on: 2010/06/18
 *      Author: brNX
 */
#include "Z80.h"
#include "memory.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


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

void byte2String(char *strBits, unsigned long long byte,int tamanho)
{
        char  mask = 0x01;  //get LSbit
        char  bit;
        int i;

        for (i = (tamanho-1); i >= 0; i--)
        {
                bit = byte & mask;
                strBits[i] = bit + 48;
                byte = byte >> 1;
        }
        strBits[tamanho]='\0';
}

void resetstring(char * string){
    int i;
    for (i=0;i<8;i++)
        string[i]=0;
}

void printMEMStatus(Memory * mem)
{
    
    char string[15];
    uint8 c0,c1,c2,c3;

    printf("*******MEM Status*********\n");
    byte2String(string,mem->rie,5);
    printf("IE: %s ",string);
    byte2String(string,mem->IO[0x0F],5);
    printf("IF: %s \n",string);
    byte2String(string,mem->IO[0x40],8);
    printf("LCDC: %s \n",string);
    byte2String(string,mem->IO[0x41],7);
    printf("STAT: %s ",string);
    printf("mode: %u \n",mem->IO[0x41]&0x3);
    printf("SCY: %u \n",mem->IO[0x42]);
    printf("SCX: %u \n",mem->IO[0x43]);
    printf("LY: %u \n",mem->IO[0x44]);
    printf("LYC: %u \n",mem->IO[0x45]);
    printf("WY: %u \n",mem->IO[0x4A]);
    printf("WX: %u \n",mem->IO[0x4B]);

    c0=(mem->IO[0x47] & 0x3);
    c1=((mem->IO[0x47]>>2) & 0x3);
    c2=((mem->IO[0x47]>>4) & 0x3);
    c3=((mem->IO[0x47]>>6) & 0x3);
    printf("BGP: C3: %u C2: %u C1: %u C0: %u\n",c3,c2,c1,c0);

    c1=((mem->IO[0x48]>>2) & 0x3);
    c2=((mem->IO[0x48]>>4) & 0x3);
    c3=((mem->IO[0x48]>>6) & 0x3);
    printf("OBP0: C3: %u C2: %u C1: %u \n",c3,c2,c1);

    c1=((mem->IO[0x49]>>2) & 0x3);
    c2=((mem->IO[0x49]>>4) & 0x3);
    c3=((mem->IO[0x49]>>6) & 0x3);
    printf("OBP1: C3: %u C2: %u C1: %u \n",c3,c2,c1);

    printf("DIV: %u \n",mem->IO[0x04]);
    printf("TIMA: %u \n",mem->IO[0x05]);
    printf("TMA: %u \n",mem->IO[0x06]);
    printf("TAC: %u \n",mem->IO[0x07]);
    printf("**************************\n");
}

extern INLINE uint8 readMem(uint16 address,Memory * mem)
{
    uint8 index;
    uint32 newaddress;
    uint16 addr;

    switch (address >> 12){

    /************ROM**************/
    case 0x0:
    case 0x1:
    case 0x2:
    case 0x3:
    case 0x4:
    case 0x5:
    case 0x6:
    case 0x7:
        index=address >> 14;
        newaddress = address + index*((mem->cart->rombank-1)*0x4000);
        return mem->rombanks[newaddress];
        break;

    /*********VRAM**************/
    case 0x8:
    case 0x9:
        return mem->vram[address-0x8000];
        break;

    /*********external ram*********/
    case 0xA:

        //MBC2
        if (mem->cart->type.index == 0x05 || mem->cart->type.index == 0x06){
            /*0xA000 <= adress <= 0xA1FF*/
            addr = address - 0xA000;
            if (addr <= 0x1FF) return (mem->rambanks[addr]&0xF);
            break;
        }

    case 0xB:
        return mem->rambanks[address-0xA000 + (mem->cart->rambank*8192)];
        break;

    /***********Work RAM************/
    case 0xC:
    case 0xD:
        return mem->wram[address-0xC000];
        break;

    /********part of echo ram*******/
    case 0xE:
         return mem->wram[address-0xE000];
         break;

    //E000-FDFF   Same as C000-DDFF (ECHO)    (typically not used)
    //FE00-FE9F   Sprite Attribute Table (OAM)
    //FEA0-FEFF   Not Usable
    //FF00-FF7F   I/O Ports
    //FF80-FFFE   High RAM (HRAM)
    //FFFF        Interrupt Enable Register
    case 0xF:

         //FF00  joypad
         if (address == 0xFF00){
             return getJoypadState(mem);
             break;
         }


         //FE00-FE9F   Sprite Attribute Table (OAM)
         /*FE00 <= addr <= 0xFE9F*/
         addr= address - 0xFE00;
         if (addr <= 0x9F){
             return mem->OAM[addr];
             break;
         }

         //FF00-FF7F   I/O Ports
         addr= address - 0xFF00;
         /*FF00 <= addr <= 0xFF7F*/
         if (addr <= 0x7F){
             if (addr==0x0F)
                 return mem->rif;
             else
                 return mem->IO[addr];
              break;
         }

         //FF80-FFFE   High RAM (HRAM)
         /*FF80 <= addr <= 0xFFFE*/
         addr= address - 0xFF80;
         if (addr <= 0x7E){
             return mem->hram[addr];
             break;
         }


         //FFFF  Interrupt Enable Register
         if (address == 0xFFFF){
             return mem->rie;
             break;
         }

         //echo ram
         /*F000 <= addr <= 0xFDFF*/
         addr= address - 0xF000;
         if (addr <= 0xDFF){
             return mem->wram[0X1000|addr];
             break;
         }

        break;
    default:
        break;

    }

    return 0;
}


extern INLINE void writeMem(uint16 address, uint8 value,Memory * mem)
{
    uint16 addr;
    switch (address >> 12){

    case 0x0:
        break;
    case 0x1:
        break;

    //rom bank switching
    //2000<= adress <= 3FFF
    case 0x2:
    case 0x3:
        romBankSwitch(address,value,mem);
        break;

    /*4000-5FFF - RAM Bank Number (MBC 1/3) - or - Upper Bits of ROM Bank Number (Write Only) (MBC 1)
    -or - RTC Register Select (Write Only) (MBC 3)*/
    case 0x4:
    case 0x5:
        ramBankSwitch(address,value,mem);
        break;

    case 0x6:
        break;
    case 0x7:
        break;

    /*******Video Ram*********/
    case 0x8:
    case 0x9:
        mem->vram[address-0x8000]=value;
        break;

    /*******external ram********/
    case 0xA:

        //MBC2
        if (mem->cart->type.index == 0x05 || mem->cart->type.index == 0x06){
            /*0xA000 <= adress <= 0xA1FF*/
            addr = address - 0xA000;
            if (addr <= 0x1FF) mem->rambanks[addr]=(value&0xF);
            break;
        }

    case 0xB:
        mem->rambanks[address-0xA000 + (mem->cart->rambank*8192)]=value;
        break;

    /*C000-CFFF   4KB Work RAM Bank 0 (WRAM)*/
    /*D000-DFFF   4KB Work RAM Bank 1 (WRAM)  (switchable bank 1-7 in CGB Mode)*/
    case 0xC:
        addr=address & 0xFFF;
        mem->wram[addr] = value;
        break;
    case 0xD:
        addr= address - 0xC000;
        mem->wram[addr] = value;
        break;

    /*E000-FDFF   Same as C000-DDFF (ECHO)    (typically not used)*/
    case 0xE:
        addr=address & 0xFFF;
        mem->wram[addr] = value;
        break;

    //I/O Zone
    case 0xF:
#ifdef DEBUG
    printf("write to iozone\n");
#endif
        writeToIOZone(address,value,mem);
        break;
    }


}

INLINE uint8 getJoypadState(Memory * mem){
    
    uint8 state = ~JOYP;

    //directional keys
    if (!(state & (1<<4))){

        state &= ((gbcpu.joypad  >> 4) | 0xF0);

    }
    //button keys
    else if (!(state & (1<<5))){
        state &= ((gbcpu.joypad & 0xF) | 0xF0);
    }

    return state;
}


void initMemory(Memory * mem,Cartridge * cart){
    int romsize,ramsize;
    
    cart->rambank=0;
    cart->rombank=1;

    cart->mbc1mode=0;

    mem->cart=cart;

    
    /*16384 bytes *  n rombanks*/
    if (cart->size.nbanks > 0)
        romsize=cart->size.nbanks*16384*sizeof(uint8);
    else
        romsize=2*16384*sizeof(uint8);
    mem->rombanks=(uint8 *) malloc (romsize);


    ramsize=8*1024*sizeof(uint8);
    /*rambanks*/
    if (cart->ramsize == 3)
        ramsize=32*1024*sizeof(uint8);

    //MBC2
    if (cart->type.index == 0x06 || cart->type.index == 0x05)
        mem->rambanks=(uint8 *) malloc (512*sizeof(uint8));
    else{

        //TODO : read and write ram from/to file  (savegame)
        // if (ramsize > 0)
        mem->rambanks=(uint8 *) malloc (ramsize);
        memset(mem->rambanks,0xFF,ramsize);
    }


    /*copy rom from file*/
    memcpy(mem->rombanks,cart->gbcart,romsize);

    /*free cart file*/
    destroy_cart_file(cart);

}

INLINE void romBankSwitch(uint16 address, uint8 value,Memory * mem){
    uint16 addr;

    switch (mem->cart->type.index){

        //MBC1
    case 0x1:case 0x2: case 0x3:
        //00 -> 01, 20 -> 21 , 40 -> 41 , 60 -> 61
        addr = value&0x1F;
        addr+=(addr==0)?1:0;
        mem->cart->rombank=(mem->cart->rombank&0xE0) | addr;
        break;

        //MBC2
    case 0x5: case 0x6:
        mem->cart->rombank=value&0xF;
        break;

        //MBC3
    case 0xF: case 0x10: case 0x11:
    case 0x12: case 0x13:
        addr = value&0x7F;
        addr+=(addr==0)?1:0;
        mem->cart->rombank=value;
        break;

    default :
            break;

    }

}

INLINE void ramBankSwitch(uint16 address, uint8 value,Memory * mem){

    uint16 x,change;

    //MBC1
    /*0x1 <= index <= 0x3*/
    x= mem->cart->type.index - 0x1;
    if (x <= 0x2){

        change = value&0x3; //2 bit register

        /*if rom mode*/
        if (mem->cart->mbc1mode==0)
            mem->cart->rombank=(mem->cart->rombank&0x1F) | (change<<5);
        else
            mem->cart->rambank= change;
        return;
    }

    //MBC3
    /*0xF <= index <= 0x13*/
    x= mem->cart->type.index - 0xF;
    if (x <= 0x4){
        change = value & 0xF;
        switch(change){

            /*ram bank change*/
        case 0x0:
        case 0x1:
        case 0x2:
        case 0x3:
            mem->cart->rambank= change;
            break;

            /*rtc*/
        case 0x8:
        case 0x9:
        case 0xA:
        case 0xB:
        case 0xC:
            mem->cart->mbc3rtc=change;
            break;

        default:
            break;
        }
        return;
    }
}




INLINE void writeToIOZone(uint16 address, uint8 value,Memory * mem){

    uint16 addr;

    //FE00-FE9F   Sprite Attribute Table (OAM)
    /*FE00 <= addr <= 0xFE9F*/
    addr = address - 0xFE00;

    if (addr <= 0x9F){
        mem->OAM[addr]=value;
        return;
    }

    //FF80-FFFE   High RAM (HRAM)
    /*FF80 <= addr <= 0xFFFE*/
    addr = address - 0xFF80;
    if (addr <= 0x7E){
        mem->hram[addr]=value;
        return;
    }

    //FF00-FF7F   I/O Ports
    addr= address - 0xFF00;
    /*FF00 <= addr <= 0xFF7F*/

    if (addr <= 0x7F)
    {

        //FF04 - DIV - Divider Register (R/W)
        if (addr == 0x04)
        {
            mem->IO[addr]=0;
            mem->timer1=0;
            return;
        }

        //FF07 - TAC
        if (addr == 0x07)
        {
            mem->IO[addr]=value|0xF8;
            mem->timer2=0;
            return;
        }

        //FF0F - IF
        if (addr == 0x0F)
        {
             mem->rif=value|0xE0;
             return;
        }

        //FF44 - LY - LCDC Y-Coordinate (R)
        if (addr == 0x44)
        {
            mem->IO[addr]=0;
            return;
        }

        //FF46 - DMA - DMA Transfer and Start Address (W)
        if (addr == 0x46)
        {
            lcdDMA(value,mem);
            return;
        }

        mem->IO[addr]=value;
        return;
    }

    //FFFF  Interrupt Enable Register
    if (address == 0xFFFF)
    {
        mem->rie=value;
        return;
    }

    //echo ram
    /*F000 <= addr <= 0xFDFF*/
    addr= address - 0xF000;
    if (addr <= 0xDFF)
    {
        mem->wram[0x1000|addr] = value;
        return;
    }


}

//DMA transfer
INLINE void lcdDMA(uint8 value,Memory * mem)
{
    int i=0;
    uint16 addr = value << 8;
    for (; i < 0xA0; i++)
        writeMem(0xFE00+i, readMem(addr+i,mem),mem);
}

void destroyMemory(Memory * mem){

    if (mem->rambanks)
        free(mem->rambanks);
    mem->rambanks=NULL;

    if (mem->rombanks)
        free(mem->rombanks);
    mem->rombanks=NULL;

}
