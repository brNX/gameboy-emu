#ifndef CPULOOP_H
#define CPULOOP_H

#include <QThread>



class CpuLoop : public QThread
{
   Q_OBJECT;
public:
    CpuLoop(QObject *parent = 0);
    void run();
signals:
    void iterationfinished();
};

#endif // CPULOOP_H
