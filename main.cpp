#include "Z80.h"
#include "memory.h"

#include "lookuptables.h"

#include <cstdio>



int main()
{
	reg16bit af;
	reg16bit opAuxtemp;
	af.Byte.l=0;//C_FLAG;
	af.Byte.h = 0xE1;
	opAuxtemp.Word =  (af.Byte.h << 1) | ((af.Byte.l & C_FLAG) >> 4);
	opAuxtemp.Word = ((opAuxtemp.Word >> 1) | (opAuxtemp.Word << 8)) & 0x1FF;

	af.Byte.l= (opAuxtemp.Word & 0x1) << 4 ;
	af.Byte.h = opAuxtemp.Word >> 1;

	printf("A: %x F: %x\n",af.Byte.h,af.Byte.l);
	resetZ80();

        FILE *f;
        int n;

        f = fopen("memdump", "rb");
        if (f)
        {
            n = fread(gb_memory, 0x10000, 1, f);
        }
        else{
            printf("cenas\n");
        }
        execute(1000500);

	return 0;
}
