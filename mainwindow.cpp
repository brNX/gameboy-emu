#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Z80.h"
#include "memory.h"
#include "cartridge.h"
#include "lookuptables.h"
#include "cpuloop.h"
#include <cstdio>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);
	mem = new Memory();
	lcd = new LCD();
	cart = new Cartridge();

	//cpucycles between lcd interupts =~ 69905
	resetZ80(mem, lcd);

	//read_cart_file("killer_instinct.gb",cart);
	//read_cart_file("motocross_maniacs.gb",cart);
	read_cart_file("MEGANIME.GB", cart);
	//read_cart_file("super_mario_land.gb",&cart);
	parse_cart_Header(EGB, cart);
	initMemory(mem, cart);
        //for now no rom banking
        for (int i = 0; i < (2 * 16384); i++) {
            QString line=QString("%1:\tROM 0: %2\t").arg(i, 4, 16, QChar('0')).arg(gbcpu.mem->rombanks[i],2,16,QChar('0'));
            line.append(parseOpcode(i));
            ui->romList->addItem(line);
        }
        fillList();

	loop = new CpuLoop(this);
	connect(loop, SIGNAL(iterationfinished()), this, SLOT(renderScreen()));

}

MainWindow::~MainWindow() {
	destroyMemory( mem);
	delete mem;
	delete lcd;
	delete cart;
	delete ui;

}

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
	/*QPainter painter;
	 painter.begin(ui->lcd);
	 painter.drawImage(0,0,*image,160,144);
	 */
	//lcd enabled ?
	if (LCDC & 0x80) {
		ui->lcd->drawImage(gbcpu.lcd->display);
	} else {
		ui->lcd->drawBlank();
	}

}

void MainWindow::mainloop() {

	loop->start(QThread::LowPriority);
	while (!(LCDC & 0x80))
		loop->start(QThread::LowPriority);

}

void MainWindow::on_runButton_clicked() {
	mainloop();
}

void MainWindow::on_stepButton_clicked() {
	execute(1);
	renderScreen();
        fillList();
}

void MainWindow::fillList() {

    ui->afEdit->setText(QString("%1").arg(AF, 4, 16, QChar('0')));
    ui->bcEdit->setText(QString("%1").arg(BC, 4, 16, QChar('0')));
    ui->deEdit->setText(QString("%1").arg(DE, 4, 16, QChar('0')));
    ui->hlEdit->setText(QString("%1").arg(HL, 4, 16, QChar('0')));
    ui->pcEdit->setText(QString("%1").arg(PC, 4, 16, QChar('0')));
    ui->spEdit->setText(QString("%1").arg(SP, 4, 16, QChar('0')));

    ui->zflagBox->setCheckState((F>>7) ? Qt::Checked : Qt::Unchecked);
    ui->addflagBox->setCheckState((F & N_FLAG) ? Qt::Checked : Qt::Unchecked);
    ui->hcarryflagBox->setCheckState((F & H_FLAG) ? Qt::Checked : Qt::Unchecked);
    ui->carryflagBox->setCheckState((F & C_FLAG) ? Qt::Checked : Qt::Unchecked);
    ui->carryflagBox->setCheckState((F & C_FLAG) ? Qt::Checked : Qt::Unchecked);
    ui->imeflagBox->setCheckState(IME ? Qt::Checked : Qt::Unchecked);


    ui->lcdcBox0->setCheckState((LCDC & 1)? Qt::Checked : Qt::Unchecked);
    ui->lcdcBox1->setCheckState((LCDC &(1<<1))? Qt::Checked : Qt::Unchecked);
    ui->lcdcBox2->setCheckState((LCDC &(1<<2))? Qt::Checked : Qt::Unchecked);
    ui->lcdcBox3->setCheckState((LCDC &(1<<3))? Qt::Checked : Qt::Unchecked);
    ui->lcdcBox4->setCheckState((LCDC &(1<<4))? Qt::Checked : Qt::Unchecked);
    ui->lcdcBox5->setCheckState((LCDC &(1<<5))? Qt::Checked : Qt::Unchecked);
    ui->lcdcBox6->setCheckState((LCDC &(1<<6))? Qt::Checked : Qt::Unchecked);
    ui->lcdcBox7->setCheckState((LCDC &(1<<7))? Qt::Checked : Qt::Unchecked);

    ui->statBox2->setCheckState((STAT &(1<<2))? Qt::Checked : Qt::Unchecked);
    ui->statBox3->setCheckState((STAT &(1<<3))? Qt::Checked : Qt::Unchecked);
    ui->statBox4->setCheckState((STAT &(1<<4))? Qt::Checked : Qt::Unchecked);
    ui->statBox5->setCheckState((STAT &(1<<5))? Qt::Checked : Qt::Unchecked);
    ui->statBox6->setCheckState((STAT &(1<<6))? Qt::Checked : Qt::Unchecked);

    ui->statmodeEdit->setText(QString().number(STAT&0x3));


    ui->scyEdit->setText(QString().number(SCY));
    ui->scxEdit->setText(QString().number(SCX));
    ui->wyEdit->setText(QString().number(WY));
    ui->wxEdit->setText(QString().number(WX));
    ui->lyEdit->setText(QString().number(LY));
    ui->lycEdit->setText(QString().number(LYC));

    ui->bgpEdit->setText(QString("%1").arg(BGP, 2, 16, QChar('0')));
    ui->obp0Edit->setText(QString("%1").arg(OBP0, 2, 16, QChar('0')));
    ui->obp1Edit->setText(QString("%1").arg(OBP1, 2, 16, QChar('0')));

    ui->statEdit->setText(QString("%1").arg(STAT, 2, 16, QChar('0')));
    ui->lcdcEdit->setText(QString("%1").arg(LCDC, 2, 16, QChar('0')));

    ui->timaEdit->setText(QString("%1").arg(TIMA, 2, 16, QChar('0')));
    ui->tacEdit->setText(QString("%1").arg(TAC, 2, 16, QChar('0')));
    ui->tmaEdit->setText(QString("%1").arg(TMA, 2, 16, QChar('0')));
    ui->divEdit->setText(QString("%1").arg(DIV, 2, 16, QChar('0')));



    ui->vramList->clear();
    for (int i = 0; i < (8192); i++) {
        ui->vramList->addItem(QString("%1:\tVRAM : %2").arg(i+2*16384, 4, 16, QChar('0')).arg(gbcpu.mem->rombanks[i],2,16,QChar('0')));
    }

    ui->wramList->clear();
    for (int i = 0; i < 8192; i++) {
        ui->wramList->addItem(QString("%1:\tWRAM : %2").arg(i+0xC000, 4, 16, QChar('0')).arg(gbcpu.mem->wram[i],2,16,QChar('0')));
    }

    ui->oamList->clear();
    for (int i = 0; i <160;i++){
        ui->oamList->addItem(QString("%1:\tOAM : %2").arg(i+0xFE00, 4, 16, QChar('0')).arg(gbcpu.mem->OAM[i],2,16,QChar('0')));
    }

    ui->hramList->clear();
    for (int i = 0; i <127;i++){
        ui->hramList->addItem(QString("%1:\tHRAM : %2").arg(i+0xFF80, 4, 16, QChar('0')).arg(gbcpu.mem->hram[i],2,16,QChar('0')));
    }

    ui->romList->setCurrentRow(PC);



}

