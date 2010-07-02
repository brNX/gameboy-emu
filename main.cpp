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


	printf ("%d\n",Cycles[0xE5]);
	printf ("%d\n",Cycles[0xF1]);
	uint8_t cenas = 250;
	uint8_t cenas2 = 70;
	printf("cenas ? : %u\n",cenas);
	uint16_t cenas3 = cenas+cenas2;
	printf("cenas ? : %u\n",cenas3);
	cenas2+=cenas;
	printf("cenas2 ? : %u\n",cenas2);
        printf("cycles: %d\n",Cycles[0xCB]);

	return 0;
}
