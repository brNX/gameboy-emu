#include "Z80.h"
#include "memory.h"
#include "cartridge.h"

#include "lookuptables.h"

#include <cstdio>



int main()
{

        Cartridge cart;
        Memory mem;
        resetZ80(&mem);
        //read_cart_file("killer_instinct.gb",&cart);
        //read_cart_file("motocross_maniacs.gb",&cart);
        //read_cart_file("MEGANIME.GB",&cart);
        read_cart_file("super_mario_land.gb",&cart);
        parse_cart_Header(EGB,&cart);
        initMemory(&mem,&cart);
        execute(1000000);
        destroyMemory(&mem);

	return 0;
}
