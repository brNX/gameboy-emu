#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QWidget>
#include <QImage>
#include "types.h"

class Background : public QWidget
{
   Q_OBJECT
public:
    explicit Background(QWidget *parent = 0);
    ~Background();
    void draw();
protected:
    void paintEvent(QPaintEvent *event);

private:
        QImage * image;
        INLINE QRgb getColor(int,int);
};

#endif // BACKGROUND_H
