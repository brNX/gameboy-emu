#ifndef LCDUI_H
#define LCDUI_H

#include <QWidget>
#include <QImage>

typedef struct _RGB RGB;

class LcdUi : public QWidget
{
Q_OBJECT
public:
    explicit LcdUi(QWidget *parent = 0);
    ~LcdUi();
    void drawBlank();
    void drawImage(RGB lcdimage [][144]);


protected:
    void paintEvent(QPaintEvent *event);

private:
        QImage * image;

};

#endif // LCDUI_H
