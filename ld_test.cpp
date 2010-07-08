#include "ld_test.h"
#include "Z80.h"
#include "memory.h"



void LD_Test::initTestCase()
{
	resetZ80();
}

void LD_Test::ADD_HL_SS()
{
        DE=0x1111;
        HL=0x4242;
        execOpcode(0x19);
        QVERIFY(HL == 0x5353);
        QVERIFY((F&N_FLAG) != N_FLAG);
        QVERIFY((F&C_FLAG) != C_FLAG);
        printStatusZ80();

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
        printStatusZ80();

}

void LD_Test::ADD_SP_n()
{

	execOpcode(0xE8);
	QVERIFY(1 != 2);
}

void LD_Test::cleanupTestCase()
{ qDebug("called after myFirstTest and mySecondTest"); }

QTEST_MAIN(LD_Test)
