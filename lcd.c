#include "lcd.h"
#include "Z80.h"


INLINE void drawScanline(){

    switch (LCDC & 0x1) {
    case 0:
        drawSprites();
        break;
    case 1:
        drawBG();
        break;
    }

}

INLINE void drawBG(){

}

INLINE void drawSprites(){

}
