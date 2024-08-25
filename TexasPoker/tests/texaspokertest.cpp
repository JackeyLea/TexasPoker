#include "texaspokertest.h"

#include "../TexasPoker/card.h"

void TexasPokerTest::case_checkGetBrandType()
{
    QVERIFY(getBrandType(HighCard)=="高牌");//高牌
    QVERIFY(getBrandType(OnePair)=="一对");//高牌
    QVERIFY(getBrandType(TwoPair)=="两对");//高牌
    QVERIFY(getBrandType(ThreeOfaKind)=="三条");//高牌
    QVERIFY(getBrandType(Straight)=="顺子");//高牌
    QVERIFY(getBrandType(Flush)=="同花");//高牌
    QVERIFY(getBrandType(FullHouse)=="葫芦");//高牌
    QVERIFY(getBrandType(FourOfaKind)=="四条");//高牌
    QVERIFY(getBrandType(StraightFlush)=="同花顺");//高牌
    QVERIFY(getBrandType(RoyalFlush)=="皇家同花顺");//高牌
}

void TexasPokerTest::case_checkStraightCards()
{
    //非顺子
    Cards cards1;
    cards1.card[0].CardDecor = Diamond;
    cards1.card[0].CardNum   = Num_A;
    cards1.card[1].CardDecor = Spade;
    cards1.card[1].CardNum   = Num_9;
    cards1.card[2].CardDecor = Heart;
    cards1.card[2].CardNum   = Num_J;
    cards1.card[3].CardDecor = Club;
    cards1.card[3].CardNum   = Num_2;
    cards1.card[4].CardDecor = Diamond;
    cards1.card[4].CardNum   = Num_5;
    straightCards(cards1);
    QVERIFY(cards1.card[0].CardNum==Num_A);
    QVERIFY(cards1.card[1].CardNum==Num_J);
    QVERIFY(cards1.card[2].CardNum==Num_9);
    QVERIFY(cards1.card[3].CardNum==Num_5);
    QVERIFY(cards1.card[4].CardNum==Num_2);

    //顺子
    Cards cards2;
    cards2.card[0].CardDecor = Diamond;
    cards2.card[0].CardNum   = Num_9;
    cards2.card[1].CardDecor = Heart;
    cards2.card[1].CardNum   = Num_6;
    cards2.card[2].CardDecor = Club;
    cards2.card[2].CardNum   = Num_5;
    cards2.card[3].CardDecor = Spade;
    cards2.card[3].CardNum   = Num_7;
    cards2.card[4].CardDecor = Diamond;
    cards2.card[4].CardNum   = Num_8;
    straightCards(cards2);
    QVERIFY(cards2.card[0].CardNum==Num_9);
    QVERIFY(cards2.card[1].CardNum==Num_8);
    QVERIFY(cards2.card[2].CardNum==Num_7);
    QVERIFY(cards2.card[3].CardNum==Num_6);
    QVERIFY(cards2.card[4].CardNum==Num_5);
}

void TexasPokerTest::case_checkIsDuplicate()
{
    //不重复
    Cards cards1;
    cards1.card[0].CardDecor = Diamond;
    cards1.card[0].CardNum   = Num_9;
    cards1.card[1].CardDecor = Heart;
    cards1.card[1].CardNum   = Num_6;
    cards1.card[2].CardDecor = Club;
    cards1.card[2].CardNum   = Num_5;
    cards1.card[3].CardDecor = Spade;
    cards1.card[3].CardNum   = Num_7;
    cards1.card[4].CardDecor = Diamond;
    cards1.card[4].CardNum   = Num_8;
    QVERIFY(isDuplicate(cards1)==false);

    //重复
    Cards cards2;
    cards2.card[0].CardDecor = Diamond;
    cards2.card[0].CardNum   = Num_9;
    cards2.card[1].CardDecor = Heart;
    cards2.card[1].CardNum   = Num_6;
    cards2.card[2].CardDecor = Club;
    cards2.card[2].CardNum   = Num_5;
    cards2.card[3].CardDecor = Spade;
    cards2.card[3].CardNum   = Num_7;
    cards2.card[4].CardDecor = Diamond;
    cards2.card[4].CardNum   = Num_9;
    QVERIFY(isDuplicate(cards2)==true);
}

void TexasPokerTest::case_checkIs5()
{
    //一样
    Cards cards1;
    cards1.card[0].CardDecor = Diamond;
    cards1.card[0].CardNum   = Num_9;
    cards1.card[1].CardDecor = Heart;
    cards1.card[1].CardNum   = Num_9;
    cards1.card[2].CardDecor = Club;
    cards1.card[2].CardNum   = Num_9;
    cards1.card[3].CardDecor = Spade;
    cards1.card[3].CardNum   = Num_9;
    cards1.card[4].CardDecor = Diamond;
    cards1.card[4].CardNum   = Num_9;
    QVERIFY(is5(cards1)==true);

    //不一样
    Cards cards2;
    cards2.card[0].CardDecor = Diamond;
    cards2.card[0].CardNum   = Num_9;
    cards2.card[1].CardDecor = Heart;
    cards2.card[1].CardNum   = Num_9;
    cards2.card[2].CardDecor = Club;
    cards2.card[2].CardNum   = Num_9;
    cards2.card[3].CardDecor = Spade;
    cards2.card[3].CardNum   = Num_9;
    cards2.card[4].CardDecor = Diamond;
    cards2.card[4].CardNum   = Num_8;
    QVERIFY(is5(cards2)==false);
}

