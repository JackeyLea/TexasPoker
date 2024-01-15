#ifndef MYTEST_H
#define MYTEST_H

#include <QObject>
#include <QtTest>
#include "../texaspoker/poker.h"

class MyTest : public QObject
{
    Q_OBJECT

private slots:
    void case_checkBrandType();
    void case_checkFlush();
    void case_checkA();
    void case_checkStraight();
    void case_checkFourKind();
    void case_checkThreeKind();
    void case_checkFullHouse();
    void case_checkTwoPair();
    void case_checkOnePair();
};

#endif // MYTEST_H
