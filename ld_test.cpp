#include "ld_test.h"


void LD_Test::initTestCase()
{ qDebug("called before everything else"); }

void LD_Test::myFirstTest()
{ QVERIFY(1 == 1); }

void LD_Test::mySecondTest()
{ QVERIFY(1 != 2); }

void LD_Test::cleanupTestCase()
{ qDebug("called after myFirstTest and mySecondTest"); }

QTEST_MAIN(LD_Test)
