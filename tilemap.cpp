#include "tilemap.h"

#include <QPainter>
#include <QPaintEvent>
#include <QRgb>
#include <QBrush>
#include <cstdio>
#include <iostream>

#include "Z80.h"

TileMap::TileMap(QWidget *parent)
{
    image = new QImage(271,430,QImage::Format_RGB32);
    image->fill(qRgb(255,255,255));

   // draw();
}

TileMap::~TileMap(){
    delete image;
}


void TileMap::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.drawImage(QPoint(0,0),*image);
    painter.end();
}

void TileMap::draw(){

    int x=16,y=16;


    for (int i=0 ; i<15;i++ ){
        for (int j=0;j<407;j++){
            image->setPixel(x,j,qRgb(50,50,50));
        }
        x+=17;
    }

    for (int i=0 ; i<23;i++ ){
        for (int j=0;j<271;j++){
            image->setPixel(j,y,qRgb(50,50,50));
        }
        y+=17;
    }


    x=0;
    y=0;
    int address = 0;
    //16 bytes(0x10) per tile
    for(int line=0;line <24;line++){
        y=line*16+line;
        for (int row = 0 ; row <16;row++){
            x=row*16+row;


            //8 2bytes pairs
            for (int i=0,pixely=0;i<8;i++,pixely+=2){
                uint8 data1=gbcpu.mem->vram[address+i*2];
                uint8 data2=gbcpu.mem->vram[address+i*2+1];

                //8 pixels per line
                for (int j=7,pixelx=0;j>-1;j--,pixelx+=2){

                    int colorNumber = (data2 & (1<<j))?0x2:0;
                    colorNumber |= (data1 & (1<<j))?1:0;

                    QRgb value = getColor(colorNumber,0);


                    image->setPixel(x+pixelx,y+pixely,value);
                    image->setPixel(x+pixelx+1,y+pixely,value);
                    image->setPixel(x+pixelx,y+pixely+1,value);
                    image->setPixel(x+pixelx+1,y+pixely+1,value);
                }
            }
            address+=16;
        }
    }
    update();
}


INLINE QRgb TileMap::getColor(int number,int mode){
    QRgb white = qRgb(255,255,255);
    QRgb light_gray = qRgb(190,190,190);
    QRgb dark_gray = qRgb(90,90,90);
    QRgb black = qRgb(0,0,0);

    int colorindex;
    uint8 palette;

    int hi,lo;
    //white
    QRgb color=white;


    switch(number)
    {
        case 0: hi = 1 ; lo = 0 ;break ;
        case 1: hi = 3 ; lo = 2 ;break ;
        case 2: hi = 5 ; lo = 4 ;break ;
        case 3: hi = 7 ; lo = 6 ;break ;
    }

    switch(mode)
    {
        case 0: palette=BGP ;  break;
        case 1: palette=OBP0;  break;
        case 2: palette=OBP1;  break;
    }

    colorindex = (palette & (1<<hi))?0x2:0;
    colorindex |= (palette & (1<<lo))?0x1:0;

    switch(colorindex){
        //white
        case 0: break ;

        //light gray
        case 1: color=light_gray;break ;

        //dark gray
        case 2: color=dark_gray;break ;

        //black
        case 3: color=black;break ;
    }

    return color;
}
