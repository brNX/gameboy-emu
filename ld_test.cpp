#include "ld_test.h"
#include "Z80.h"
#include "memory.h"



void LD_Test::initTestCase()
{
	resetZ80();
}

void LD_Test::ADD_HL_SS()
{
	BC=0x1111;
	HL=0x4242;
	execOpcode(0x19);
	QVERIFY(HL == 0x5353);
	QVERIFY((F&N_FLAG) != N_FLAG);
	QVERIFY((F&C_FLAG) != C_FLAG);

}

void LD_Test::ADD_SP_n()
{

	execOpcode(0xE8);
	QVERIFY(1 != 2);
}

void LD_Test::cleanupTestCase()
{ qDebug("called after myFirstTest and mySecondTest"); }

QTEST_MAIN(LD_Test)
