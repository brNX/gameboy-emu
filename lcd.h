#ifndef LCD_H
#define LCD_H

#include "types.h"

typedef struct {
    int scanlinecyclecounter;
}LCD;

INLINE void drawScanline();

#endif // LCD_H
