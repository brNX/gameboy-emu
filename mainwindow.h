#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>


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

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    void mainloop();
    CpuLoop * loop;
    Cartridge * cart;
    Memory * mem;
    LCD * lcd;
public slots:
    void renderScreen();
private slots:
    void on_runButton_clicked();


};

#endif // MAINWINDOW_H
