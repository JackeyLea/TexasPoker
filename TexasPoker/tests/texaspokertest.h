////////////////////////////////////////
/// \author JackeyLea
/// \date 2024-01-14
/// \brief 单元测试类
////////////////////////////////////////

#ifndef TEXASPOKERTEST_H
#define TEXASPOKERTEST_H

#include <QObject>
#include <QtTest/QTest>

#include "../TexasPoker/card.h"

class TexasPokerTest : public QObject
{
    Q_OBJECT

public:
    TexasPokerTest();

private slots:
    /*
     * 检测getBrandType函数
     */
    void case_checkGetBrandType();
    /* 检测各个独立的牌型检测函数是否正常
     */
    void case_checkOnePair();
    void case_checkTwoPair();
    void case_checkThreeKind();
    void case_checkStraight();
    void case_checkFlush();
    void case_checkFullhouse();
    void case_checkFourKind();
    void case_checkA();
    /* 检测牌型判断是否正常
     * 高牌无法独立判断
     * 同花顺由同花和顺子共同判断
     * 皇家同花顺由A、同花、顺子共同判断
     */
    void case_checkBrandType();
    /*
     * 检测牌型对比功能是否正常
     */
    //void case_CardsCompare();

private:
    //高牌
    Cards c0;
    //一对
    Cards c1;
    //两对
    Cards c2;
    //三条
    Cards c3;
    //顺子
    Cards c4;
    //同花
    Cards c5;
    //葫芦
    Cards c6;
    //四条
    Cards c7;
    //同花顺
    Cards c8;
    //皇家同花顺
    Cards c9;
};

#endif // TEXASPOKERTEST_H