void TexasPokerTest::case_checkOnePair()
{
    //包含一对的有三条 四条 三带二 一对 两对

    //四条
    Cards c7;
    c7.card[0].CardDecor=Decor::Spade;
    c7.card[0].CardNum=Num_4;
    c7.card[1].CardDecor=Decor::Heart;
    c7.card[1].CardNum=Num_4;
    c7.card[2].CardDecor=Decor::Diamond;
    c7.card[2].CardNum=Num_4;
    c7.card[3].CardDecor=Decor::Club;
    c7.card[3].CardNum=Num_4;
    c7.card[4].CardDecor=Decor::Club;
    c7.card[4].CardNum=Num_7;
    QVERIFY(isOnePair(c7)==true);//四条

    //葫芦
    Cards c6;
    c6.card[0].CardDecor=Decor::Spade;
    c6.card[0].CardNum=Num_4;
    c6.card[1].CardDecor=Decor::Heart;
    c6.card[1].CardNum=Num_4;
    c6.card[2].CardDecor=Decor::Diamond;
    c6.card[2].CardNum=Num_4;
    c6.card[3].CardDecor=Decor::Club;
    c6.card[3].CardNum=Num_7;
    c6.card[4].CardDecor=Decor::Diamond;
    c6.card[4].CardNum=Num_7;
    QVERIFY(isOnePair(c6)==true);//葫芦测试

    //三条不能是葫芦不能是四条
    Cards c3;
    c3.card[0].CardDecor=Decor::Spade;
    c3.card[0].CardNum=Num_4;
    c3.card[1].CardDecor=Decor::Heart;
    c3.card[1].CardNum=Num_4;
    c3.card[2].CardDecor=Decor::Diamond;
    c3.card[2].CardNum=Num_4;
    c3.card[3].CardDecor=Decor::Club;
    c3.card[3].CardNum=Num_8;
    c3.card[4].CardDecor=Decor::Diamond;
    c3.card[4].CardNum=Num_7;
    QVERIFY(isOnePair(c3)==true);//三条测试

    //两对
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
    QVERIFY(isOnePair(c2)==true);//两对测试

    //一对不能含两对和葫芦
    Cards c1;
    c1.card[0].CardDecor=Decor::Spade;
    c1.card[0].CardNum=Num_4;
    c1.card[1].CardDecor=Decor::Heart;
    c1.card[1].CardNum=Num_4;
    c1.card[2].CardDecor=Decor::Diamond;
    c1.card[2].CardNum=Num_9;
    c1.card[3].CardDecor=Decor::Club;
    c1.card[3].CardNum=Num_8;
    c1.card[4].CardDecor=Decor::Diamond;
    c1.card[4].CardNum=Num_7;
    QVERIFY(isOnePair(c1)==true);//一对测试

    //高牌，什么也不是
    Cards c0;
    c0.card[0].CardDecor=Decor::Spade;
    c0.card[0].CardNum=Num_A;
    c0.card[1].CardDecor=Decor::Heart;
    c0.card[1].CardNum=Num_9;
    c0.card[2].CardDecor=Decor::Diamond;
    c0.card[2].CardNum=Num_8;
    c0.card[3].CardDecor=Decor::Club;
    c0.card[3].CardNum=Num_7;
    c0.card[4].CardDecor=Decor::Diamond;
    c0.card[4].CardNum=Num_4;
    QVERIFY(isOnePair(c0)==false);//高牌
}

void TexasPokerTest::case_checkTwoPair()
{
    ///两对
    //两对
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
    QVERIFY(isTwoPair(c2)==true);//两对测试

    ///非两对
    //四条
    Cards c7;
    c7.card[0].CardDecor=Decor::Spade;
    c7.card[0].CardNum=Num_4;
    c7.card[1].CardDecor=Decor::Heart;
    c7.card[1].CardNum=Num_4;
    c7.card[2].CardDecor=Decor::Diamond;
    c7.card[2].CardNum=Num_4;
    c7.card[3].CardDecor=Decor::Club;
    c7.card[3].CardNum=Num_4;
    c7.card[4].CardDecor=Decor::Club;
    c7.card[4].CardNum=Num_7;
    QVERIFY(isTwoPair(c7)==false);//四条

    //葫芦
    Cards c6;
    c6.card[0].CardDecor=Decor::Spade;
    c6.card[0].CardNum=Num_4;
    c6.card[1].CardDecor=Decor::Heart;
    c6.card[1].CardNum=Num_4;
    c6.card[2].CardDecor=Decor::Diamond;
    c6.card[2].CardNum=Num_4;
    c6.card[3].CardDecor=Decor::Club;
    c6.card[3].CardNum=Num_7;
    c6.card[4].CardDecor=Decor::Diamond;
    c6.card[4].CardNum=Num_7;
    QVERIFY(isTwoPair(c6)==true);//葫芦测试

    //三条不能是葫芦不能是四条
    Cards c3;
    c3.card[0].CardDecor=Decor::Spade;
    c3.card[0].CardNum=Num_4;
    c3.card[1].CardDecor=Decor::Heart;
    c3.card[1].CardNum=Num_4;
    c3.card[2].CardDecor=Decor::Diamond;
    c3.card[2].CardNum=Num_4;
    c3.card[3].CardDecor=Decor::Club;
    c3.card[3].CardNum=Num_8;
    c3.card[4].CardDecor=Decor::Diamond;
    c3.card[4].CardNum=Num_7;
    QVERIFY(isTwoPair(c3)==false);//三条测试

    //一对不能含两对和葫芦
    Cards c1;
    c1.card[0].CardDecor=Decor::Spade;
    c1.card[0].CardNum=Num_4;
    c1.card[1].CardDecor=Decor::Heart;
    c1.card[1].CardNum=Num_4;
    c1.card[2].CardDecor=Decor::Diamond;
    c1.card[2].CardNum=Num_9;
    c1.card[3].CardDecor=Decor::Club;
    c1.card[3].CardNum=Num_8;
    c1.card[4].CardDecor=Decor::Diamond;
    c1.card[4].CardNum=Num_7;
    QVERIFY(isTwoPair(c1)==false);//一对测试

    //高牌，什么也不是
    Cards c0;
    c0.card[0].CardDecor=Decor::Spade;
    c0.card[0].CardNum=Num_A;
    c0.card[1].CardDecor=Decor::Heart;
    c0.card[1].CardNum=Num_9;
    c0.card[2].CardDecor=Decor::Diamond;
    c0.card[2].CardNum=Num_8;
    c0.card[3].CardDecor=Decor::Club;
    c0.card[3].CardNum=Num_7;
    c0.card[4].CardDecor=Decor::Diamond;
    c0.card[4].CardNum=Num_4;
    QVERIFY(isTwoPair(c0)==false);//高牌
}

