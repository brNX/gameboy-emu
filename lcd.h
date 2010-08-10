#ifndef LCD_H
#define LCD_H

#include "types.h"

typedef struct {
    int scanlinecyclecounter;
}LCD;

INLINE void drawScanline();
INLINE void drawBG();
INLINE void drawSprites();

#endif // LCD_H
