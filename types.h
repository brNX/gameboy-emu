#ifndef TYPES_H
#define TYPES_H

#ifdef _MSC_VER
// Define it from MSVC's internal type
typedef unsigned __int8 uint8;
typedef unsigned __int16 uint16;
typedef unsigned __int32 uint32;
typedef __int8 int8;
typedef __int16 int16;
typedef __int32 int32;
#else
#include <stdint.h>		// Use the C99 official header
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef int8_t  int8;
typedef int16_t int16;
typedef int32_t int32;
#endif


#endif // TYPES_H