void TexasPokerTest::case_checkThreeKind()
{
    //包含三条 可能是三条、葫芦、四条
    //四条
    Cards cards1;
    cards1.card[0].CardDecor=Decor::Spade;
    cards1.card[0].CardNum=Num_4;
    cards1.card[1].CardDecor=Decor::Heart;
    cards1.card[1].CardNum=Num_4;
    cards1.card[2].CardDecor=Decor::Diamond;
    cards1.card[2].CardNum=Num_4;
    cards1.card[3].CardDecor=Decor::Club;
    cards1.card[3].CardNum=Num_4;
    cards1.card[4].CardDecor=Decor::Club;
    cards1.card[4].CardNum=Num_7;
    QVERIFY(isThreeKind(cards1)==true);

    //葫芦
    Cards cards2;
    cards2.card[0].CardDecor=Decor::Spade;
    cards2.card[0].CardNum=Num_4;
    cards2.card[1].CardDecor=Decor::Heart;
    cards2.card[1].CardNum=Num_4;
    cards2.card[2].CardDecor=Decor::Diamond;
    cards2.card[2].CardNum=Num_4;
    cards2.card[3].CardDecor=Decor::Club;
    cards2.card[3].CardNum=Num_7;
    cards2.card[4].CardDecor=Decor::Diamond;
    cards2.card[4].CardNum=Num_7;
    QVERIFY(isThreeKind(cards1)==true);

    //三条不能是葫芦不能是四条
    Cards cards3;
    cards3.card[0].CardDecor=Decor::Spade;
    cards3.card[0].CardNum=Num_4;
    cards3.card[1].CardDecor=Decor::Heart;
    cards3.card[1].CardNum=Num_4;
    cards3.card[2].CardDecor=Decor::Diamond;
    cards3.card[2].CardNum=Num_4;
    cards3.card[3].CardDecor=Decor::Club;
    cards3.card[3].CardNum=Num_8;
    cards3.card[4].CardDecor=Decor::Diamond;
    cards3.card[4].CardNum=Num_7;
    cards3.status=ThreeOfaKind;
    QVERIFY(isThreeKind(cards3)==true);

    //不包含三条
    //高牌，什么也不是
    Cards card4;
    card4.card[0].CardDecor=Decor::Spade;
    card4.card[0].CardNum=Num_A;
    card4.card[1].CardDecor=Decor::Heart;
    card4.card[1].CardNum=Num_9;
    card4.card[2].CardDecor=Decor::Diamond;
    card4.card[2].CardNum=Num_8;
    card4.card[3].CardDecor=Decor::Club;
    card4.card[3].CardNum=Num_7;
    card4.card[4].CardDecor=Decor::Diamond;
    card4.card[4].CardNum=Num_4;
    QVERIFY(isThreeKind(card4)==false);
}

void TexasPokerTest::case_checkStraight()
{
    //顺子
    Cards c0;
    c0.card[0].CardDecor=Decor::Spade;
    c0.card[0].CardNum=Num_5;
    c0.card[1].CardDecor=Decor::Heart;
    c0.card[1].CardNum=Num_6;
    c0.card[2].CardDecor=Decor::Diamond;
    c0.card[2].CardNum=Num_8;
    c0.card[3].CardDecor=Decor::Club;
    c0.card[3].CardNum=Num_7;
    c0.card[4].CardDecor=Decor::Diamond;
    c0.card[4].CardNum=Num_4;
    QVERIFY(isStraight(c0)==true);//顺子

    //非顺子
    Cards c1;
    c1.card[0].CardDecor=Decor::Spade;
    c1.card[0].CardNum=Num_A;
    c1.card[1].CardDecor=Decor::Heart;
    c1.card[1].CardNum=Num_9;
    c1.card[2].CardDecor=Decor::Diamond;
    c1.card[2].CardNum=Num_8;
    c1.card[3].CardDecor=Decor::Club;
    c1.card[3].CardNum=Num_7;
    c1.card[4].CardDecor=Decor::Diamond;
    c1.card[4].CardNum=Num_4;
    c1.status=HighCard;
    QVERIFY(isStraight(c1)==false);
}

//测试同花
void TexasPokerTest::case_checkFlush()
{
    //同花
    Cards cards1;
    cards1.card[0].CardDecor=Decor::Spade;
    cards1.card[0].CardNum=Num_10;
    cards1.card[1].CardDecor=Decor::Spade;
    cards1.card[1].CardNum=Num_J;
    cards1.card[2].CardDecor=Decor::Spade;
    cards1.card[2].CardNum=Num_Q;
    cards1.card[3].CardDecor=Decor::Spade;
    cards1.card[3].CardNum=Num_K;
    cards1.card[4].CardDecor=Decor::Spade;
    cards1.card[4].CardNum=Num_A;
    QVERIFY(isFlush(cards1)==true);

    //非同花
    Cards cards2;
    cards2.card[0].CardDecor=Decor::Spade;
    cards2.card[0].CardNum=Num_10;
    cards2.card[1].CardDecor=Decor::Spade;
    cards2.card[1].CardNum=Num_J;
    cards2.card[2].CardDecor=Decor::Spade;
    cards2.card[2].CardNum=Num_Q;
    cards2.card[3].CardDecor=Decor::Spade;
    cards2.card[3].CardNum=Num_K;
    cards2.card[4].CardDecor=Decor::Heart;
    cards2.card[4].CardNum=Num_A;
    QVERIFY(isFlush(cards2)==false);
}

//测试葫芦
void TexasPokerTest::case_checkFullhouse()
{
    ///葫芦
    //葫芦
    Cards c6;
    c6.card[0].CardDecor=Decor::Spade;
    c6.card[0].CardNum=Num_4;
    c6.card[1].CardDecor=Decor::Heart;
    c6.card[1].CardNum=Num_4;
    c6.card[2].CardDecor=Decor::Diamond;
    c6.card[2].CardNum=Num_4;
    c6.card[3].CardDecor=Decor::Club;
    c6.card[3].CardNum=Num_7;
    c6.card[4].CardDecor=Decor::Diamond;
    c6.card[4].CardNum=Num_7;
    QVERIFY(isFullHouse(c6)==true);//葫芦测试

    ///非葫芦
    //四条
    Cards c7;
    c7.card[0].CardDecor=Decor::Spade;
    c7.card[0].CardNum=Num_4;
    c7.card[1].CardDecor=Decor::Heart;
    c7.card[1].CardNum=Num_4;
    c7.card[2].CardDecor=Decor::Diamond;
    c7.card[2].CardNum=Num_4;
    c7.card[3].CardDecor=Decor::Club;
    c7.card[3].CardNum=Num_4;
    c7.card[4].CardDecor=Decor::Club;
    c7.card[4].CardNum=Num_7;
    QVERIFY(isFullHouse(c7)==false);//四条

    //三条不能是葫芦不能是四条
    Cards c3;
    c3.card[0].CardDecor=Decor::Spade;
    c3.card[0].CardNum=Num_4;
    c3.card[1].CardDecor=Decor::Heart;
    c3.card[1].CardNum=Num_4;
    c3.card[2].CardDecor=Decor::Diamond;
    c3.card[2].CardNum=Num_4;
    c3.card[3].CardDecor=Decor::Club;
    c3.card[3].CardNum=Num_8;
    c3.card[4].CardDecor=Decor::Diamond;
    c3.card[4].CardNum=Num_7;
    QVERIFY(isFullHouse(c3)==false);//三条测试

    //两对
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
    QVERIFY(isFullHouse(c2)==false);//两对测试

    //一对不能含两对和葫芦
    Cards c1;
    c1.card[0].CardDecor=Decor::Spade;
    c1.card[0].CardNum=Num_4;
    c1.card[1].CardDecor=Decor::Heart;
    c1.card[1].CardNum=Num_4;
    c1.card[2].CardDecor=Decor::Diamond;
    c1.card[2].CardNum=Num_9;
    c1.card[3].CardDecor=Decor::Club;
    c1.card[3].CardNum=Num_8;
    c1.card[4].CardDecor=Decor::Diamond;
    c1.card[4].CardNum=Num_7;
    QVERIFY(isFullHouse(c1)==false);//一对测试

    //高牌，什么也不是
    Cards c0;
    c0.card[0].CardDecor=Decor::Spade;
    c0.card[0].CardNum=Num_A;
    c0.card[1].CardDecor=Decor::Heart;
    c0.card[1].CardNum=Num_9;
    c0.card[2].CardDecor=Decor::Diamond;
    c0.card[2].CardNum=Num_8;
    c0.card[3].CardDecor=Decor::Club;
    c0.card[3].CardNum=Num_7;
    c0.card[4].CardDecor=Decor::Diamond;
    c0.card[4].CardNum=Num_4;
    QVERIFY(isFullHouse(c0)==false);//高牌
}

