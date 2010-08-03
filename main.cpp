#include "Z80.h"
#include "memory.h"
#include "cartridge.h"

#include "lookuptables.h"

#include <cstdio>


//cpucycles between lcd interupts =~ 69905

int main()
{

        Cartridge cart;
        Memory mem;
        LCD lcd;
        resetZ80(&mem,&lcd);
        //read_cart_file("killer_instinct.gb",&cart);
        //read_cart_file("motocross_maniacs.gb",&cart);
        //read_cart_file("MEGANIME.GB",&cart);
        read_cart_file("super_mario_land.gb",&cart);
        parse_cart_Header(EGB,&cart);
        initMemory(&mem,&cart);
        for(int i=0;i<5;i++){
            execute(69905);
            //renderscreen();
            //sleep
        }

        destroyMemory(&mem);

	return 0;
}
