#ifndef CARTRIDGE_H_
#define CARTRIDGE_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif


uint8_t * gbcart;

int readfile(char * name);
void destroy();

#ifdef __cplusplus
}
#endif


#endif /*CARTRIDGE_H_*/
