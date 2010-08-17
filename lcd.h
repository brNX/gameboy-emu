#ifndef LCD_H
#define LCD_H

#include "types.h"

typedef struct _RGB{
    int r;
    int g;
    int b;
}RGB;

typedef struct _LCD{
    int scanlinecyclecounter;
    RGB display[160][144];
}LCD;

enum COLOR {WHITE,LGRAY,DGRAY,BLACK};

INLINE void drawScanline();
INLINE void drawBG();
INLINE void drawSprites();

INLINE RGB getColor(int number,int mode);


#endif // LCD_H
