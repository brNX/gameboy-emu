#include "background.h"

#include <QPainter>
#include <QPaintEvent>
#include <QRgb>
#include <QBrush>

#include "Z80.h"
#include <cstdio>
#include <iostream>



Background::Background(QWidget *parent)
{
    image = new QImage(256,256,QImage::Format_RGB32);
    image->fill(qRgb(255,255,255));
}

Background::~Background()
{
    delete image;
}

void Background::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.drawImage(QPoint(0,0),*image);
    painter.end();
}

void Background::draw(){

    uint16 backgroundAddress;
    uint16 tileAddress;

    //Window Tile Map Display Select
    if(LCDC & 0x8)
        backgroundAddress=0x1C00;
    else
        backgroundAddress=0x1800;


    for (int line=0,y=0;line<32;line++,y+=8){
        for (int row=0,x=0;row<32;row++,x+=8){

                if (LCDC & 0x10){
                    uint8 tilenumber;
                    tileAddress = 0x0;
                    tilenumber= gbcpu.mem->vram[backgroundAddress];
                    tileAddress+=(tilenumber*16);
                }
                else{
                    int8 tilenumber;
                    tileAddress = 0x800;
                    tilenumber= gbcpu.mem->vram[backgroundAddress];
                    tileAddress+=((tilenumber+128)*16);
                }

                //8 2bytes pairs
                for (int i=0,pixely=0;i<8;i++,pixely++){
                    uint8 data1=gbcpu.mem->vram[tileAddress+i*2];
                    uint8 data2=gbcpu.mem->vram[tileAddress+i*2+1];

                    //8 pixels per line
                    for (int j=7,pixelx=0;j>-1;j--,pixelx++){

                        int colorNumber = (data2 & (1<<j))?0x2:0;
                        colorNumber |= (data1 & (1<<j))?1:0;

                        QRgb value = getColor(colorNumber,0);

                        image->setPixel(x+pixelx,y+pixely,value);
                    }

                }
                backgroundAddress++;
        }
    }

    this->update();
}

INLINE QRgb Background::getColor(int number,int mode){
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
