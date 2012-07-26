/*
 * lockuptables.h
 *
 *  Created on: Jun 29, 2010
 *      Author: bgouveia
 */

#ifndef LOCKUPTABLES_H_
#define LOCKUPTABLES_H_

#include "Z80.h"

//numero de ciclos correspondentes a cada opcode
const static int Cycles[256] =
{
    4, 12, 8, 8, 4, 4, 8, 4, 20, 8, 8, 8, 4, 4, 8,
    4, 4, 12, 8, 8, 4, 4, 8, 4, 12, 8, 8, 8, 4, 4, 8, 4, 12, 12, 8, 8, 4,
    4, 8, 4, 12, 8, 8, 8, 4, 4, 8, 4, 12, 12, 8, 8, 12, 12, 12, 4, 12, 8,
    8, 8, 4, 4, 8, 4,

    4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4,
    4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4,
    8, 8, 8, 8, 8, 8, 4, 8, 4, 4, 4, 4, 4, 4, 8, 4,

    4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4,
    4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4,
    4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4,

    20, 12, 16, 16, 24, 16, 8, 16, 20, 16, 16, 0, 24, 24, 8, 16, 20, 12,
    16, 0, 24, 16, 8, 16, 20, 16, 16, 0, 24, 0, 8, 16, 12, 12, 8, 0, 0, 16,
    8, 16, 16, 4, 16, 0, 0, 0, 8, 16, 12, 12, 8, 4, 0, 16, 8, 16, 12, 8,
    16, 4, 0, 0, 8, 16,
};



//numero de ciclos correspondentes a cada opcode CB
const static int CyclesCB[256] =
{
    8 , 8 , 8 , 8 , 8 , 8 , 16 , 8 , 8 , 8 , 8 , 8 , 8 , 8 , 16 , 8 ,
    8 , 8 , 8 , 8 , 8 , 8 , 16 , 8 , 8 , 8 , 8 , 8 , 8 , 8 , 16 , 8 ,
    8 , 8 , 8 , 8 , 8 , 8 , 16 , 8 , 8 , 8 , 8 , 8 , 8 , 8 , 16 , 8 ,
    8 , 8 , 8 , 8 , 8 , 8 , 16 , 8 , 8 , 8 , 8 , 8 , 8 , 8 , 16 , 8 ,

    8 , 8 , 8 , 8 , 8 , 8 , 12 , 8 , 8 , 8 , 8 , 8 , 8 , 8 , 12 , 8 ,
    8 , 8 , 8 , 8 , 8 , 8 , 12 , 8 , 8 , 8 , 8 , 8 , 8 , 8 , 12 , 8 ,
    8 , 8 , 8 , 8 , 8 , 8 , 12 , 8 , 8 , 8 , 8 , 8 , 8 , 8 , 12 , 8 ,
    8 , 8 , 8 , 8 , 8 , 8 , 12 , 8 , 8 , 8 , 8 , 8 , 8 , 8 , 12 , 8 ,

    8 , 8 , 8 , 8 , 8 , 8 , 16 , 8 , 8 , 8 , 8 , 8 , 8 , 8 , 16 , 8 ,
    8 , 8 , 8 , 8 , 8 , 8 , 16 , 8 , 8 , 8 , 8 , 8 , 8 , 8 , 16 , 8 ,
    8 , 8 , 8 , 8 , 8 , 8 , 16 , 8 , 8 , 8 , 8 , 8 , 8 , 8 , 16 , 8 ,
    8 , 8 , 8 , 8 , 8 , 8 , 16 , 8 , 8 , 8 , 8 , 8 , 8 , 8 , 16 , 8 ,

    8 , 8 , 8 , 8 , 8 , 8 , 16 , 8 , 8 , 8 , 8 , 8 , 8 , 8 , 16 , 8 ,
    8 , 8 , 8 , 8 , 8 , 8 , 16 , 8 , 8 , 8 , 8 , 8 , 8 , 8 , 16 , 8 ,
    8 , 8 , 8 , 8 , 8 , 8 , 16 , 8 , 8 , 8 , 8 , 8 , 8 , 8 , 16 , 8 ,
    8 , 8 , 8 , 8 , 8 , 8 , 16 , 8 , 8 , 8 , 8 , 8 , 8 , 8 , 16 , 8 ,
};




//ZeroLookupTable
const static int ZeroLookup[256] =
{
    Z_FLAG, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0,
};

//INC r lookuptable
const static uint8 INCLookup[256] =
{
    H_FLAG|Z_FLAG, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    H_FLAG, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    H_FLAG, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    H_FLAG, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

    H_FLAG, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    H_FLAG, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    H_FLAG, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    H_FLAG, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

    H_FLAG, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    H_FLAG, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    H_FLAG, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    H_FLAG, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

    H_FLAG, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    H_FLAG, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    H_FLAG, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    H_FLAG, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

//DEC r lookuptable
const static uint8 DECLookup[256] =
{

    N_FLAG|Z_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, H_FLAG|N_FLAG,
    N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, H_FLAG|N_FLAG,
    N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, H_FLAG|N_FLAG,
    N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, H_FLAG|N_FLAG,

    N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, H_FLAG|N_FLAG,
    N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, H_FLAG|N_FLAG,
    N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, H_FLAG|N_FLAG,
    N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, H_FLAG|N_FLAG,

    N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, H_FLAG|N_FLAG,
    N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, H_FLAG|N_FLAG,
    N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, H_FLAG|N_FLAG,
    N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, H_FLAG|N_FLAG,

    N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, H_FLAG|N_FLAG,
    N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, H_FLAG|N_FLAG,
    N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, H_FLAG|N_FLAG,
    N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, N_FLAG, H_FLAG|N_FLAG,

};

const static int TACCycles[4] =
{
    1024,16,64,256,
};

#endif /* LOCKUPTABLES_H_ */
