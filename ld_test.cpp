#include "ld_test.h"
#include "Z80.h"
#include "memory.h"
#include "lookuptables.h"
#include <cstdlib>





void LD_Test::initTestCase()
{
	resetZ80();
        srand(time(NULL));
}

void LD_Test::ADD_HL_SS()
{
        DE=0x1111;
        HL=0x4242;
        execOpcode(0x19);
        QVERIFY(HL == 0x5353);
        QVERIFY((F&N_FLAG) != N_FLAG);
        QVERIFY((F&C_FLAG) != C_FLAG);
}

void LD_Test::ADD_HL_SS_CARRY()
{
        DE=0x680;
        HL=0xFF42;
        execOpcode(0x19);
        QVERIFY(HL == 0x5C2);
        QVERIFY((F&N_FLAG) != N_FLAG);
        QVERIFY((F&C_FLAG) == C_FLAG);
        QVERIFY((F&H_FLAG) == H_FLAG);
}

void LD_Test::ADD_SP_n()
{
        uint16_t temp=SP;
        gb_memory[0x100]=0xF5;
	execOpcode(0xE8);
        QVERIFY(SP == temp-11);
        temp=SP;
        gb_memory[0x100]=0x5;
        execOpcode(0xE8);
        QVERIFY(SP == temp+5);
}

void LD_Test::BIT_N_R(){
    F=0;
    B=0xF8;
    gb_memory[0x100]=0x50;
    execOpcode(0xCB);
    QVERIFY((F&Z_FLAG) == Z_FLAG);
    QVERIFY((F&N_FLAG) != N_FLAG);
    QVERIFY((F&H_FLAG) == H_FLAG);

    B=0xFC;
    execOpcode(0xCB);
    QVERIFY((F&Z_FLAG) != Z_FLAG);
    QVERIFY((F&N_FLAG) != N_FLAG);
    QVERIFY((F&H_FLAG) == H_FLAG);
}

void LD_Test::cleanupTestCase()
{ qDebug("called after myFirstTest and mySecondTest"); }

QTEST_MAIN(LD_Test)
