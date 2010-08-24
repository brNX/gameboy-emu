#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include "types.h"


namespace Ui {
    class MainWindow;
}

class CpuLoop;
typedef struct _Cartridge Cartridge;
typedef struct _Memory Memory;
typedef struct _LCD LCD;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
   // friend class CpuLoop;
    void fillList();
    QString parseOpcode(int index);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    CpuLoop * loop;
    Cartridge * cart;
    Memory * mem;
    LCD * lcd;
public slots:
    void renderScreen();
private slots:
    void on_runButton_clicked();
    void on_stepButton_clicked();
    void on_runtoButton_clicked();


};

#endif // MAINWINDOW_H
