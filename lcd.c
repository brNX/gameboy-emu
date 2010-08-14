#include "lcd.h"
#include "Z80.h"


INLINE void drawScanline(){

    if (LCDC & 0x1)
        drawBG();

    if (LCDC & 0x2)
        drawSprites();


}

INLINE void drawBG(){


    int useWindow = 0;
    uint8 yPos,xPos0=SCX,xPos1=SCX,xPos2=SCX,xPos3=SCX;
    uint16 rowPos=0;
    int i;


    //window enabled and scanline within window ?
    if ((LCDC & 0x20) && ( WY <= LY ))
    {
        yPos=SCY+LY;
        useWindow=1;
    }
    else //not using window

    {
        yPos=LY-WY;
    }

    //rowPos o current scanline (of the 8 pixels)
    rowPos = (((uint8)(yPos/8))*32);

    //draw de 160 pixels in current line (4 by 4)
    for (i=0;i<160;i=+4){
        xPos0 += i;
        xPos1 += i+1;
        xPos2 += i+2;
        xPos3 += i+3;


    }


}



INLINE void drawSprites(){

}
