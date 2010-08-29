#ifndef TILEMAP_H
#define TILEMAP_H

#include <QWidget>
#include <QImage>
#include "types.h"




class TileMap : public QWidget
{
    Q_OBJECT

public:
    explicit TileMap(QWidget *parent = 0);
    ~TileMap();
     void draw();

protected:
    void paintEvent(QPaintEvent *event);

private:
        QImage * image;
        INLINE RGB getColor(int,int);

};

#endif // TILEMAP_H
