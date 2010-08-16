#include "cpuloop.h"
#include "Z80.h"
#include <QTime>

#define FRAMETIME 1000

CpuLoop::CpuLoop(QObject *parent):QThread(parent)
{

}

void CpuLoop::run()
{

    QTime timer;
    for(;;){
        timer.restart();
        execute(69905);
        emit iterationfinished();
        int elapsed = timer.elapsed();
        if (elapsed>0)
            this->msleep(FRAMETIME-elapsed);

    }

}