//四条
void TexasPokerTest::case_checkFourKind()
{
    //包含
    Cards c0;
    c0.card[0].CardDecor=Decor::Spade;
    c0.card[0].CardNum=Num_A;
    c0.card[1].CardDecor=Decor::Heart;
    c0.card[1].CardNum=Num_A;
    c0.card[2].CardDecor=Decor::Diamond;
    c0.card[2].CardNum=Num_A;
    c0.card[3].CardDecor=Decor::Club;
    c0.card[3].CardNum=Num_A;
    c0.card[4].CardDecor=Decor::Diamond;
    c0.card[4].CardNum=Num_4;
    QVERIFY(isFourKing(c0)==true);

    //不包含
    Cards c1;
    c1.card[0].CardDecor=Decor::Spade;
    c1.card[0].CardNum=Num_A;
    c1.card[1].CardDecor=Decor::Heart;
    c1.card[1].CardNum=Num_A;
    c1.card[2].CardDecor=Decor::Diamond;
    c1.card[2].CardNum=Num_A;
    c1.card[3].CardDecor=Decor::Club;
    c1.card[3].CardNum=Num_4;
    c1.card[4].CardDecor=Decor::Diamond;
    c1.card[4].CardNum=Num_4;
    QVERIFY(isFourKing(c1)==false);
}

//测试最大是否为A
void TexasPokerTest::case_checkA()
{
    //不包含
    Cards c0;
    c0.card[0].CardDecor=Decor::Spade;
    c0.card[0].CardNum=Num_A;
    c0.card[1].CardDecor=Decor::Heart;
    c0.card[1].CardNum=Num_A;
    c0.card[2].CardDecor=Decor::Diamond;
    c0.card[2].CardNum=Num_9;
    c0.card[3].CardDecor=Decor::Club;
    c0.card[3].CardNum=Num_8;
    c0.card[4].CardDecor=Decor::Diamond;
    c0.card[4].CardNum=Num_7;
    QVERIFY(isHighA(c0)==true);

    //包含
    Cards c1;
    c1.card[0].CardDecor=Decor::Spade;
    c1.card[0].CardNum=Num_A;
    c1.card[1].CardDecor=Decor::Heart;
    c1.card[1].CardNum=Num_9;
    c1.card[2].CardDecor=Decor::Diamond;
    c1.card[2].CardNum=Num_8;
    c1.card[3].CardDecor=Decor::Club;
    c1.card[3].CardNum=Num_7;
    c1.card[4].CardDecor=Decor::Diamond;
    c1.card[4].CardNum=Num_4;
    QVERIFY(isHighA(c1)==true);
}

