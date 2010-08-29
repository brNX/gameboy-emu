#include "cpuloop.h"
#include "Z80.h"
#include <cstdio>
#include <QTime>

#define FRAMETIME 1000/60

CpuLoop::CpuLoop(QObject *parent):QThread(parent)
{

}

void CpuLoop::run()
{

    QTime timer;
    for(;;){
        timer.restart();
        execute(70221);
        //scanline
        //execute(22850);
        emit iterationfinished();
       int elapsed = timer.elapsed();
       if (elapsed>0)
            this->msleep(FRAMETIME-elapsed);
       if(gbcpu.forcequit==1)
           break;

    }

}
