#include "oamdialog.h"
#include "ui_oamDialog.h"

OamDialog::OamDialog(QWidget *parent) :
        QDialog(parent),ui(new Ui::OamDialog){

    ui->setupUi(this);

}


OamDialog::~OamDialog()
{
    delete ui;
}

void OamDialog::refreshPanels()
{
    ui->tileMap->draw();
}

void OamDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
