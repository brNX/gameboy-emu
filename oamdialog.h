#ifndef OAMDIALOG_H
#define OAMDIALOG_H

#include <QDialog>

namespace Ui {
    class OamDialog;
}

class OamDialog : public QDialog
{
    Q_OBJECT
public:
    OamDialog(QWidget *parent = 0);
    ~OamDialog();
    void refreshPanels();

protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *event);

 private:
    Ui::OamDialog * ui;

};

#endif // OAMDIALOG_H