void TexasPokerTest::case_checkBrandType()
{
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
    //皇家同花顺
    c9.card[0].CardDecor=Decor::Spade;
    c9.card[0].CardNum=Num_10;
    c9.card[1].CardDecor=Decor::Spade;
    c9.card[1].CardNum=Num_J;
    c9.card[2].CardDecor=Decor::Spade;
    c9.card[2].CardNum=Num_Q;
    c9.card[3].CardDecor=Decor::Spade;
    c9.card[3].CardNum=Num_K;
    c9.card[4].CardDecor=Decor::Spade;
    c9.card[4].CardNum=Num_A;
    c9.status=RoyalFlush;

    //同花顺 不能是皇家同花顺
    c8.card[0].CardDecor=Decor::Spade;
    c8.card[0].CardNum=Num_4;
    c8.card[1].CardDecor=Decor::Spade;
    c8.card[1].CardNum=Num_3;
    c8.card[2].CardDecor=Decor::Spade;
    c8.card[2].CardNum=Num_5;
    c8.card[3].CardDecor=Decor::Spade;
    c8.card[3].CardNum=Num_6;
    c8.card[4].CardDecor=Decor::Spade;
    c8.card[4].CardNum=Num_7;
    c8.status=StraightFlush;

    //四条
    c7.card[0].CardDecor=Decor::Spade;
    c7.card[0].CardNum=Num_4;
    c7.card[1].CardDecor=Decor::Heart;
    c7.card[1].CardNum=Num_4;
    c7.card[2].CardDecor=Decor::Diamond;
    c7.card[2].CardNum=Num_4;
    c7.card[3].CardDecor=Decor::Club;
    c7.card[3].CardNum=Num_4;
    c7.card[4].CardDecor=Decor::Club;
    c7.card[4].CardNum=Num_7;
    c7.status=FourOfaKind;

    //葫芦
    c6.card[0].CardDecor=Decor::Spade;
    c6.card[0].CardNum=Num_4;
    c6.card[1].CardDecor=Decor::Heart;
    c6.card[1].CardNum=Num_4;
    c6.card[2].CardDecor=Decor::Diamond;
    c6.card[2].CardNum=Num_4;
    c6.card[3].CardDecor=Decor::Club;
    c6.card[3].CardNum=Num_7;
    c6.card[4].CardDecor=Decor::Diamond;
    c6.card[4].CardNum=Num_7;
    c6.status=FullHouse;

    //同花 不能是顺子 不能是皇家同花顺
    c5.card[0].CardDecor=Decor::Heart;
    c5.card[0].CardNum=Num_2;
    c5.card[1].CardDecor=Decor::Heart;
    c5.card[1].CardNum=Num_4;
    c5.card[2].CardDecor=Decor::Heart;
    c5.card[2].CardNum=Num_8;
    c5.card[3].CardDecor=Decor::Heart;
    c5.card[3].CardNum=Num_K;
    c5.card[4].CardDecor=Decor::Heart;
    c5.card[4].CardNum=Num_Q;
    c5.status=Flush;

    //顺子不能是同花、不能是皇家同花顺
    c4.card[0].CardDecor=Decor::Club;
    c4.card[0].CardNum=Num_5;
    c4.card[1].CardDecor=Decor::Heart;
    c4.card[1].CardNum=Num_4;
    c4.card[2].CardDecor=Decor::Spade;
    c4.card[2].CardNum=Num_6;
    c4.card[3].CardDecor=Decor::Diamond;
    c4.card[3].CardNum=Num_8;
    c4.card[4].CardDecor=Decor::Club;
    c4.card[4].CardNum=Num_7;
    c4.status=Straight;

    //三条不能是葫芦不能是四条
    c3.card[0].CardDecor=Decor::Spade;
    c3.card[0].CardNum=Num_4;
    c3.card[1].CardDecor=Decor::Heart;
    c3.card[1].CardNum=Num_4;
    c3.card[2].CardDecor=Decor::Diamond;
    c3.card[2].CardNum=Num_4;
    c3.card[3].CardDecor=Decor::Club;
    c3.card[3].CardNum=Num_8;
    c3.card[4].CardDecor=Decor::Diamond;
    c3.card[4].CardNum=Num_7;
    c3.status=ThreeOfaKind;

    //两对
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
    c2.status=TwoPair;

    //一对不能含两对和葫芦
    c1.card[0].CardDecor=Decor::Spade;
    c1.card[0].CardNum=Num_4;
    c1.card[1].CardDecor=Decor::Heart;
    c1.card[1].CardNum=Num_4;
    c1.card[2].CardDecor=Decor::Diamond;
    c1.card[2].CardNum=Num_9;
    c1.card[3].CardDecor=Decor::Club;
    c1.card[3].CardNum=Num_8;
    c1.card[4].CardDecor=Decor::Diamond;
    c1.card[4].CardNum=Num_7;
    c1.status=OnePair;

    //高牌，什么也不是
    c0.card[0].CardDecor=Decor::Spade;
    c0.card[0].CardNum=Num_A;
    c0.card[1].CardDecor=Decor::Heart;
    c0.card[1].CardNum=Num_9;
    c0.card[2].CardDecor=Decor::Diamond;
    c0.card[2].CardNum=Num_8;
    c0.card[3].CardDecor=Decor::Club;
    c0.card[3].CardNum=Num_7;
    c0.card[4].CardDecor=Decor::Diamond;
    c0.card[4].CardNum=Num_4;
    c0.status=HighCard;
    // WARNING 此处会修改牌型
    checkBranchType(c9);
    QVERIFY(c9.status==BrandType::RoyalFlush);//皇家同花顺
    checkBranchType(c8);
    QVERIFY(c8.status==BrandType::StraightFlush);//同花顺
    checkBranchType(c7);
    QVERIFY(c7.status==BrandType::FourOfaKind);//四条
    checkBranchType(c6);
    QVERIFY(c6.status==BrandType::FullHouse);//葫芦测试
    checkBranchType(c5);
    QVERIFY(c5.status==BrandType::Flush);//同花测试
    checkBranchType(c4);
    QVERIFY(c4.status==BrandType::Straight);//顺子测试
    checkBranchType(c3);
    QVERIFY(c3.status==BrandType::ThreeOfaKind);//三条测试
    checkBranchType(c2);
    QVERIFY(c2.status==BrandType::TwoPair);//两对测试
    checkBranchType(c1);
    QVERIFY(c1.status==BrandType::OnePair);//一对测试
    checkBranchType(c0);
    QVERIFY(c0.status==BrandType::HighCard);
}

