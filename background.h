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
    void draw(uint8 map[]);
protected:
    void paintEvent(QPaintEvent *event);

private:
        QImage * image;
};

#endif // BACKGROUND_H
