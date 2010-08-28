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

protected:
    void paintEvent(QPaintEvent *event);
    void draw(uint8 map []);

private:
        QImage * image;
};

#endif // TILEMAP_H
