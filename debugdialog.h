#ifndef DEBUGDIALOG_H
#define DEBUGDIALOG_H

#include <QDialog>

namespace Ui {
    class DebugDialog;
}

class DebugDialog : public QDialog
{
     Q_OBJECT
public:
    DebugDialog(QWidget *parent = 0);
    ~DebugDialog();
    void refreshPanels();
private:
        QString parseOpcode(int index);
protected slots:
   void closeEvent(QCloseEvent *event);

private:
   Ui::DebugDialog * ui;

};

#endif // DEBUGDIALOG_H
