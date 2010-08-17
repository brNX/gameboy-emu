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

    //cpucycles between lcd interupts =~ 69905
    resetZ80(mem,lcd);

    //read_cart_file("killer_instinct.gb",cart);
    //read_cart_file("motocross_maniacs.gb",cart);
    read_cart_file("MEGANIME.GB",cart);
    //read_cart_file("super_mario_land.gb",&cart);
    parse_cart_Header(EGB,cart);
    initMemory(mem,cart);

    loop = new CpuLoop(this);
    connect(loop,SIGNAL(iterationfinished()),this,SLOT(renderScreen()));

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

    loop->start(QThread::LowPriority);
    while(!(LCDC & 0x80))
        loop->start(QThread::LowPriority);

}

void MainWindow::on_runButton_clicked()
{
    mainloop();
}

void MainWindow::on_stepButton_clicked()
{
    execute(1);
    renderScreen();
    ui->afEdit->setText(QString("%1").arg(AF,4,16,QChar('0')));
    ui->bcEdit->setText(QString("%1").arg(BC,4,16,QChar('0')));
    ui->deEdit->setText(QString("%1").arg(DE,4,16,QChar('0')));
    ui->hlEdit->setText(QString("%1").arg(HL,4,16,QChar('0')));
    ui->pcEdit->setText(QString("%1").arg(PC,4,16,QChar('0')));
    ui->spEdit->setText(QString("%1").arg(SP,4,16,QChar('0')));
    ui->zflagBox->setCheckState((F&Z_FLAG)?Qt::Checked:Qt::Unchecked);
    ui->addflagBox->setCheckState((F&N_FLAG)?Qt::Checked:Qt::Unchecked);
    ui->hcarryflagBox->setCheckState((F&H_FLAG)?Qt::Checked:Qt::Unchecked);
    ui->carryflagBox->setCheckState((F&C_FLAG)?Qt::Checked:Qt::Unchecked);
    ui->carryflagBox->setCheckState((F&C_FLAG)?Qt::Checked:Qt::Unchecked);
    ui->imeflagBox->setCheckState(IME?Qt::Checked:Qt::Unchecked);

}