void TexasPokerTest::case_CardsCompare()
{
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
    //皇家同花顺
    c9.card[0].CardDecor=Decor::Spade;
    c9.card[0].CardNum=Num_10;
    c9.card[1].CardDecor=Decor::Spade;
    c9.card[1].CardNum=Num_J;
    c9.card[2].CardDecor=Decor::Spade;
    c9.card[2].CardNum=Num_Q;
    c9.card[3].CardDecor=Decor::Spade;
    c9.card[3].CardNum=Num_K;
    c9.card[4].CardDecor=Decor::Spade;
    c9.card[4].CardNum=Num_A;
    c9.status=RoyalFlush;

    //同花顺 不能是皇家同花顺
    c8.card[0].CardDecor=Decor::Spade;
    c8.card[0].CardNum=Num_4;
    c8.card[1].CardDecor=Decor::Spade;
    c8.card[1].CardNum=Num_3;
    c8.card[2].CardDecor=Decor::Spade;
    c8.card[2].CardNum=Num_5;
    c8.card[3].CardDecor=Decor::Spade;
    c8.card[3].CardNum=Num_6;
    c8.card[4].CardDecor=Decor::Spade;
    c8.card[4].CardNum=Num_7;
    c8.status=StraightFlush;

    //四条
    c7.card[0].CardDecor=Decor::Spade;
    c7.card[0].CardNum=Num_4;
    c7.card[1].CardDecor=Decor::Heart;
    c7.card[1].CardNum=Num_4;
    c7.card[2].CardDecor=Decor::Diamond;
    c7.card[2].CardNum=Num_4;
    c7.card[3].CardDecor=Decor::Club;
    c7.card[3].CardNum=Num_4;
    c7.card[4].CardDecor=Decor::Club;
    c7.card[4].CardNum=Num_7;
    c7.status=FourOfaKind;

    //葫芦
    c6.card[0].CardDecor=Decor::Spade;
    c6.card[0].CardNum=Num_4;
    c6.card[1].CardDecor=Decor::Heart;
    c6.card[1].CardNum=Num_4;
    c6.card[2].CardDecor=Decor::Diamond;
    c6.card[2].CardNum=Num_4;
    c6.card[3].CardDecor=Decor::Club;
    c6.card[3].CardNum=Num_7;
    c6.card[4].CardDecor=Decor::Diamond;
    c6.card[4].CardNum=Num_7;
    c6.status=FullHouse;

    //同花 不能是顺子 不能是皇家同花顺
    c5.card[0].CardDecor=Decor::Heart;
    c5.card[0].CardNum=Num_2;
    c5.card[1].CardDecor=Decor::Heart;
    c5.card[1].CardNum=Num_4;
    c5.card[2].CardDecor=Decor::Heart;
    c5.card[2].CardNum=Num_8;
    c5.card[3].CardDecor=Decor::Heart;
    c5.card[3].CardNum=Num_K;
    c5.card[4].CardDecor=Decor::Heart;
    c5.card[4].CardNum=Num_Q;
    c5.status=Flush;

    //顺子不能是同花、不能是皇家同花顺
    c4.card[0].CardDecor=Decor::Club;
    c4.card[0].CardNum=Num_5;
    c4.card[1].CardDecor=Decor::Heart;
    c4.card[1].CardNum=Num_4;
    c4.card[2].CardDecor=Decor::Spade;
    c4.card[2].CardNum=Num_6;
    c4.card[3].CardDecor=Decor::Diamond;
    c4.card[3].CardNum=Num_8;
    c4.card[4].CardDecor=Decor::Club;
    c4.card[4].CardNum=Num_7;
    c4.status=Straight;

    //三条不能是葫芦不能是四条
    c3.card[0].CardDecor=Decor::Spade;
    c3.card[0].CardNum=Num_4;
    c3.card[1].CardDecor=Decor::Heart;
    c3.card[1].CardNum=Num_4;
    c3.card[2].CardDecor=Decor::Diamond;
    c3.card[2].CardNum=Num_4;
    c3.card[3].CardDecor=Decor::Club;
    c3.card[3].CardNum=Num_8;
    c3.card[4].CardDecor=Decor::Diamond;
    c3.card[4].CardNum=Num_7;
    c3.status=ThreeOfaKind;

    //两对
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
    c2.status=TwoPair;

    //一对不能含两对和葫芦
    c1.card[0].CardDecor=Decor::Spade;
    c1.card[0].CardNum=Num_4;
    c1.card[1].CardDecor=Decor::Heart;
    c1.card[1].CardNum=Num_4;
    c1.card[2].CardDecor=Decor::Diamond;
    c1.card[2].CardNum=Num_9;
    c1.card[3].CardDecor=Decor::Club;
    c1.card[3].CardNum=Num_8;
    c1.card[4].CardDecor=Decor::Diamond;
    c1.card[4].CardNum=Num_7;
    c1.status=OnePair;

    //高牌，什么也不是
    c0.card[0].CardDecor=Decor::Spade;
    c0.card[0].CardNum=Num_A;
    c0.card[1].CardDecor=Decor::Heart;
    c0.card[1].CardNum=Num_9;
    c0.card[2].CardDecor=Decor::Diamond;
    c0.card[2].CardNum=Num_8;
    c0.card[3].CardDecor=Decor::Club;
    c0.card[3].CardNum=Num_7;
    c0.card[4].CardDecor=Decor::Diamond;
    c0.card[4].CardNum=Num_4;
    c0.status=HighCard;
    //高牌
    QVERIFY(CardsCompare(c0,c1)==2);//高牌-一对
    QVERIFY(CardsCompare(c0,c2)==2);//高牌-两对
    QVERIFY(CardsCompare(c0,c3)==2);//高牌-三条
    QVERIFY(CardsCompare(c0,c4)==2);//高牌-顺子
    QVERIFY(CardsCompare(c0,c5)==2);//高牌-同花
    QVERIFY(CardsCompare(c0,c6)==2);//高牌-葫芦
    QVERIFY(CardsCompare(c0,c7)==2);//高牌-四条
    QVERIFY(CardsCompare(c0,c8)==2);//高牌-同花顺
    QVERIFY(CardsCompare(c0,c9)==2);//高牌-皇家同花顺
    //一对
    QVERIFY(CardsCompare(c1,c2)==2);//一对-两对
    QVERIFY(CardsCompare(c1,c3)==2);//一对-三条
    QVERIFY(CardsCompare(c1,c4)==2);//一对-顺子
    QVERIFY(CardsCompare(c1,c5)==2);//一对-同花
    QVERIFY(CardsCompare(c1,c6)==2);//一对-葫芦
    QVERIFY(CardsCompare(c1,c7)==2);//一对-四条
    QVERIFY(CardsCompare(c1,c8)==2);//一对-同花顺
    QVERIFY(CardsCompare(c1,c9)==2);//一对-皇家同花顺
    //两对
    QVERIFY(CardsCompare(c2,c3)==2);//两对-三条
    QVERIFY(CardsCompare(c2,c4)==2);//两对-顺子
    QVERIFY(CardsCompare(c2,c5)==2);//两对-同花
    QVERIFY(CardsCompare(c2,c6)==2);//两对-葫芦
    QVERIFY(CardsCompare(c2,c7)==2);//两对-四条
    QVERIFY(CardsCompare(c2,c8)==2);//两对-同花顺
    QVERIFY(CardsCompare(c2,c9)==2);//两对-皇家同花顺
    //三条
    QVERIFY(CardsCompare(c3,c4)==2);//三条-顺子
    QVERIFY(CardsCompare(c3,c5)==2);//三条-同花
    QVERIFY(CardsCompare(c3,c6)==2);//三条-葫芦
    QVERIFY(CardsCompare(c3,c7)==2);//三条-四条
    QVERIFY(CardsCompare(c3,c8)==2);//三条-同花顺
    QVERIFY(CardsCompare(c3,c9)==2);//三条-皇家同花顺
    //顺子
    QVERIFY(CardsCompare(c4,c5)==2);//顺子-同花
    QVERIFY(CardsCompare(c4,c6)==2);//顺子-葫芦
    QVERIFY(CardsCompare(c4,c7)==2);//顺子-四条
    QVERIFY(CardsCompare(c4,c8)==2);//顺子-同花顺
    QVERIFY(CardsCompare(c4,c9)==2);//顺子-皇家同花顺
    //同花
    QVERIFY(CardsCompare(c5,c6)==2);//同花-葫芦
    QVERIFY(CardsCompare(c5,c7)==2);//同花-四条
    QVERIFY(CardsCompare(c5,c8)==2);//同花-同花顺
    QVERIFY(CardsCompare(c5,c9)==2);//同花-皇家同花顺
    //葫芦
    QVERIFY(CardsCompare(c6,c7)==2);//葫芦-四条
    QVERIFY(CardsCompare(c6,c8)==2);//葫芦-同花顺
    QVERIFY(CardsCompare(c6,c9)==2);//葫芦-皇家同花顺
    //四条
    QVERIFY(CardsCompare(c7,c8)==2);//四条-同花顺
    QVERIFY(CardsCompare(c7,c9)==2);//四条-皇家同花顺
    //同花顺
    QVERIFY(CardsCompare(c8,c9)==2);//同花顺-皇家同花顺
}

