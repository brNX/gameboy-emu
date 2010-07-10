#include "cartridge.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Cart_mode Cart_type[] =
{
    {0x0,"ROM ONLY"},{0x13,"MBC3+RAM+BATTERY"},
    {0x01, "MBC1"},{0x15,"MBC4"},
    {0x02, "MBC1+RAM"},{0x16 ,"MBC4+RAM"},
    {0x03, "MBC1+RAM+BATTERY"},{0x17 ,"MBC4+RAM+BATTERY"},
    {0x05, "MBC2"},{0x19 ,"MBC5"},
    {0x06, "MBC2+BATTERY"},{0x1A ,"MBC5+RAM"},
    {0x08, "ROM+RAM"},{0x1B ,"MBC5+RAM+BATTERY"},
    {0x09, "ROM+RAM+BATTERY"},{0x1C ,"MBC5+RUMBLE"},
    {0x0B, "MMM01"},{0x1D ,"MBC5+RUMBLE+RAM"},
    {0x0C, "MMM01+RAM"},{0x1E ,"MBC5+RUMBLE+RAM+BATTERY"},
    {0x0D, "MMM01+RAM+BATTERY"},{0xFC ,"POCKET CAMERA"},
    {0x0F, "MBC3+TIMER+BATTERY"},{0xFD ,"BANDAI TAMA5"},
    {0x10, "MBC3+TIMER+RAM+BATTERY"},{0xFE ,"HuC3"},
    {0x11, "MBC3"},{0xFF ,"HuC1+RAM+BATTERY"},
    {0x12, "MBC3+RAM"},

};

Cart_size_mode Cart_size[] =
{
    {0x00,"32KByte (no ROM banking)",0},
    {0x01,"64KByte (4 banks)",4},
    {0x02,"128KByte (8 banks)",8},
    {0x03,"256KByte (16 banks)",16},
    {0x04,"512KByte (32 banks)",32},
    {0x05,"1MByte (64 banks)  - only 63 banks used by MBC1",64},
    {0x06,"2MByte (128 banks) - only 125 banks used by MBC1",128},
    {0x07,"4MByte (256 banks)",256},
    {0x52,"1.1MByte (72 banks)",72},
    {0x53,"1.2MByte (80 banks)",80},
    {0x54,"1.5MByte (96 banks)",96},
};


int read_cart_file(char * filename,Cartridge * cart){

FILE * file;
int filesize=0;

//abrir ficheiro e ler tamanho
file = fopen(filename, "rb");
if (file == NULL)
{
        printf("Error opening file for reading. Exiting...\n");
        return 1;
}
fseek(file, 0L, SEEK_END);
filesize = ftell(file);  //ignore EOF
fseek(file, 0L, SEEK_SET);

//ler ficheiro inteiro para array inByteArray
cart->gbcart = (uint8*) calloc(filesize, sizeof(uint8));
fread(cart->gbcart, 1, filesize, file);

printf("reading %s , filesize:%d K\n",filename,filesize/1024);

fclose(file);
return 0;

}

void destroy_cart_file(Cartridge * cart){
    free(cart->gbcart);
    cart->gbcart=NULL;
}

void initMemory(uint8 * gbmemory,Cartridge * cart){

    if (cart->size.index == 0){
    //32kb rom only
        //TODO: initialize variables
        return;
    }

    if (cart->size.index  <  0x52){
        //TODO: initialize variables
        return;
    }

    if (cart->size.index  <  0x52){
        //TODO: initialize variables
        return;
    }
}

//Parsing file
void parse_cart_Header(GBMODE mode,Cartridge * cart){
    parse_cart_Name(mode,cart);
    parse_cart_SGBCapable(cart);
    parse_cart_GBCCapable(cart);
    parse_cart_type(cart);
    parse_cart_size(cart);
    parse_cart_ramsize(cart);
    parse_cart_notimportant(cart);
}

//SGB capable ?
void parse_cart_SGBCapable(Cartridge * cart){
    cart->SGB=(cart->gbcart[0x0146]==0x03)?1:0;
    printf("SGB Capable: %d\n",(cart->gbcart[0x0146]==0x03)?1:0);
}

//GBC capable ?
void parse_cart_GBCCapable(Cartridge * cart){
     cart->GBC=(cart->gbcart[0x0143]==0x80)?1:0;
     printf("GBC Capable: %d\n",cart->GBC);
}

void parse_cart_ramsize(Cartridge * cart){
    cart->ramsize=cart->gbcart[0x0149];
    switch (cart->ramsize)
    {
    case 0:
        printf("RAM size: None\n");
        break;
    case 1:
        printf("RAM size: 2 KBytes\n");
        break;
    case 2:
        printf("RAM size: 8 KBytes\n");
        break;
    case 3:
        printf("RAM size: 32 KBytes (4 banks of 8KBytes each)\n");
        break;
    default:
        break;
    }
}

void parse_cart_type(Cartridge * cart){
    uint8 type= cart->gbcart[0x0147];
    uint8 i;
    for(i=0;i<29;i++){
        if (Cart_type[i].index==type){
            cart->type=Cart_type[i];
            printf("Type: %s\n",cart->type.Name);
            break;
        }
    }
}

void parse_cart_size(Cartridge * cart){
    uint8 type= cart->gbcart[0x0148];
    if (type<=0x7){
        cart->size=Cart_size[type];
    }else{
        cart->size=Cart_size[type-0x4A];
    }
     printf("Size : %s\n",cart->size.Name);
}

//parse name
void parse_cart_Name(GBMODE mode,Cartridge * cart){
    int i;

    switch (mode)
    {

    case (EGB):
        for (i=0;i<16;i++){
            cart->name[i]=cart->gbcart[i+0x134];
        }

        //trim
        for (i=15;i>=0;i--){
            if (cart->name[i] != 0)
                break;
            cart->name[i]='\0';
        }

        cart->name[16]='\0';
        printf("Game Name: %s\n",cart->name);
        break;

    case (EGBC):
        break;

    case (ESGB):
        break;

    default:
        printf("oi ?\n");
        break;

    }
}

//random not important info
void parse_cart_notimportant(Cartridge * cart){
    //destination
    printf("Destination : %s\n",(cart->gbcart[0x014A]==00)?"Japanese":"Non Japanese");
    printf("Version: %u\n",cart->gbcart[0x014C]);


}

