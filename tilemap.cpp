#include "tilemap.h"

#include <QPainter>
#include <QPaintEvent>
#include <QRgb>
#include <QBrush>

TileMap::TileMap(QWidget *parent)
{
    image = new QImage(156,430,QImage::Format_RGB32);
    image->fill(qRgb(255,255,255));

    draw(NULL);
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

void TileMap::draw(uint8 map[]){

    int x=16,y=16;

    for (int i=0 ; i<7;i++ ){
        for (int j=0;j<407;j++){
             image->setPixel(x,j,qRgb(0,0,0));
        }
        x+=17;
    }

    for (int i=0 ; i<23;i++ ){
        for (int j=0;j<135;j++){
             image->setPixel(j,y,qRgb(0,0,0));
        }
        y+=17;
    }

    QRgb value;
    for (int i=0;i<24;i++)
        for (int j=0;j<8;j++){

    }
    this->update();
}