void TexasPokerTest::case_HighCardCompare()
{
    //高牌
    Cards c0;
    c0.card[0].CardDecor=Decor::Spade;
    c0.card[0].CardNum=Num_A;
    c0.card[1].CardDecor=Decor::Heart;
    c0.card[1].CardNum=Num_9;
    c0.card[2].CardDecor=Decor::Diamond;
    c0.card[2].CardNum=Num_8;
    c0.card[3].CardDecor=Decor::Club;
    c0.card[3].CardNum=Num_7;
    c0.card[4].CardDecor=Decor::Diamond;
    c0.card[4].CardNum=Num_4;
    c0.status=HighCard;
    // A > B
    Cards temp;
    temp.card[0].CardDecor=Decor::Diamond;
    temp.card[0].CardNum=Num_A;
    temp.card[1].CardDecor=Decor::Spade;
    temp.card[1].CardNum=Num_J;
    temp.card[2].CardDecor=Decor::Club;
    temp.card[2].CardNum=Num_6;
    temp.card[3].CardDecor=Decor::Spade;
    temp.card[3].CardNum=Num_4;
    temp.card[4].CardDecor=Decor::Heart;
    temp.card[4].CardNum=Num_2;
    temp.status=HighCard;
    QVERIFY(CardsCompare(temp,c0)==1);
    // A<B
    QVERIFY(CardsCompare(c0,temp)==2);
    // A==B
    temp.card[0].CardDecor=Decor::Diamond;
    temp.card[0].CardNum=Num_A;
    temp.card[1].CardDecor=Decor::Spade;
    temp.card[1].CardNum=Num_9;
    temp.card[2].CardDecor=Decor::Club;
    temp.card[2].CardNum=Num_8;
    temp.card[3].CardDecor=Decor::Spade;
    temp.card[3].CardNum=Num_7;
    temp.card[4].CardDecor=Decor::Heart;
    temp.card[4].CardNum=Num_4;
    temp.status=HighCard;
    QVERIFY(CardsCompare(temp,c0)==0);
}

void TexasPokerTest::case_OnePairCompare()
{
    // A > B 对子大
    Cards c1;
    c1.card[0].CardDecor=Decor::Diamond;
    c1.card[0].CardNum=Num_A;
    c1.card[1].CardDecor=Decor::Spade;
    c1.card[1].CardNum=Num_A;
    c1.card[2].CardDecor=Decor::Club;
    c1.card[2].CardNum=Num_J;
    c1.card[3].CardDecor=Decor::Spade;
    c1.card[3].CardNum=Num_8;
    c1.card[4].CardDecor=Decor::Heart;
    c1.card[4].CardNum=Num_6;
    c1.status=OnePair;
    c1.Data.pair.pairc=Num_A;
    c1.Data.pair.c[0]=Num_J;
    c1.Data.pair.c[1]=Num_8;
    c1.Data.pair.c[2]=Num_6;

    Cards temp;
    temp.card[0].CardDecor=Decor::Diamond;
    temp.card[0].CardNum=Num_2;
    temp.card[1].CardDecor=Decor::Spade;
    temp.card[1].CardNum=Num_2;
    temp.card[2].CardDecor=Decor::Club;
    temp.card[2].CardNum=Num_A;
    temp.card[3].CardDecor=Decor::Spade;
    temp.card[3].CardNum=Num_J;
    temp.card[4].CardDecor=Decor::Heart;
    temp.card[4].CardNum=Num_6;
    temp.status=OnePair;
    temp.Data.pair.pairc=Num_2;
    temp.Data.pair.c[0]=Num_A;
    temp.Data.pair.c[1]=Num_J;
    temp.Data.pair.c[2]=Num_A;
    QVERIFY(CardsCompare(c1,temp)==1);//a > b
    QVERIFY(CardsCompare(temp,c1)==2);//a < b
    // A > B 对子一样 但是单牌大
    temp.card[0].CardDecor=Decor::Diamond;
    temp.card[0].CardNum=Num_A;
    temp.card[1].CardDecor=Decor::Spade;
    temp.card[1].CardNum=Num_A;
    temp.card[2].CardDecor=Decor::Club;
    temp.card[2].CardNum=Num_J;
    temp.card[3].CardDecor=Decor::Spade;
    temp.card[3].CardNum=Num_8;
    temp.card[4].CardDecor=Decor::Heart;
    temp.card[4].CardNum=Num_4;
    temp.status=OnePair;
    temp.Data.pair.pairc=Num_A;
    temp.Data.pair.c[0]=Num_J;
    temp.Data.pair.c[1]=Num_8;
    temp.Data.pair.c[2]=Num_4;
    QVERIFY(CardsCompare(c1,temp)==1);//a > b
    QVERIFY(CardsCompare(temp,c1)==2);//a < b
    // A = B
    temp.card[0].CardDecor=Decor::Diamond;
    temp.card[0].CardNum=Num_A;
    temp.card[1].CardDecor=Decor::Spade;
    temp.card[1].CardNum=Num_A;
    temp.card[2].CardDecor=Decor::Club;
    temp.card[2].CardNum=Num_J;
    temp.card[3].CardDecor=Decor::Spade;
    temp.card[3].CardNum=Num_8;
    temp.card[4].CardDecor=Decor::Heart;
    temp.card[4].CardNum=Num_7;
    temp.status=OnePair;
    temp.Data.pair.pairc=Num_A;
    temp.Data.pair.c[0]=Num_J;
    temp.Data.pair.c[1]=Num_8;
    temp.Data.pair.c[2]=Num_6;
    QVERIFY(CardsCompare(c1,temp)==0);//a > b
}

