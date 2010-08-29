#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QKeyEvent>
#include "types.h"


namespace Ui {
    class MainWindow;
}

class CpuLoop;
class OamDialog;

typedef struct _Cartridge Cartridge;
typedef struct _Memory Memory;
typedef struct _LCD LCD;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void fillList();
    QString parseOpcode(int index);

protected:
    void changeEvent(QEvent *e);
    void keyPressEvent ( QKeyEvent * event );
    void keyReleaseEvent( QKeyEvent * event );

private:
    Ui::MainWindow *ui;
    CpuLoop * loop;
    Cartridge * cart;
    Memory * mem;
    LCD * lcd;
    OamDialog * oamdialog;
public slots:
    void renderScreen();
private slots:
    void on_runButton_clicked();
    void on_stopButton_clicked();
    void on_stepButton_clicked();
    void on_runtoButton_clicked();



};

#endif // MAINWINDOW_H
