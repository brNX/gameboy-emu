#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>

namespace Ui {
    class MainWindow;
}

class CpuLoop;

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
public slots:
    void renderScreen();
private slots:
    void on_runButton_clicked();


};

#endif // MAINWINDOW_H