void TexasPokerTest::case_TwoPairCompare()
{
    // A > B 对子比较大
    Cards c1;
    c1.card[0].CardDecor=Decor::Diamond;
    c1.card[0].CardNum=Num_A;
    c1.card[1].CardDecor=Decor::Spade;
    c1.card[1].CardNum=Num_A;
    c1.card[2].CardDecor=Decor::Club;
    c1.card[2].CardNum=Num_J;
    c1.card[3].CardDecor=Decor::Spade;
    c1.card[3].CardNum=Num_J;
    c1.card[4].CardDecor=Decor::Heart;
    c1.card[4].CardNum=Num_6;
    c1.status=TwoPair;
    c1.Data.pairs.pairc1=Num_A;
    c1.Data.pairs.pairc2=Num_J;
    c1.Data.pairs.c=Num_6;

    Cards c2;
    c2.card[0].CardDecor=Decor::Diamond;
    c2.card[0].CardNum=Num_J;
    c2.card[1].CardDecor=Decor::Spade;
    c2.card[1].CardNum=Num_J;
    c2.card[2].CardDecor=Decor::Club;
    c2.card[2].CardNum=Num_8;
    c2.card[3].CardDecor=Decor::Spade;
    c2.card[3].CardNum=Num_8;
    c2.card[4].CardDecor=Decor::Heart;
    c2.card[4].CardNum=Num_6;
    c2.status=TwoPair;
    c2.Data.pairs.pairc1=Num_J;
    c2.Data.pairs.pairc2=Num_8;
    c2.Data.pairs.c=Num_6;
    QVERIFY(CardsCompare(c1,c2)==1);//A>B
    QVERIFY(CardsCompare(c2,c1)==2);//A<B

    // A > B 对子一样大，单牌不一样大
    Cards c3;
    c3.card[0].CardDecor=Decor::Diamond;
    c3.card[0].CardNum=Num_A;
    c3.card[1].CardDecor=Decor::Spade;
    c3.card[1].CardNum=Num_A;
    c3.card[2].CardDecor=Decor::Club;
    c3.card[2].CardNum=Num_J;
    c3.card[3].CardDecor=Decor::Spade;
    c3.card[3].CardNum=Num_J;
    c3.card[4].CardDecor=Decor::Heart;
    c3.card[4].CardNum=Num_2;
    c3.status=TwoPair;
    c3.Data.pairs.pairc1=Num_A;
    c3.Data.pairs.pairc2=Num_J;
    c3.Data.pairs.c=Num_2;
    QVERIFY(CardsCompare(c1,c3)==1);//A>B
    QVERIFY(CardsCompare(c3,c1)==2);//A<B

    // A = B
    Cards c4;
    c4.card[0].CardDecor=Decor::Diamond;
    c4.card[0].CardNum=Num_A;
    c4.card[1].CardDecor=Decor::Spade;
    c4.card[1].CardNum=Num_A;
    c4.card[2].CardDecor=Decor::Club;
    c4.card[2].CardNum=Num_J;
    c4.card[3].CardDecor=Decor::Spade;
    c4.card[3].CardNum=Num_J;
    c4.card[4].CardDecor=Decor::Heart;
    c4.card[4].CardNum=Num_6;
    c4.status=TwoPair;
    c4.Data.pairs.pairc1=Num_A;
    c4.Data.pairs.pairc2=Num_J;
    c4.Data.pairs.c=Num_6;
    QVERIFY(CardsCompare(c1,c4)==0);//A=B
}

void TexasPokerTest::case_ThreeCompare()
{
    // A > B 三条比较大
    Cards c1;
    c1.card[0].CardDecor=Decor::Diamond;
    c1.card[0].CardNum=Num_A;
    c1.card[1].CardDecor=Decor::Spade;
    c1.card[1].CardNum=Num_A;
    c1.card[2].CardDecor=Decor::Club;
    c1.card[2].CardNum=Num_A;
    c1.card[3].CardDecor=Decor::Spade;
    c1.card[3].CardNum=Num_J;
    c1.card[4].CardDecor=Decor::Heart;
    c1.card[4].CardNum=Num_6;
    c1.status=ThreeOfaKind;
    c1.Data.three.threec=Num_A;
    c1.Data.three.c[0]=Num_J;
    c1.Data.three.c[1]=Num_6;

    Cards c2;
    c2.card[0].CardDecor=Decor::Diamond;
    c2.card[0].CardNum=Num_J;
    c2.card[1].CardDecor=Decor::Spade;
    c2.card[1].CardNum=Num_J;
    c2.card[2].CardDecor=Decor::Club;
    c2.card[2].CardNum=Num_J;
    c2.card[3].CardDecor=Decor::Spade;
    c2.card[3].CardNum=Num_8;
    c2.card[4].CardDecor=Decor::Heart;
    c2.card[4].CardNum=Num_6;
    c2.status=ThreeOfaKind;
    c2.Data.three.threec=Num_J;
    c2.Data.three.c[0]=Num_8;
    c2.Data.three.c[1]=Num_6;
    QVERIFY(CardsCompare(c1,c2)==1);//A>B
    QVERIFY(CardsCompare(c2,c1)==2);//A<B

    // A > B 三条一样大，单牌不一样大
    Cards c3;
    c3.card[0].CardDecor=Decor::Diamond;
    c3.card[0].CardNum=Num_A;
    c3.card[1].CardDecor=Decor::Spade;
    c3.card[1].CardNum=Num_A;
    c3.card[2].CardDecor=Decor::Club;
    c3.card[2].CardNum=Num_A;
    c3.card[3].CardDecor=Decor::Spade;
    c3.card[3].CardNum=Num_J;
    c3.card[4].CardDecor=Decor::Heart;
    c3.card[4].CardNum=Num_2;
    c3.status=ThreeOfaKind;
    c3.Data.three.threec=Num_A;
    c3.Data.three.c[0]=Num_J;
    c3.Data.three.c[1]=Num_2;
    QVERIFY(CardsCompare(c1,c3)==1);//A>B
    QVERIFY(CardsCompare(c3,c1)==2);//A<B

    // A = B
    Cards c4;
    c4.card[0].CardDecor=Decor::Diamond;
    c4.card[0].CardNum=Num_A;
    c4.card[1].CardDecor=Decor::Spade;
    c4.card[1].CardNum=Num_A;
    c4.card[2].CardDecor=Decor::Club;
    c4.card[2].CardNum=Num_A;
    c4.card[3].CardDecor=Decor::Spade;
    c4.card[3].CardNum=Num_J;
    c4.card[4].CardDecor=Decor::Heart;
    c4.card[4].CardNum=Num_6;
    c4.status=ThreeOfaKind;
    c4.Data.three.threec=Num_A;
    c4.Data.three.c[0]=Num_J;
    c4.Data.three.c[1]=Num_6;
    QVERIFY(CardsCompare(c1,c4)==0);//A=B
}
