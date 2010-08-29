#include "background.h"

#include <QPainter>
#include <QPaintEvent>
#include <QRgb>
#include <QBrush>



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

    for (int i=0;i<32;i++)
        for (int j=0;j<32;j++){

    }

    this->update();
}
