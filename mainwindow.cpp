#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Z80.h"
#include "memory.h"
#include "cartridge.h"
#include "lookuptables.h"
#include "cpuloop.h"
#include <cstdio>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mem = new Memory();
    lcd = new LCD();
    cart = new Cartridge();
}

MainWindow::~MainWindow()
{
    destroyMemory(mem);
    delete mem;
    delete lcd;
    delete cart;
    delete ui;

}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::renderScreen()
{
    /*QPainter painter;
    painter.begin(ui->lcd);
    painter.drawImage(0,0,*image,160,144);
    */
    //lcd enabled ?
    if (LCDC & 0x80){
        ui->lcd->drawImage(gbcpu.lcd->display);
    }else{
        ui->lcd->drawBlank();
    }
}

void MainWindow::mainloop(){
    //cpucycles between lcd interupts =~ 69905
    resetZ80(mem,lcd);

    //read_cart_file("killer_instinct.gb",&cart);
    //read_cart_file("motocross_maniacs.gb",&cart);
    read_cart_file("MEGANIME.GB",cart);
    //read_cart_file("super_mario_land.gb",&cart);
    parse_cart_Header(EGB,cart);
    initMemory(mem,cart);

    loop = new CpuLoop(this);
    connect(loop,SIGNAL(iterationfinished()),this,SLOT(renderScreen()));

    loop->start(QThread::LowPriority);



    /*for(int i=0;i<20000;i++){
        execute(69905);
        renderScreen();
        //sleep
    }*/
}

void MainWindow::on_runButton_clicked()
{
    mainloop();
}