QString MainWindow::parseOpcode(int index) {

	QString opcode;

	switch (gbcpu.mem->rombanks[index]) {
	/*nop*/
	case 0x00:
	case 0x40:
	case 0x49:
	case 0x52: //LD D,D
	case 0x5B: //LD E,E
	case 0x64: //LD H,H
	case 0x6D: //LD L,L
	case 0x7F:
		opcode.append("NOP");
		break;
		/*LD r,r'*/
	case 0x41:////LD B,C
		opcode.append("LD B,C");
		break;
	case 0x42:////LD B,D
		opcode.append("LD B,D");
		break;
	case 0x43:////LD B,E
		opcode.append("LD B,E");
		break;
	case 0x44:////LD B,H
		opcode.append("LD B,H");
		break;
	case 0x45:////LD B,L
		opcode.append("LD B,L");
		break;
	case 0x47:////LD B,A
		opcode.append("LD B,A");
		break;
	case 0x48: ////LD C,B
		opcode.append("LD C,B");
		break;
	case 0x4A: ////LD C,D
		opcode.append("LD C,D");
		break;
	case 0x4B: ////LD C,E
		opcode.append("LD C,E");
		break;
	case 0x4C: ////LD C,H
		opcode.append("LD C,H");
		break;
	case 0x4D: ////LD C,L
		opcode.append("LD C,L");
		break;
	case 0x4F: ////LD C,A
		opcode.append("LD C,A");
		break;
	case 0x50: ////LD D,B
		opcode.append("LD D,B");
		break;
	case 0x51: ////LD D,C
		opcode.append("LD D,C");
		break;
	case 0x53: ////LD D,E
		opcode.append("LD D,E");
		break;
	case 0x54: ////LD D,H
		opcode.append("LD D,H");
		break;
	case 0x55: ////LD D,L
		opcode.append("LD D,L");
		break;
	case 0x57: ////LD D,A
		opcode.append("LD D,A");
		break;
	case 0x58: ////LD E,B
		opcode.append("LD E,B");
		break;
	case 0x59: ////LD E,C
		opcode.append("LD E,C");
		break;
	case 0x5A: ////LD E,D
		opcode.append("LD E,D");
		break;
	case 0x5C: ////LD E,H
		opcode.append("LD E,H");
		break;
	case 0x5D: ////LD E,L
		opcode.append("LD E,L");
		break;
	case 0x5F: ////LD E,A
		opcode.append("LD E,A");
		break;
	case 0x60: ////LD H,B
		opcode.append("LD H,B");
		break;
	case 0x61: ////LD H,C
		opcode.append("LD H,C");
		break;
	case 0x62: ////LD H,D
		opcode.append("LD H,D");
		break;
	case 0x63: ////LD H,E
		opcode.append("LD H,E");
		break;
	case 0x65: ////LD H,L
		opcode.append("LD H,L");
		break;
	case 0x67: ////LD H,A
		opcode.append("LD H,A");
		break;
	case 0x68: ////LD L,B
		opcode.append("LD L,B");
		break;
	case 0x69: ////LD L,C
		opcode.append("LD L,C");
		break;
	case 0x6A: ////LD L,D
		opcode.append("LD L,D");
		break;
	case 0x6B: ////LD L,E
		opcode.append("LD L,E");
		break;
	case 0x6C: ////LD L,H
		opcode.append("LD L,H");
		break;
	case 0x78:////LD A,B
		opcode.append("LD A,B");
		break;
	case 0x79:////LD A,C
		opcode.append("LD A,C");
		break;
	case 0x7A:////LD A,D
		opcode.append("LD A,D");
		break;
	case 0x7B:////LD A,E
		opcode.append("LD A,E");
		break;
	case 0x7C:////LD A,H
		opcode.append("LD A,H");
		break;
	case 0x7D:////LD A,L
		opcode.append("LD A,L");
		break;
		/*LD r,n*/
	case 0x06: //LD B,n
		opcode.append(QString("LD B,%1").arg(gbcpu.mem->rombanks[index + 1], 2,
				16, QChar('0')));
		break;
	case 0x0E: //LD C,n
		opcode.append(QString("LD C,%1").arg(gbcpu.mem->rombanks[index + 1], 2,
				16, QChar('0')));
		break;
	case 0x16: //LD D,n
		opcode.append(QString("LD D,%1").arg(gbcpu.mem->rombanks[index + 1], 2,
				16, QChar('0')));
		break;
	case 0x1E: //LD E,n
		opcode.append(QString("LD E,%1").arg(gbcpu.mem->rombanks[index + 1], 2,
				16, QChar('0')));
		break;
	case 0x26: //LD H,n
		opcode.append(QString("LD H,%1").arg(gbcpu.mem->rombanks[index + 1], 2,
				16, QChar('0')));
		break;
	case 0x2E: //LD L,n
		opcode.append(QString("LD L,%1").arg(gbcpu.mem->rombanks[index + 1], 2,
				16, QChar('0')));
		break;
	case 0x3E: //LD A,n
		opcode.append(QString("LD A,%1").arg(gbcpu.mem->rombanks[index + 1], 2,
				16, QChar('0')));
		break;
		/*LD r,(HL)*/
	case 0x46: //LD B,(HL)
		opcode.append("LD B,HL");
		break;
	case 0x4E: //LD C,(HL)
		opcode.append("LD C,HL");
		break;
	case 0x56: //LD D,(HL)
		opcode.append("LD D,HL");
		break;
	case 0x5E: //LD E,(HL)
		opcode.append("LD E,HL");
		break;
	case 0x66: //LD H,(HL)
		opcode.append("LD H,HL");
		break;
	case 0x6E: //LD L,(HL)
		opcode.append("LD L,HL");
		break;
	case 0x7E: //LD A,(HL)
		opcode.append("LD A,HL");
		break;
		/*LD (HL),r*/
	case 0x70: //LD (HL),B
		opcode.append("LD (HL),B");
		break;
	case 0x71://LD (HL),C
		opcode.append("LD (HL),C");
		break;
	case 0x72://LD (HL),D
		opcode.append("LD (HL),D");
		break;
	case 0x73://LD (HL),E
		opcode.append("LD (HL),E");
		break;
	case 0x74://LD (HL),H
		opcode.append("LD (HL),H");
		break;
	case 0x75://LD (HL),L
		opcode.append("LD (HL),L");
		break;
	case 0x77://LD (HL),A
		opcode.append("LD (HL),A");
		break;
		/*LD (HL), n*/
	case 0x36:
		opcode.append(QString("LD (HL),%1").arg(gbcpu.mem->rombanks[index + 1],
				2, 16, QChar('0')));
		break;
		/*LD A,(BC)*/
	case 0x0A:
		opcode.append("LD A,(BC)");
		break;
		/*LD A,(DE)*/
	case 0x1A:
		opcode.append("LD A,(DE)");
		break;
		/*LD(BC),A*/
	case 0x02:
		opcode.append("LD (BC),A");
		break;
		/*LD(DE),A*/
	case 0x12:
		opcode.append("LD (DE),A");
		break;
	case 0x3A://LDD A,(HL)
		opcode.append("LDD A,(HL)");
		break;
	case 0x32:
		opcode.append("LDD (HL),A");
		break;
	case 0xEA:
		opcode.append("LD (nn),A");
		break;
	case 0xFA:
		opcode.append("LD A,(nn)");
		break;
	case 0xE0:
		opcode.append("LD (FF00+n),A");
		break;
	case 0xF0:
		opcode.append("LD A,(FF00+n)");
		break;
	case 0xE2:
		opcode.append("LD (FF00+C),A");
		break;
	case 0xF2:
		opcode.append("LD A,(FF00+C)");
		break;
	case 0x22:
		opcode.append("LDI (HL),A");
		break;
	case 0x2A:
		opcode.append("LDI A,(HL)");
		break;
		/*LD rr,nn*/
	case 0x01://LD BC,nn
		opcode.append("LD BC,nn");
		break;
	case 0x11: //LD DE,nn
		opcode.append("LD DE,nn");
		break;
	case 0x21: //LD HL,nn
		opcode.append("LD HL,nn");
		break;
	case 0x31: //LD SP,nn
		opcode.append("LD SP,nn");
		break;
		/*  ld   SP,HL */
	case 0xF9:
		opcode.append("LD SP,HL");
		break;
		/*LD (nn),SP */
	case 0x08:
		opcode.append("LD (nn),SP");
		break;
		/*push rr*/
	case 0xF5://PUSH AF
		opcode.append("PUSH AF");
		break;
	case 0xC5://PUSH BC
		opcode.append("PUSH BC");
		break;
	case 0xD5://PUSH DE
		opcode.append("PUSH DE");
		break;
	case 0xE5://PUSH HL
		opcode.append("PUSH HL");
		break;
		/*pop  rr*/
	case 0xF1: //POP AF
		opcode.append("POP AF");
		break;
	case 0xC1: //POP BC
		opcode.append("POP BC");
		break;
	case 0xD1: //POP DE
		opcode.append("POP DE");
		break;
	case 0xE1: //POP HL
		opcode.append("POP HL");
		break;
		/*add  A,r*/
	case 0x80: //ADD A,B
		opcode.append("ADD A,B");
		break;
	case 0x81: //ADD A,C
		opcode.append("ADD A,C");
		break;
	case 0x82: //ADD A,D
		opcode.append("ADD A,D");
		break;
	case 0x83: //ADD A,E
		opcode.append("ADD A,E");
		break;
	case 0x84: //ADD A,H
		opcode.append("ADD A,H");
		break;
	case 0x85: //ADD A,L
		opcode.append("ADD A,L");
		break;
	case 0x87: //ADD A,A
		opcode.append("ADD A,A");
		break;
		/*add A,n*/
	case 0xC6:
		opcode.append("ADD A,n");
		break;
		/*add A,(HL)*/
	case 0x86:
		opcode.append("ADD A,(HL)");
		break;
		/*ADC A,r*/
	case 0x8F: //ADC A,A
		opcode.append("ADC A,A");
		break;
	case 0x88: //ADC A,B
		opcode.append("ADC A,B");
		break;
	case 0x89: //ADC A,C
		opcode.append("ADC A,C");
		break;
	case 0x8A: //ADC A,D
		opcode.append("ADC A,D");
		break;
	case 0x8B: //ADC A,E
		opcode.append("ADC A,E");
		break;
	case 0x8C: //ADC A,H
		opcode.append("ADC A,H");
		break;
	case 0x8D: //ADC A,L
		opcode.append("ADC A,L");
		break;
		/*ADC A,n*/
	case 0xCE:
		opcode.append("ADC A,n");
		break;
		/*ADC A,(HL)*/
	case 0x8E:
		opcode.append("ADC A,(HL)");
		break;
		/*SUB A,r */
	case 0x90: //SUB B
		opcode.append("SUB A,B");
		break;
	case 0x91: //SUB C
		opcode.append("SUB A,C");
		break;
	case 0x92: //SUB D
		opcode.append("SUB A,D");
		break;
	case 0x93: //SUB E
		opcode.append("SUB A,E");
		break;
	case 0x94: //SUB H
		opcode.append("SUB A,H");
		break;
	case 0x95: //SUB L
		opcode.append("SUB A,L");
		break;
	case 0x97: //SUB A
		opcode.append("SUB A,A");
		break;
		/*SUB A,(HL) */
	case 0x96:
		opcode.append("SUB A,(HL)");
		break;
		/*SUB A,n*/
	case 0xD6:
		opcode.append("SUB A,n");
		break;
		/*SBC A,r*/
	case 0x98: //SBC B
		opcode.append("SBC A,B");
		break;
	case 0x99: //SBC C
		opcode.append("SBC A,C");
		break;
	case 0x9A: //SBC D
		opcode.append("SBC A,D");
		break;
	case 0x9B: //SBC E
		opcode.append("SBC A,E");
		break;
	case 0x9C: //SBC H
		opcode.append("SBC A,H");
		break;
	case 0x9D: //SBC L
		opcode.append("SBC A,L");
		break;
	case 0x9F: //SBC A
		opcode.append("SBC A,A");
		break;
		/*SBC A,(HL) */
	case 0x9E:
		opcode.append("SBC A,(HL)");
		break;
		/*SBC A,n*/
	case 0xDE:
		opcode.append("SBC A,n");
		break;
		/*AND A,r */
	case 0xA0: //AND B
		opcode.append("AND A,B");
		break;
	case 0xA1: //AND C
		opcode.append("AND A,C");
		break;
	case 0xA2: //AND D
		opcode.append("AND A,D");
		break;
	case 0xA3: //AND E
		opcode.append("AND A,E");
		break;
	case 0xA4: //AND H
		opcode.append("AND A,H");
		break;
	case 0xA5: //AND L
		opcode.append("AND A,L");
		break;
	case 0xA7: //AND A
		opcode.append("AND A,A");
		break;
		/*AND A,(HL) */
	case 0xA6:
		opcode.append("AND A,(HL)");
		break;
		/*AND A,n*/
	case 0xE6:
		opcode.append("AND A,n");
		break;
		/*XOR A,r */
	case 0xA8: //XOR B
		opcode.append("XOR A,B");
		break;
	case 0xA9: //XOR C
		opcode.append("XOR A,C");
		break;
	case 0xAA: //XOR D
		opcode.append("XOR A,D");
		break;
	case 0xAB: //XOR E
		opcode.append("XOR A,E");
		break;
	case 0xAC: //XOR H
		opcode.append("XOR A,H");
		break;
	case 0xAD: //XOR L
		opcode.append("XOR A,L");
		break;
	case 0xAF: //XOR A
		opcode.append("XOR A,A");
		break;
		/*XOR A,(HL) */
	case 0xAE:
		opcode.append("XOR A,(HL)");
		break;
		/*XOR A,n*/
	case 0xEE:
		opcode.append("XOR A,n");
		break;
		/*OR A,r */
	case 0xB0: //OR B
		opcode.append("OR A,B");
		break;
	case 0xB1: //OR C
		opcode.append("OR A,C");
		break;
	case 0xB2: //OR D
		opcode.append("OR A,D");
		break;
	case 0xB3: //OR E
		opcode.append("OR A,E");
		break;
	case 0xB4: //OR H
		opcode.append("OR A,H");
		break;
	case 0xB5: //OR L
		opcode.append("OR A,L");
		break;
	case 0xB7: //OR A
		opcode.append("OR A,A");
		break;
		/*OR A,(HL) */
	case 0xB6:
		opcode.append("OR A,(HL)");
		break;
		/*OR A,n*/
	case 0xF6:
		opcode.append("OR A,n");
		break;
		/*CP A,r */
	case 0xB8: //CP B
		opcode.append("CP A,B");
		break;
	case 0xB9: //CP C
		opcode.append("CP A,C");
		break;
	case 0xBA: //CP D
		opcode.append("CP A,D");
		break;
	case 0xBB: //CP E
		opcode.append("CP A,E");
		break;
	case 0xBC: //CP H
		opcode.append("CP A,H");
		break;
	case 0xBD: //CP L
		opcode.append("CP A,L");
		break;
	case 0xBF: //CP A
		opcode.append("CP A,A");
		break;
		/*CP A,(HL) */
	case 0xBE:
		opcode.append("CP A,(HL)");
		break;
		/*CP A,n*/
	case 0xFE:
		opcode.append("CP A,n");
		break;
		/*INC r */
	case 0x04: //INC B
		opcode.append("INC B");
		break;
	case 0x0C: //INC C
		opcode.append("INC C");
		break;
	case 0x14: //INC D
		opcode.append("INC D");
		break;
	case 0x1C: //INC E
		opcode.append("INC E");
		break;
	case 0x24: //INC H
		opcode.append("INC H");
		break;
	case 0x2C: //INC L
		opcode.append("INC L");
		break;
	case 0x3C: //INC A
		opcode.append("INC A");
		break;
		/*INC (HL) */
	case 0x34:
		opcode.append("INC (HL)");
		break;
		/*DEC r */
	case 0x05: //DEC B
		opcode.append("DEC B");
		break;
	case 0x0D: //DEC C
		opcode.append("DEC C");
		break;
	case 0x15: //DEC D
		opcode.append("DEC D");
		break;
	case 0x1D: //DEC E
		opcode.append("DEC E");
		break;
	case 0x25: //DEC H
		opcode.append("DEC H");
		break;
	case 0x2D: //DEC L
		opcode.append("DEC L");
		break;
	case 0x3D: //DEC A
		opcode.append("DEC A");
		break;
		/*DEC (HL) */
	case 0x35:
		opcode.append("DEC (HL)");
		break;
		/*DAA */
	case 0x27:
		opcode.append("DAA");
		break;
	case 0x2F:
		opcode.append("CPL");
		break;
		/*ADD HL,rr*/
	case 0x09: //ADD HL,BC
		opcode.append("ADD HL,BC");
		break;
	case 0x19: //ADD HL,DE
		opcode.append("ADD HL,DE");
		break;
	case 0x29: //ADD HL,HL
		opcode.append("ADD HL,HL");
		break;
	case 0x39: //ADD HL,SP
		opcode.append("ADD HL,SP");
		break;
		/*ADD SP,n */
	case 0xE8:
		opcode.append("Add SP,n");
		break;
		/*INC rr*/
	case 0x03: //INC BC
		opcode.append("INC BC");
		break;
	case 0x13: //INC DE
		opcode.append("INC DE");
		break;
	case 0x23: //INC HL
		opcode.append("INC HL");
		break;
	case 0x33: //INC SP
		opcode.append("INC SP");
		break;
		/*DEC rr*/
	case 0x0B: //DEC BC
		opcode.append("DEC BC");
		break;
	case 0x1B: //DEC DE
		opcode.append("DEC DE");
		break;
	case 0x2B: //DEC HL
		opcode.append("DEC HL");
		break;
	case 0x3B: //DEC SP
		opcode.append("DEC SP");
		break;
		/*LD HL,SP+n*/
	case 0xF8:
		opcode.append("LD HL,SP+n");
		break;
	case 0x07: //RLCA
		opcode.append("RLCA");
		break;
	case 0x17: //RLA
		opcode.append("RLA");
		break;
	case 0x0F: //RRCA
		opcode.append("RRCA");
		break;
	case 0x1F: //RRA
		opcode.append("RRA");
		break;

		/*JP nn*/
	case 0xC3:
		opcode.append("JP nn");
		break;
		/* JP (HL) */
	case 0xE9:
		opcode.append("JP (HL)");
		break;
		/*JP cc,nn*/
	case 0xC2: //JP  NZ,nn
		opcode.append("JP NZ,nn");
		break;
	case 0xCA: //JP  Z,nn
		opcode.append("JP Z,nn");
		break;
	case 0xD2: //JP  NC,nn
		opcode.append("JP NC,nn");
		break;
	case 0xDA: //JP  C,nn
		opcode.append("JP C,nn");
		break;
		/*JR PC+dd*/
	case 0x18:
		opcode.append("JP PC+dd");
		break;
		/*JR   f,PC+dd*/
	case 0x20://JR NZ,dd
		opcode.append("JP NZ,PC+dd");
		break;
	case 0x28://JR Z,dd
		opcode.append("JP Z,PC+dd");
		break;
	case 0x30://JR NC,dd
		opcode.append("JP NC,PC+dd");
		break;
	case 0x38://JR C,dd
		opcode.append("JP C,PC+dd");
		break;
	case 0xCD:
		opcode.append("CALL nn");
		break;
	case 0xC4://CALL NZ,nn
		opcode.append("CALL NZ,nn");
		break;
	case 0xCC://CALL Z,nn
		opcode.append("CALL Z,nn");
		break;
	case 0xD4://CALL NC,nn
		opcode.append("CALL NC,nn");
		break;
	case 0xDC://CALL C,nn
		opcode.append("CALL C,nn");
		break;
		/*RET*/
	case 0xC9:
		opcode.append("RET");
		break;
		/*RET cc*/
	case 0xC0://RET NZ
		opcode.append("RET NZ");
		break;
	case 0xC8://RET Z
		opcode.append("RET Z");
		break;
	case 0xD0://RET NC
		opcode.append("RET NC");
		break;
	case 0xD8://RET C
		opcode.append("RET C");
		break;
		/*RETI*/
	case 0xD9:
		opcode.append("RETI");
		break;
		/*RST n*/
	case 0xC7://RST 0x0
		opcode.append("RST 0x0");
		break;
	case 0xD7://RST 0x10
		opcode.append("RST 0x10");
		break;
	case 0xDF://RST 0x18
		opcode.append("RST 0x18");
		break;
	case 0xE7://RST 0x20
		opcode.append("RST 0x20");
		break;
	case 0xEF://RST 0x28
		opcode.append("RST 0x28");
		break;
	case 0xF7://RST 0x30
		opcode.append("RST 0x30");
		break;
	case 0xFF://RST 0x38
		opcode.append("RST 0x38");
		break;
	case 0xCF://RST 0x8
		opcode.append("RST 0x8");
		break;
	case 0x3F: //CCF
		opcode.append("CCF");
		break;
	case 0x37: //SCF
		opcode.append("SCF");
		break;
	case 0x76://HALT
		opcode.append("HALT");
		break;
	case 0x10://STOP
		opcode.append("STOP");
		break;
	case 0xF3: //DI
		opcode.append("DI");
		break;
	case 0xFB: //EI
		opcode.append("EI");
		break;

	case 0xCB:
		int NOpCode = gbcpu.mem->rombanks[index + 1];
		switch (NOpCode) {
		/*RLC  r*/
		case 0x00: //RLC B
			opcode.append("RLC B");
			break;
		case 0x01://RLC C
			opcode.append("RLC C");
			break;
		case 0x02://RLC D
			opcode.append("RLC D");
			break;
		case 0x03://RLC E
			opcode.append("RLC E");
			break;
		case 0x04://RLC H
			opcode.append("RLC H");
			break;
		case 0x05://RLC L
			opcode.append("RLC L");
			break;
		case 0x06://RLC (HL)
			opcode.append("RLC (HL)");
			break;
		case 0x07: //RLC A
			opcode.append("RLC A");
			break;
			/*RL   r*/
		case 0x10: //RL B
			opcode.append("RL B");
			break;
		case 0x11://RL C
			opcode.append("RL C");
			break;
		case 0x12://RL D
			opcode.append("RL D");
			break;
		case 0x13://RL E
			opcode.append("RL E");
			break;
		case 0x14://RL H
			opcode.append("RL H");
			break;
		case 0x15://RL L
			opcode.append("RL L");
			break;
		case 0x16://RL (HL)
			opcode.append("RL (HL)");
			break;
		case 0x17://RL A
			opcode.append("RL A");
			break;
			/*RRC r*/
		case 0x08: //RRC B
			opcode.append("RRC B");
			break;
		case 0x09://RRC C
			opcode.append("RRC C");
			break;
		case 0x0A://RRC D
			opcode.append("RRC D");
			break;
		case 0x0B://RRC E
			opcode.append("RRC E");
			break;
		case 0x0C://RRC H
			opcode.append("RRC H");
			break;
		case 0x0D://RRC L
			opcode.append("RRC L");
			break;
		case 0x0E://RRC (HL)
			opcode.append("RRC (HL)");
			break;
		case 0x0F: //RRC A
			opcode.append("RRC A");
			break;
			/*RR r*/
		case 0x18: //RR B
			opcode.append("RR B");
			break;
		case 0x19://RR C
			opcode.append("RR C");
			break;
		case 0x1A://RR D
			opcode.append("RR D");
			break;
		case 0x1B://RR E
			opcode.append("RR E");
			break;
		case 0x1C://RR H
			opcode.append("RR H");
			break;
		case 0x1D://RR L
			opcode.append("RR L");
			break;
		case 0x1E://RR (HL)
			opcode.append("RR (HL)");
			break;
		case 0x1F: //RR A
			opcode.append("RR A");
			break;
			/*SLA r*/
		case 0x20: //SLA B
			opcode.append("SLA B");
			break;
		case 0x21://SLA C
			opcode.append("SLA C");
			break;
		case 0x22://SLA D
			opcode.append("SLA D");
			break;
		case 0x23://SLA E
			opcode.append("SLA E");
			break;
		case 0x24://SLA H
			opcode.append("SLA H");
			break;
		case 0x25://SLA L
			opcode.append("SLA L");
			break;
		case 0x26://SLA (HL)
			opcode.append("SLA (HL)");
			break;
		case 0x27: //SLA A
			opcode.append("SLA A");
			break;
			/*SRA r*/
		case 0x28: //SRA B
			opcode.append("SRA B");
			break;
		case 0x29://SRA C
			opcode.append("SRA C");
			break;
		case 0x2A://SRA D
			opcode.append("SRA D");
			break;
		case 0x2B://SRA E
			opcode.append("SRA E");
			break;
		case 0x2C://SRA H
			opcode.append("SRA H");
			break;
		case 0x2D://SRA L
			opcode.append("SRA L");
			break;
		case 0x2E://SRA (HL)
			opcode.append("SRA (HL)");
			break;
		case 0x2F: //SRA A
			opcode.append("SRA A");
			break;
			/*SRL r*/
		case 0x38: //SRL B
			opcode.append("SRL B");
			break;
		case 0x39://SRL C
			opcode.append("SRL C");
			break;
		case 0x3A://SRL D
			opcode.append("SRL D");
			break;
		case 0x3B://SRL E
			opcode.append("SRL E");
			break;
		case 0x3C://SRL H
			opcode.append("SRL H");
			break;
		case 0x3D://SRL L
			opcode.append("SRL L");
			break;
		case 0x3E://SRL (HL)
			opcode.append("SRL (HL)");
			break;
		case 0x3F: //SRL A
			opcode.append("SRL A");
			break;
			/*SWAP r*/
		case 0x30: //SWAP B
			opcode.append("SWAP B");
			break;
		case 0x31://SWAP C
			opcode.append("SWAP C");
			break;
		case 0x32://SWAP D
			opcode.append("SWAP D");
			break;
		case 0x33://SWAP E
			opcode.append("SWAP E");
			break;
		case 0x34://SWAP H
			opcode.append("SWAP H");
			break;
		case 0x35://SWAP L
			opcode.append("SWAP L");
			break;
		case 0x36://SWAP (HL)
			opcode.append("SWAP (HL)");
			break;
		case 0x37: //SWAP A
			opcode.append("SWAP A");
			break;
			/***bit opcodes**/
			/*BIT b,r*/
		case 0x40: //BIT 0,B
			opcode.append("BIT 0,B");
			break;
		case 0x41: //BIT 0,C
			opcode.append("BIT 0,C");
			break;
		case 0x42: //BIT 0,D
			opcode.append("BIT 0,D");
			break;
		case 0x43: //BIT 0,E
			opcode.append("BIT 0,E");
			break;
		case 0x44: //BIT 0,H
			opcode.append("BIT 0,H");
			break;
		case 0x45: //BIT 0,L
			opcode.append("BIT 0,L");
			break;
		case 0x47: //BIT 0,A
			opcode.append("BIT 0,A");
			break;
		case 0x48: //BIT 1,B
			opcode.append("BIT 1,B");
			break;
		case 0x49: //BIT 1,C
			opcode.append("BIT 1,C");
			break;
		case 0x4A: //BIT 1,D
			opcode.append("BIT 1,D");
			break;
		case 0x4B: //BIT 1,E
			opcode.append("BIT 1,E");
			break;
		case 0x4C: //BIT 1,H
			opcode.append("BIT 1,H");
			break;
		case 0x4D: //BIT 1,L
			opcode.append("BIT 1,L");
			break;
		case 0x4F: //BIT 1,A
			opcode.append("BIT 1,A");
			break;
		case 0x50: //BIT 2,B
			opcode.append("BIT 2,B");
			break;
		case 0x51: //BIT 2,C
			opcode.append("BIT 2,C");
			break;
		case 0x52: //BIT 2,D
			opcode.append("BIT 2,D");
			break;
		case 0x53: //BIT 2,E
			opcode.append("BIT 2,E");
			break;
		case 0x54: //BIT 2,H
			opcode.append("BIT 2,H");
			break;
		case 0x55: //BIT 2,L
			opcode.append("BIT 2,L");
			break;
		case 0x57: //BIT 2,A
			opcode.append("BIT 2,A");
			break;
		case 0x58: //BIT 3,B
			opcode.append("BIT 3,B");
			break;
		case 0x59: //BIT 3,C
			opcode.append("BIT 3,C");
			break;
		case 0x5A: //BIT 3,D
			opcode.append("BIT 3,D");
			break;
		case 0x5B: //BIT 3,E
			opcode.append("BIT 3,E");
			break;
		case 0x5C: //BIT 3,H
			opcode.append("BIT 3,H");
			break;
		case 0x5D: //BIT 3,L
			opcode.append("BIT 3,L");
			break;
		case 0x5F: //BIT 3,A
			opcode.append("BIT 3,A");
			break;
		case 0x60: //BIT 4,B
			opcode.append("BIT 4,B");
			break;
		case 0x61: //BIT 4,C
			opcode.append("BIT 4,C");
			break;
		case 0x62: //BIT 4,D
			opcode.append("BIT 4,D");
			break;
		case 0x63: //BIT 4,E
			opcode.append("BIT 4,E");
			break;
		case 0x64: //BIT 4,H
			opcode.append("BIT 4,H");
			break;
		case 0x65: //BIT 4,L
			opcode.append("BIT 4,L");
			break;
		case 0x67: //BIT 4,A
			opcode.append("BIT 4,A");
			break;
		case 0x68: //BIT 5,B
			opcode.append("BIT 5,B");
			break;
		case 0x69: //BIT 5,C
			opcode.append("BIT 5,C");
			break;
		case 0x6A: //BIT 5,D
			opcode.append("BIT 5,D");
			break;
		case 0x6B: //BIT 5,E
			opcode.append("BIT 5,E");
			break;
		case 0x6C: //BIT 5,H
			opcode.append("BIT 5,H");
			break;
		case 0x6D: //BIT 5,L
			opcode.append("BIT 5,L");
			break;
		case 0x6F: //BIT 5,A
			opcode.append("BIT 5,A");
			break;
		case 0x70: //BIT 6,B
			opcode.append("BIT 6,B");
			break;
		case 0x71: //BIT 6,C
			opcode.append("BIT 6,C");
			break;
		case 0x72: //BIT 6,D
			opcode.append("BIT 6,D");
			break;
		case 0x73: //BIT 6,E
			opcode.append("BIT 6,E");
			break;
		case 0x74: //BIT 6,H
			opcode.append("BIT 6,H");
			break;
		case 0x75: //BIT 6,L
			opcode.append("BIT 6,L");
			break;
		case 0x77: //BIT 6,A
			opcode.append("BIT 6,A");
			break;
		case 0x78: //BIT 7,B
			opcode.append("BIT 7,B");
			break;
		case 0x79: //BIT 7,C
			opcode.append("BIT 7,C");
			break;
		case 0x7A: //BIT 7,D
			opcode.append("BIT 7,D");
			break;
		case 0x7B: //BIT 7,E
			opcode.append("BIT 7,E");
			break;
		case 0x7C: //BIT 7,H
			opcode.append("BIT 7,H");
			break;
		case 0x7D: //BIT 7,L
			opcode.append("BIT 7,L");
			break;
		case 0x7F: //BIT 7,A
			opcode.append("BIT 7,A");
			break;
		case 0x46: //BIT 0,(HL)
			opcode.append("BIT 0,(HL)");
			break;
		case 0x4E: //BIT 1,(HL)
			opcode.append("BIT 1,(HL)");
			break;
		case 0x56: //BIT 2,(HL)
			opcode.append("BIT 2,(HL)");
			break;
		case 0x5E: //BIT 3,(HL)
			opcode.append("BIT 3,(HL)");
			break;
		case 0x66: //BIT 4,(HL)
			opcode.append("BIT 4,(HL)");
			break;
		case 0x6E: //BIT 5,(HL)
			opcode.append("BIT 5,(HL)");
			break;
		case 0x76: //BIT 6,(HL)
			opcode.append("BIT 6,(HL)");
			break;
		case 0x7E: //BIT 7,(HL)
			opcode.append("BIT 7,(HL)");
			break;
		case 0xC0://SET 0,B
			opcode.append("SET 0,B");
			break;
		case 0xC1://SET 0,C
			opcode.append("SET 0,C");
			break;
		case 0xC2://SET 0,D
			opcode.append("SET 0,D");
			break;
		case 0xC3://SET 0,E
			opcode.append("SET 0,E");
			break;
		case 0xC4://SET 0,H
			opcode.append("SET 0,H");
			break;
		case 0xC5://SET 0,L
			opcode.append("SET 0,L");
			break;
		case 0xC6://SET 0,(HL)
			opcode.append("SET 0,(HL)");
			break;
		case 0xC7://SET 0,A
			opcode.append("SET 0,A");
			break;
		case 0xC8://SET 1,B
			opcode.append("SET 1,B");
			break;
		case 0xC9://SET 1,C
			opcode.append("SET 1,C");
			break;
		case 0xCA://SET 1,D
			opcode.append("SET 1,D");
			break;
		case 0xCB://SET 1,E
			opcode.append("SET 1,E");
			break;
		case 0xCC://SET 1,H
			opcode.append("SET 1,H");
			break;
		case 0xCD://SET 1,L
			opcode.append("SET 1,L");
			break;
		case 0xCE://SET 1,(HL)
			opcode.append("SET 1,(HL)");
			break;
		case 0xCF://SET 1,A
			opcode.append("SET 1,A");
			break;
		case 0xD0://SET 2,B
			opcode.append("SET 2,B");
			break;
		case 0xD1://SET 2,C
			opcode.append("SET 2,C");
			break;
		case 0xD2://SET 2,D
			opcode.append("SET 2,D");
			break;
		case 0xD3://SET 2,E
			opcode.append("SET 2,E");
			break;
		case 0xD4://SET 2,H
			opcode.append("SET 2,H");
			break;
		case 0xD5://SET 2,L
			opcode.append("SET 2,L");
			break;
		case 0xD6://SET 2,(HL)
			opcode.append("SET 2,(HL)");
			break;
		case 0xD7://SET 2,A
			opcode.append("SET 2,A");
			break;
		case 0xD8://SET 3,B
			opcode.append("SET 3,B");
			break;
		case 0xD9://SET 3,C
			opcode.append("SET 3,C");
			break;
		case 0xDA://SET 3,D
			opcode.append("SET 3,D");
			break;
		case 0xDB://SET 3,E
			opcode.append("SET 3,E");
			break;
		case 0xDC://SET 3,H
			opcode.append("SET 3,H");
			break;
		case 0xDD://SET 3,L
			opcode.append("SET 3,L");
			break;
		case 0xDE://SET 3,(HL)
			opcode.append("SET 3,(HL)");
			break;
		case 0xDF://SET 3,A
			opcode.append("SET 3,A");
			break;
		case 0xE0://SET 4,B
			opcode.append("SET 4,B");
			break;
		case 0xE1://SET 4,C
			opcode.append("SET 4,C");
			break;
		case 0xE2://SET 4,D
			opcode.append("SET 4,D");
			break;
		case 0xE3://SET 4,E
			opcode.append("SET 4,E");
			break;
		case 0xE4://SET 4,H
			opcode.append("SET 4,H");
			break;
		case 0xE5://SET 4,L
			opcode.append("SET 4,L");
			break;
		case 0xE6://SET 4,(HL)
			opcode.append("SET 4,(HL)");
			break;
		case 0xE7://SET 4,A
			opcode.append("SET 4,A");
			break;
		case 0xE8://SET 5,B
			opcode.append("SET 5,B");
			break;
		case 0xE9://SET 5,C
			opcode.append("SET 5,C");
			break;
		case 0xEA://SET 5,D
			opcode.append("SET 5,D");
			break;
		case 0xEB://SET 5,E
			opcode.append("SET 5,E");
			break;
		case 0xEC://SET 5,H
			opcode.append("SET 5,H");
			break;
		case 0xED://SET 5,L
			opcode.append("SET 5,L");
			break;
		case 0xEE://SET 5,(HL)
			opcode.append("SET 5,(HL)");
			break;
		case 0xEF://SET 5,A
			opcode.append("SET 5,A");
			break;
		case 0xF0://SET 6,B
			opcode.append("SET 6,B");
			break;
		case 0xF1://SET 6,C
			opcode.append("SET 6,C");
			break;
		case 0xF2://SET 6,D
			opcode.append("SET 6,D");
			break;
		case 0xF3://SET 6,E
			opcode.append("SET 6,E");
			break;
		case 0xF4://SET 6,H
			opcode.append("SET 6,H");
			break;
		case 0xF5://SET 6,L
			opcode.append("SET 6,L");
			break;
		case 0xF6://SET 6,(HL)
			opcode.append("SET 6,(HL)");
			break;
		case 0xF7://SET 6,A
			opcode.append("SET 6,A");
			break;
		case 0xF8://SET 7,B
			opcode.append("SET 7,B");
			break;
		case 0xF9://SET 7,C
			opcode.append("SET 7,C");
			break;
		case 0xFA://SET 7,D
			opcode.append("SET 7,D");
			break;
		case 0xFB://SET 7,E
			opcode.append("SET 7,E");
			break;
		case 0xFC://SET 7,H
			opcode.append("SET 7,H");
			break;
		case 0xFD://SET 7,L
			opcode.append("SET 7,L");
			break;
		case 0xFE://SET 7,(HL)
			opcode.append("SET 7,(HL)");
			break;
		case 0xFF://SET 7,A
			opcode.append("SET 7,A");
			break;
		case 0x80://RES 0,B
			opcode.append("RES 0,B");
			break;
		case 0x81://RES 0,C
			opcode.append("RES 0,C");
			break;
		case 0x82://RES 0,D
			opcode.append("RES 0,D");
			break;
		case 0x83://RES 0,E
			opcode.append("RES 0,E");
			break;
		case 0x84://RES 0,H
			opcode.append("RES 0,H");
			break;
		case 0x85://RES 0,L
			opcode.append("RES 0,L");
			break;
		case 0x86://RES 0,(HL)
			opcode.append("RES 0,(HL)");
			break;
		case 0x87://RES 0,A
			opcode.append("RES 0,A");
			break;
		case 0x88://RES 1,B
			opcode.append("RES 1,B");
			break;
		case 0x89://RES 1,C
			opcode.append("RES 1,C");
			break;
		case 0x8A://RES 1,D
			opcode.append("RES 1,D");
			break;
		case 0x8B://RES 1,E
			opcode.append("RES 1,E");
			break;
		case 0x8C://RES 1,H
			opcode.append("RES 1,H");
			break;
		case 0x8D://RES 1,L
			opcode.append("RES 1,L");
			break;
		case 0x8E://RES 1,(HL)
			opcode.append("RES 1,(HL)");
			break;
		case 0x8F://RES 1,A
			opcode.append("RES 1,A");
			break;
		case 0x90://RES 2,B
			opcode.append("RES 2,B");
			break;
		case 0x91://RES 2,C
			opcode.append("RES 2,C");
			break;
		case 0x92://RES 2,D
			opcode.append("RES 2,D");
			break;
		case 0x93://RES 2,E
			opcode.append("RES 2,E");
			break;
		case 0x94://RES 2,H
			opcode.append("RES 2,H");
			break;
		case 0x95://RES 2,L
			opcode.append("RES 2,L");
			break;
		case 0x96://RES 2,(HL)
			opcode.append("RES 2,(HL)");
			break;
		case 0x97://RES 2,A
			opcode.append("RES 2,A");
			break;
		case 0x98://RES 3,B
			opcode.append("RES 3,B");
			break;
		case 0x99://RES 3,C
			opcode.append("RES 3,C");
			break;
		case 0x9A://RES 3,D
			opcode.append("RES 3,D");
			break;
		case 0x9B://RES 3,E
			opcode.append("RES 3,E");
			break;
		case 0x9C://RES 3,H
			opcode.append("RES 3,H");
			break;
		case 0x9D://RES 3,L
			opcode.append("RES 3,L");
			break;
		case 0x9E://RES 3,(HL)
			opcode.append("RES 3,(HL)");
			break;
		case 0x9F://RES 3,A
			opcode.append("RES 3,A");
			break;
		case 0xA0://RES 4,B
			opcode.append("RES 4,B");
			break;
		case 0xA1://RES 4,C
			opcode.append("RES 4,C");
			break;
		case 0xA2://RES 4,D
			opcode.append("RES 4,D");
			break;
		case 0xA3://RES 4,E
			opcode.append("RES 4,E");
			break;
		case 0xA4://RES 4,H
			opcode.append("RES 4,H");
			break;
		case 0xA5://RES 4,L
			opcode.append("RES 4,L");
			break;
		case 0xA6://RES 4,(HL)
			opcode.append("RES 4,(HL)");
			break;
		case 0xA7://RES 4,A
			opcode.append("RES 4,A");
			break;
		case 0xA8://RES 5,B
			opcode.append("RES 5,B");
			break;
		case 0xA9://RES 5,C
			opcode.append("RES 5,C");
			break;
		case 0xAA://RES 5,D
			opcode.append("RES 5,D");
			break;
		case 0xAB://RES 5,E
			opcode.append("RES 5,E");
			break;
		case 0xAC://RES 5,H
			opcode.append("RES 5,H");
			break;
		case 0xAD://RES 5,L
			opcode.append("RES 5,L");
			break;
		case 0xAE://RES 5,(HL)
			opcode.append("RES 5,(HL)");
			break;
		case 0xAF://RES 5,A
			opcode.append("RES 5,A");
			break;
		case 0xB0://RES 6,B
			opcode.append("RES 6,B");
			break;
		case 0xB1://RES 6,C
			opcode.append("RES 6,C");
			break;
		case 0xB2://RES 6,D
			opcode.append("RES 6,D");
			break;
		case 0xB3://RES 6,E
			opcode.append("RES 6,E");
			break;
		case 0xB4://RES 6,H
			opcode.append("RES 6,H");
			break;
		case 0xB5://RES 6,L
			opcode.append("RES 6,L");
			break;
		case 0xB6://RES 6,(HL)
			opcode.append("RES 6,(HL)");
			break;
		case 0xB7://RES 6,A
			opcode.append("RES 6,A");
			break;
		case 0xB8://RES 7,B
			opcode.append("RES 7,B");
			break;
		case 0xB9://RES 7,C
			opcode.append("RES 7,C");
			break;
		case 0xBA://RES 7,D
			opcode.append("RES 7,D");
			break;
		case 0xBB://RES 7,E
			opcode.append("RES 7,E");
			break;
		case 0xBC://RES 7,H
			opcode.append("RES 7,H");
			break;
		case 0xBD://RES 7,L
			opcode.append("RES 7,L");
			break;
		case 0xBE://RES 7,(HL)
			opcode.append("RES 7,(HL)");
			break;
		case 0xBF://RES 7,A
			opcode.append("RES 7,A");
			break;
		default:
			break;
		}
		break;
	}
	return opcode;
}
