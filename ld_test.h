#ifndef LD_TEST_H
#define LD_TEST_H

#include <QtTest/QtTest>
#include <QtDebug>

class LD_Test : public QObject
{
Q_OBJECT
private slots:
    void initTestCase();

    void myFirstTest();

    void mySecondTest();

    void cleanupTestCase();
};

#endif // LD_TEST_H
