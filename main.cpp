#include "Z80.h"
#include "memory.h"
#include "cartridge.h"

#include "lookuptables.h"

#include <cstdio>


//cpucycles between lcd interupts =~ 69905

int main()
{

        uint8 teste = 0xff;
        printf("teste %u\n",teste);
        teste++;
        printf("teste %u\n",teste);
        /*Cartridge cart;
        Memory mem;
        resetZ80(&mem);
        //read_cart_file("killer_instinct.gb",&cart);
        //read_cart_file("motocross_maniacs.gb",&cart);
        //read_cart_file("MEGANIME.GB",&cart);
        read_cart_file("super_mario_land.gb",&cart);
        parse_cart_Header(EGB,&cart);
        initMemory(&mem,&cart);
        for(int i=0;i<5;i++){
            execute(69905);
            interruptZ80(I_V_BLANK);
        }

        destroyMemory(&mem);
        */
	return 0;
}
