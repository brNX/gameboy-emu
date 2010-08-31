#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "oamdialog.h"
#include "debugdialog.h"
#include "Z80.h"
#include "memory.h"
#include "cartridge.h"
#include "lookuptables.h"
#include "cpuloop.h"

#include <QTimer>
#include <QFileDialog>
#include <iostream>


#include <cstdio>
#include <SDL/SDL.h>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);

    running = false;
    romloaded=false;
    debug=false;

    mem = new Memory();
    lcd = new LCD();
    cart = new Cartridge();
    resetZ80(mem, lcd);

    SDL_Init(SDL_INIT_JOYSTICK | SDL_INIT_TIMER);

    printf("%i joysticks were found.\n\n", SDL_NumJoysticks() );
    printf("The names of the joysticks are:\n");

    for(int i=0; i < SDL_NumJoysticks(); i++ ) 
    {
        printf("    %s\n", SDL_JoystickName(i));
    }

    //read_cart_file("killer_instinct.gb",cart);
    //read_cart_file("motocross_maniacs.gb",cart);
    //read_cart_file("MEGANIME.GB", cart);
    //read_cart_file("Public Domain/Joypad Test V0.1 (PD).gb", cart);
    //read_cart_file("testroms/Filltest Demo (PD).gb", cart);
    //read_cart_file("testroms/RAM Function Test (PD).gb", cart);
    //read_cart_file("tetris.gb", cart);
    //read_cart_file("alleyway.gb",cart);
    /*read_cart_file("super_mario_land.gb",cart);
    //read_cart_file("zelda.gb",cart);
    //read_cart_file("drmario.gb",cart);
    parse_cart_Header(EGB, cart);
    initMemory(mem, cart);
    //for now no rom banking
    for (int i = 0; i < (2 * 16384); i++) {
        QString line=QString("%1:\tROM 0: %2\t").arg(i, 4, 16, QChar('0')).arg(gbcpu.mem->rombanks[i],2,16,QChar('0'));
        line.append(parseOpcode(i));
        ui->romList->addItem(line);
    }
    fillList();
    */

    loop = new CpuLoop(this);
    connect(loop, SIGNAL(iterationfinished()), this, SLOT(renderScreen()));

    oamdialog = NULL ;

    QTimer::singleShot( 0, this, SLOT(resizeMainwindow()) );

}

void MainWindow::resizeMainwindow()
{
    int wheight=height();
    int cheight=ui->debugBox->height();
    setMaximumHeight(wheight-cheight);
    setMinimumHeight(wheight-cheight);
    ui->debugBox->setVisible(false);
}

MainWindow::~MainWindow() {
        destroyMemory(mem);
	delete mem;
	delete lcd;
	delete cart;
	delete ui;
	SDL_Quit();

}


void MainWindow::loadRom(QString filename)
{
    if (running){
        gbcpu.forcequit=1;
        running=false;
    }

    if(romloaded){
        //TODO: cleanup
    }

    read_cart_file(filename.toStdString().c_str(),cart);
    parse_cart_Header(EGB, cart);
    initMemory(mem, cart);
    romloaded=true;


    if(debug)
    {
     debugDialog->refreshPanels();
    }
}



/********************************Slots************************************************/

void MainWindow::changeEvent(QEvent *e) {
	QMainWindow::changeEvent(e);
	switch (e->type()) {
	case QEvent::LanguageChange:
		ui->retranslateUi(this);
		break;
	default:
		break;
	}
}

void MainWindow::renderScreen() {

        //lcd enabled ?
	if (LCDC & 0x80) {
		ui->lcd->drawImage(gbcpu.lcd->display);
	} else {
		ui->lcd->drawBlank();
	}

}

void MainWindow::on_actionOpen_Rom_activated()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                       tr("Open Rom"), "",
                       tr("GB roms (*.gb);;All Files (*)"));
    if (!fileName.isEmpty())
        loadRom(fileName);
}



void MainWindow::on_runButton_clicked() {
    if(romloaded && !running){
	loop->start(QThread::NormalPriority);
        running=true;
    }
}

void MainWindow::on_stopButton_clicked() {
    if(romloaded && running){
        gbcpu.forcequit=1;
        renderScreen();
        if (debug)
        {
            debugDialog->refreshPanels();
            oamdialog->refreshPanels();
        }
        running=false;
    }
}

void MainWindow::on_stepButton_clicked() {
    if(romloaded){
	execute(1);
	renderScreen();
        debugDialog->refreshPanels();
        oamdialog->refreshPanels();
    }
}

void MainWindow::on_runtoButton_clicked() {

    if(romloaded){
        bool ok;
        uint16 address = ui->runtoEdit->text().toUInt(&ok,16);
        if(ok){
            while (PC != address){
                execute(1);
            }
            renderScreen();
            debugDialog->refreshPanels();
            oamdialog->refreshPanels();
        }
    }
}


void MainWindow::on_actionShow_Debug_Panels_toggled(bool toggled)
{

}

void MainWindow::keyPressEvent ( QKeyEvent * event )
{
    int key;
    if (!event->isAutoRepeat()){
        switch (event->key()) {

        case Qt::Key_A: key = 1; break;
        case Qt::Key_D: key = 0; break;
        case Qt::Key_S: key = 3; break;
        case Qt::Key_W: key = 2; break;
        case Qt::Key_K: key = 4; break;
        case Qt::Key_L: key = 5; break;
        case Qt::Key_N: key = 6; break;
        case Qt::Key_M: key = 7; break;

        default:
            event->ignore();
            return;
        }

        bool unset=false;

        //already set ?
        if(!(gbcpu.joypad & (1<<key)))
            unset=true;

        //set key to 0
        gbcpu.joypad &= ~(1<<key);

        //Direction or button keys?
        if (key > 3)//buttons
        {
            if ( (!(JOYP & (1<<5)) && !unset))
                interruptZ80(I_JOYPAD); //request interrupt
        }
        else //Direction
        {
            if ( (!(JOYP & (1<<4)) && !unset))
                interruptZ80(I_JOYPAD); //request interrupt
        }

    }

}

void MainWindow::keyReleaseEvent( QKeyEvent * event )
{
    int key;
    if (!event->isAutoRepeat()){
        switch (event->key()) {

        case Qt::Key_A: key = 1; break;
        case Qt::Key_D: key = 0; break;
        case Qt::Key_S: key = 3; break;
        case Qt::Key_W: key = 2; break;
        case Qt::Key_K: key = 4; break;
        case Qt::Key_L: key = 5; break;
        case Qt::Key_N: key = 6; break;
        case Qt::Key_M: key = 7; break;

        default:
            event->ignore();
            return;
        }
          gbcpu.joypad |= (1<<key);
    }
}
