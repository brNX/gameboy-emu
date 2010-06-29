#include "Z80.h"
#include "memory.h"
#include "lookuptables.h"
#include <cstdio>

int main()
{

	resetZ80();
	printf ("%d\n",Cycles[0xE5]);
	printf ("%d\n",Cycles[0xF1]);
	return 0;
}
