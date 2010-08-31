#include "lcd.h"
#include "lcdui.h"
#include <QPainter>
#include <QPaintEvent>
#include <QRgb>


LcdUi::LcdUi(QWidget *parent) :
    QWidget(parent)
{
    image = new QImage(160,144,QImage::Format_RGB32);
    image->fill(qRgb(255,255,255));
}

LcdUi::~LcdUi()
{
    delete image;
}


void LcdUi::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.drawImage(QPoint(0,0),*image);
    painter.end();
}

void LcdUi::drawBlank()
{
    image->fill(qRgb(255,255,255));
    this->update();
}

void LcdUi::drawImage(RGB lcdimage[][144])
{
    QRgb value;
    for (int i=0;i<160;i++)
        for (int j=0;j<144;j++){
            value = qRgb(lcdimage[i][j].r,lcdimage[i][j].g,lcdimage[i][j].b);
            image->setPixel(i,j,value);
        }
    this->update();
}




