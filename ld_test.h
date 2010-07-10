#ifndef LD_TEST_H
#define LD_TEST_H

#include <QtTest/QtTest>
#include <QtDebug>
#include "cartridge.h"

class LD_Test : public QObject
{
Q_OBJECT
private slots:
    void initTestCase();

    void ADD_HL_SS();

    void ADD_HL_SS_CARRY();

    void ADD_SP_n();

    void BIT_N_R();

    void benchmemoryRange();

    void cleanupTestCase();
private :
        Cartridge cart;

};

#endif // LD_TEST_H
