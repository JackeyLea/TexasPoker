#include "mytest.h"

//测试能否正确识别牌型
void MyTest::case_checkBrandType()
{
    Cards c1;
    c1.card[0].CardDecor=Decor::Club;
    c1.card[0].CardNum=Num_A;
    c1.card[1].CardDecor=Decor::Club;
    c1.card[1].CardNum=Num_2;
    c1.card[2].CardDecor=Decor::Diamond;
    c1.card[2].CardNum=Num_4;
    c1.card[3].CardDecor=Decor::Diamond;
    c1.card[3].CardNum=Num_8;
    c1.card[4].CardDecor=Decor::Spade;
    c1.card[4].CardNum=Num_Q;
    c1.status=None;

    QVERIFY(checkBranchType(c1)==BrandType::HighCard);
}
///测试同花
void MyTest::case_checkFlush()
{
    Cards c1;
    c1.card[0].CardDecor=Decor::Club;
    c1.card[0].CardNum=Num_A;
    c1.card[1].CardDecor=Decor::Club;
    c1.card[1].CardNum=Num_2;
    c1.card[2].CardDecor=Decor::Club;
    c1.card[2].CardNum=Num_4;
    c1.card[3].CardDecor=Decor::Club;
    c1.card[3].CardNum=Num_8;
    c1.card[4].CardDecor=Decor::Club;
    c1.card[4].CardNum=Num_Q;
    c1.status=None;

    QVERIFY(isFlush(c1)==true);
}
//测试最大是否为A
void MyTest::case_checkA()
{
    Cards c1;
    c1.card[0].CardDecor=Decor::Club;
    c1.card[0].CardNum=Num_A;
    c1.card[1].CardDecor=Decor::Club;
    c1.card[1].CardNum=Num_2;
    c1.card[2].CardDecor=Decor::Club;
    c1.card[2].CardNum=Num_4;
    c1.card[3].CardDecor=Decor::Club;
    c1.card[3].CardNum=Num_8;
    c1.card[4].CardDecor=Decor::Club;
    c1.card[4].CardNum=Num_Q;
    c1.status=None;

    QVERIFY(isA(c1)==true);
}

void MyTest::case_checkStraight()
{
    Cards c1;
    c1.card[0].CardDecor=Decor::Club;
    c1.card[0].CardNum=Num_5;
    c1.card[1].CardDecor=Decor::Club;
    c1.card[1].CardNum=Num_4;
    c1.card[2].CardDecor=Decor::Club;
    c1.card[2].CardNum=Num_6;
    c1.card[3].CardDecor=Decor::Club;
    c1.card[3].CardNum=Num_8;
    c1.card[4].CardDecor=Decor::Club;
    c1.card[4].CardNum=Num_7;
    c1.status=None;

    QVERIFY(isStraight(c1)==true);
}
//判断4条
void MyTest::case_checkFourKind()
{
    Cards c1;
    c1.card[0].CardDecor=Decor::Spade;
    c1.card[0].CardNum=Num_4;
    c1.card[1].CardDecor=Decor::Heart;
    c1.card[1].CardNum=Num_4;
    c1.card[2].CardDecor=Decor::Diamond;
    c1.card[2].CardNum=Num_4;
    c1.card[3].CardDecor=Decor::Club;
    c1.card[3].CardNum=Num_4;
    c1.card[4].CardDecor=Decor::Club;
    c1.card[4].CardNum=Num_7;
    c1.status=None;

    QVERIFY(isFourKing(c1)==true);
}
//判断三条
void MyTest::case_checkThreeKind()
{
    Cards c1;
    c1.card[0].CardDecor=Decor::Spade;
    c1.card[0].CardNum=Num_4;
    c1.card[1].CardDecor=Decor::Heart;
    c1.card[1].CardNum=Num_4;
    c1.card[2].CardDecor=Decor::Diamond;
    c1.card[2].CardNum=Num_4;
    c1.card[3].CardDecor=Decor::Club;
    c1.card[3].CardNum=Num_8;
    c1.card[4].CardDecor=Decor::Diamond;
    c1.card[4].CardNum=Num_7;
    c1.status=None;

    QVERIFY(isThreeKind(c1)==true);
}

void MyTest::case_checkFullHouse()
{
    Cards c1;
    c1.card[0].CardDecor=Decor::Spade;
    c1.card[0].CardNum=Num_4;
    c1.card[1].CardDecor=Decor::Heart;
    c1.card[1].CardNum=Num_4;
    c1.card[2].CardDecor=Decor::Diamond;
    c1.card[2].CardNum=Num_4;
    c1.card[3].CardDecor=Decor::Club;
    c1.card[3].CardNum=Num_7;
    c1.card[4].CardDecor=Decor::Diamond;
    c1.card[4].CardNum=Num_7;
    c1.status=None;

    QVERIFY(isFullHouse(c1)==true);
}

void MyTest::case_checkTwoPair()
{
    Cards c1;
    c1.card[0].CardDecor=Decor::Spade;
    c1.card[0].CardNum=Num_4;
    c1.card[1].CardDecor=Decor::Heart;
    c1.card[1].CardNum=Num_4;
    c1.card[2].CardDecor=Decor::Diamond;
    c1.card[2].CardNum=Num_9;
    c1.card[3].CardDecor=Decor::Club;
    c1.card[3].CardNum=Num_7;
    c1.card[4].CardDecor=Decor::Diamond;
    c1.card[4].CardNum=Num_7;
    c1.status=None;

    QVERIFY(isTwoPair(c1)==true);
}

void MyTest::case_checkOnePair()
{
    {
        Cards c1;
        c1.card[0].CardDecor=Decor::Spade;
        c1.card[0].CardNum=Num_4;
        c1.card[1].CardDecor=Decor::Heart;
        c1.card[1].CardNum=Num_4;
        c1.card[2].CardDecor=Decor::Diamond;
        c1.card[2].CardNum=Num_4;
        c1.card[3].CardDecor=Decor::Club;
        c1.card[3].CardNum=Num_7;
        c1.card[4].CardDecor=Decor::Diamond;
        c1.card[4].CardNum=Num_7;
        c1.status=None;

        QVERIFY(isOnePair(c1)==false);
    }

    {
        Cards c2;
        c2.card[0].CardDecor=Decor::Spade;
        c2.card[0].CardNum=Num_4;
        c2.card[1].CardDecor=Decor::Heart;
        c2.card[1].CardNum=Num_4;
        c2.card[2].CardDecor=Decor::Diamond;
        c2.card[2].CardNum=Num_9;
        c2.card[3].CardDecor=Decor::Club;
        c2.card[3].CardNum=Num_7;
        c2.card[4].CardDecor=Decor::Diamond;
        c2.card[4].CardNum=Num_7;
        c2.status=None;

        QVERIFY(isOnePair(c2)==false);
    }

    {
        Cards c2;
        c2.card[0].CardDecor=Decor::Spade;
        c2.card[0].CardNum=Num_4;
        c2.card[1].CardDecor=Decor::Heart;
        c2.card[1].CardNum=Num_4;
        c2.card[2].CardDecor=Decor::Diamond;
        c2.card[2].CardNum=Num_9;
        c2.card[3].CardDecor=Decor::Club;
        c2.card[3].CardNum=Num_8;
        c2.card[4].CardDecor=Decor::Diamond;
        c2.card[4].CardNum=Num_7;
        c2.status=None;

        QVERIFY(isOnePair(c2)==true);
    }
}
