#include "lcd.h"
#include "Z80.h"


INLINE void drawScanline(){

    if (LCDC & 0x1)
        drawBG();

    if (LCDC & 0x2)
        drawSprites();


}

INLINE void drawBG(){

    int i,z;
    int useWindow = 0;
    uint8 yPos,xPos[4];
    uint16 rowPos=0,colPos[4];
    uint16 tileAddress[4];
    uint16 backgroundAddress = 0;



    //window enabled and scanline within window ?
    if ((LCDC & 0x20) && ( WY <= LY ))
    {
        yPos=SCY+LY;

        //Window Tile Map Display Select
        if(LCDC & 0x40)
            backgroundAddress=0x9C00;
        else
            backgroundAddress=0x9800;

        useWindow=1;
    }
    else //not using window

    {
        yPos=LY-WY;

        //Window Tile Map Display Select
        if(LCDC & 0x8)
            backgroundAddress=0x9C00;
        else
            backgroundAddress=0x9800;
    }

     //TODO: testing divide by 8 == multiply by 0.125
    //rowPos o current scanline (of the 8 pixels)
    rowPos = (((uint8)(yPos/8))*32);

    //draw de 160 pixels in current line (4 by 4)
    for (i=0;i<160;i=+4){

        for(z=0;z<4;z++)
            xPos[z] = i+z+SCX;

        if(useWindow){
             uint8 rWX = WX -7;

             for(z=0;z<4;z++)
                if ((i+z) >= rWX)
                    xPos[z] = (i+z) - rWX;
        }

        //TODO: testing divide by 8 == multiply by 0.125
        for(z=0;z<4;z++)
            colPos[z]=(xPos[z]/8);


        // get the tile identity number
        // which tile data are we using?
        if (LCDC & 0x10)
        {
            uint8 tilenumber;

            for(z=0;z<4;z++){
                tileAddress[z] = 0x8000 ;
                tilenumber= readMem(backgroundAddress+rowPos+colPos[z],gbcpu.mem);
                tileAddress[z]+=(tilenumber*16);
            }

        }
        else
        {
            int8 tilenumber;

            for(z=0;z<4;z++){
                tileAddress[z] = 0x8800 ;
                tilenumber= readMem(backgroundAddress+rowPos+colPos[z],gbcpu.mem);
                tileAddress[z]+=((tilenumber+128)*16);
            }

        }

        uint8 line = (yPos % 8) *2;
        uint8 data1[4];
        uint8 data2[4];

        for(z=0;z<4;z++){
            data1[z]=readMem(tileAddress[z]+line,gbcpu.mem);
            data2[z]=readMem(tileAddress[z]+line+1,gbcpu.mem);
        }

        int colorBit[4];
        int colorNumber[4];
        for(z=0;z<4;z++){

            colorBit[z] = ((xPos[z] % 8)-7)*-1;
            // combine data 2 and data 1 to get the colour id for this pixel
            colorNumber[z] = (data2[z] & (1<<colorBit[z]))?0x2:0;
            colorNumber[z] |= (data1[z] & (1<<colorBit[z]))?1:0;
        }

        //finaly get color from palette and draw
        RGB color[4];
        for(z=0;z<4;z++){
            color[z] = getColor(colorNumber[z],0);

            //draw
            gbcpu.lcd->display[i+z][LY]=color[z];

        }

    }

}



INLINE void drawSprites(){

}

//mode 0 - BGP FF47
//mode 1 - OBP0 FF48
//mode 2 - OBP1 FF49
INLINE RGB getColor(int number,int mode){

    RGB color={0,0,0};

    //TODO: finish this
    switch(mode){
    case 0:
        break;
    case 1:
        break;
    case 2:
        break;
    }
    return color;

}
