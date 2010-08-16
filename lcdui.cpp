#include "lcdui.h"
#include <QPainter>
#include <QRgb>
#include "lcd.h"

LcdUi::LcdUi(QWidget *parent) :
    QWidget(parent)
{
    image = new QImage(160,144,QImage::Format_RGB32);
    image->fill(0);
}

LcdUi::~LcdUi()
{
    delete image;
}


void LcdUi::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.drawImage(0,0,*image,160,144);
    painter.end();
}

void LcdUi::drawBlank()
{
    image->fill(0);
    this->update();
}

void LcdUi::drawImage(RGB lcdimage[][144])
{
    for (int i=0;i<160;i++)
        for (int j=0;j<144;j++){

            image->setPixel(i,j,qRgb(lcdimage[i][j].r,lcdimage[i][j].g,lcdimage[i][j].b));
        }
    this->update();
}




