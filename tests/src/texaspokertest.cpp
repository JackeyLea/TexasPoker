#include "texaspokertest.h"

#include "../TexasPoker/card.h"
#include "../TexasPoker/comparecards.h"

void TexasPokerTest::case_checkGetBrandType()
{
    CompareCards cc;
    QVERIFY(cc.getBrandType(CompareCards::HighCard)=="高牌");//高牌
    QVERIFY(cc.getBrandType(CompareCards::OnePair)=="一对");//高牌
    QVERIFY(cc.getBrandType(CompareCards::TwoPair)=="两对");//高牌
    QVERIFY(cc.getBrandType(CompareCards::ThreeOfaKind)=="三条");//高牌
    QVERIFY(cc.getBrandType(CompareCards::Straight)=="顺子");//高牌
    QVERIFY(cc.getBrandType(CompareCards::Flush)=="同花");//高牌
    QVERIFY(cc.getBrandType(CompareCards::FullHouse)=="葫芦");//高牌
    QVERIFY(cc.getBrandType(CompareCards::FourOfaKind)=="四条");//高牌
    QVERIFY(cc.getBrandType(CompareCards::StraightFlush)=="同花顺");//高牌
    QVERIFY(cc.getBrandType(CompareCards::RoyalFlush)=="皇家同花顺");//高牌
}

void TexasPokerTest::case_checkStraightCards()
{
    CompareCards cc;
    //非顺子
    CompareCards::Cards cards1;
    cards1.card[0].setDecor(Card::Diamond);
    cards1.card[0].setNum(Card::Num_A);
    cards1.card[1].setDecor(Card::Spade);
    cards1.card[1].setNum(Card::Num_9);
    cards1.card[2].setDecor(Card::Heart);
    cards1.card[2].setNum(Card::Num_J);
    cards1.card[3].setDecor(Card::Club);
    cards1.card[3].setNum(Card::Num_2);
    cards1.card[4].setDecor(Card::Diamond);
    cards1.card[4].setNum(Card::Num_5);
    cc.straightCards(cards1);
    QVERIFY(cards1.card[0].num()==Card::Num_A);
    QVERIFY(cards1.card[1].num()==Card::Num_J);
    QVERIFY(cards1.card[2].num()==Card::Num_9);
    QVERIFY(cards1.card[3].num()==Card::Num_5);
    QVERIFY(cards1.card[4].num()==Card::Num_2);

    //顺子
    CompareCards::Cards cards2;
    cards2.card[0].setDecor(Card::Diamond);
    cards2.card[0].setNum(Card::Num_9);
    cards2.card[1].setDecor(Card::Heart);
    cards2.card[1].setNum(Card::Num_6);
    cards2.card[2].setDecor(Card::Club);
    cards2.card[2].setNum(Card::Num_5);
    cards2.card[3].setDecor(Card::Spade);
    cards2.card[3].setNum(Card::Num_7);
    cards2.card[4].setDecor(Card::Diamond);
    cards2.card[4].setNum(Card::Num_8);
    cc.straightCards(cards2);
    QVERIFY(cards2.card[0].num()==Card::Num_9);
    QVERIFY(cards2.card[1].num()==Card::Num_8);
    QVERIFY(cards2.card[2].num()==Card::Num_7);
    QVERIFY(cards2.card[3].num()==Card::Num_6);
    QVERIFY(cards2.card[4].num()==Card::Num_5);
}

void TexasPokerTest::case_checkIsDuplicate()
{
    CompareCards cc;
    //不重复
    CompareCards::Cards cards1;
    cards1.card[0].setDecor(Card::Diamond);
    cards1.card[0].setNum(Card::Num_9);
    cards1.card[1].setDecor(Card::Heart);
    cards1.card[1].setNum(Card::Num_6);
    cards1.card[2].setDecor(Card::Club);
    cards1.card[2].setNum(Card::Num_5);
    cards1.card[3].setDecor(Card::Spade);
    cards1.card[3].setNum(Card::Num_7);
    cards1.card[4].setDecor(Card::Diamond);
    cards1.card[4].setNum(Card::Num_8);
    QVERIFY(cc.isDuplicate(cards1)==false);

    //重复
    CompareCards::Cards cards2;
    cards2.card[0].setDecor(Card::Diamond);
    cards2.card[0].setNum(Card::Num_9);
    cards2.card[1].setDecor(Card::Heart);
    cards2.card[1].setNum(Card::Num_6);
    cards2.card[2].setDecor(Card::Club);
    cards2.card[2].setNum(Card::Num_5);
    cards2.card[3].setDecor(Card::Spade);
    cards2.card[3].setNum(Card::Num_7);
    cards2.card[4].setDecor(Card::Diamond);
    cards2.card[4].setNum(Card::Num_9);
    QVERIFY(cc.isDuplicate(cards2)==true);
}

void TexasPokerTest::case_checkIs5()
{
    CompareCards cc;
    //一样
    CompareCards::Cards cards1;
    cards1.card[0].setDecor(Card::Diamond);
    cards1.card[0].setNum(Card::Num_9);
    cards1.card[1].setDecor(Card::Heart);
    cards1.card[1].setNum(Card::Num_9);
    cards1.card[2].setDecor(Card::Club);
    cards1.card[2].setNum(Card::Num_9);
    cards1.card[3].setDecor(Card::Spade);
    cards1.card[3].setNum(Card::Num_9);
    cards1.card[4].setDecor(Card::Diamond);
    cards1.card[4].setNum(Card::Num_9);
    QVERIFY(cc.is5(cards1)==true);

    //不一样
    CompareCards::Cards cards2;
    cards2.card[0].setDecor(Card::Diamond);
    cards2.card[0].setNum(Card::Num_9);
    cards2.card[1].setDecor(Card::Heart);
    cards2.card[1].setNum(Card::Num_9);
    cards2.card[2].setDecor(Card::Club);
    cards2.card[2].setNum(Card::Num_9);
    cards2.card[3].setDecor(Card::Spade);
    cards2.card[3].setNum(Card::Num_9);
    cards2.card[4].setDecor(Card::Diamond);
    cards2.card[4].setNum(Card::Num_8);
    QVERIFY(cc.is5(cards2)==false);
}

void TexasPokerTest::case_checkOnePair()
{
    //包含一对的有三条 四条 三带二 一对 两对
    CompareCards cc;

    //四条
    CompareCards::Cards c7;
    c7.card[0].setDecor(Card::Spade);
    c7.card[0].setNum(Card::Num_4);
    c7.card[1].setDecor(Card::Heart);
    c7.card[1].setNum(Card::Num_4);
    c7.card[2].setDecor(Card::Diamond);
    c7.card[2].setNum(Card::Num_4);
    c7.card[3].setDecor(Card::Club);
    c7.card[3].setNum(Card::Num_4);
    c7.card[4].setDecor(Card::Club);
    c7.card[4].setNum(Card::Num_7);
    QVERIFY(cc.isOnePair(c7)==true);//四条

    //葫芦
    CompareCards::Cards c6;
    c6.card[0].setDecor(Card::Spade);
    c6.card[0].setNum(Card::Num_4);
    c6.card[1].setDecor(Card::Heart);
    c6.card[1].setNum(Card::Num_4);
    c6.card[2].setDecor(Card::Diamond);
    c6.card[2].setNum(Card::Num_4);
    c6.card[3].setDecor(Card::Club);
    c6.card[3].setNum(Card::Num_7);
    c6.card[4].setDecor(Card::Diamond);
    c6.card[4].setNum(Card::Num_7);
    QVERIFY(cc.isOnePair(c6)==true);//葫芦测试

    //三条不能是葫芦不能是四条
    CompareCards::Cards c3;
    c3.card[0].setDecor(Card::Spade);
    c3.card[0].setNum(Card::Num_4);
    c3.card[1].setDecor(Card::Heart);
    c3.card[1].setNum(Card::Num_4);
    c3.card[2].setDecor(Card::Diamond);
    c3.card[2].setNum(Card::Num_4);
    c3.card[3].setDecor(Card::Club);
    c3.card[3].setNum(Card::Num_8);
    c3.card[4].setDecor(Card::Diamond);
    c3.card[4].setNum(Card::Num_7);
    QVERIFY(cc.isOnePair(c3)==true);//三条测试

    //两对
    CompareCards::Cards c2;
    c2.card[0].setDecor(Card::Spade);
    c2.card[0].setNum(Card::Num_4);
    c2.card[1].setDecor(Card::Heart);
    c2.card[1].setNum(Card::Num_4);
    c2.card[2].setDecor(Card::Diamond);
    c2.card[2].setNum(Card::Num_9);
    c2.card[3].setDecor(Card::Club;
    c2.card[3].setNum(Card::Num_7);
    c2.card[4].setDecor(Card::Diamond);
    c2.card[4].setNum(Card::Num_7);
    QVERIFY(cc.isOnePair(c2)==true);//两对测试

    //一对不能含两对和葫芦
    CompareCards::Cards c1;
    c1.card[0].setDecor(Card::Spade);
    c1.card[0].setNum(Card::Num_4);
    c1.card[1].setDecor(Card::Heart);
    c1.card[1].setNum(Card::Num_4);
    c1.card[2].setDecor(Card::Diamond);
    c1.card[2].setNum(Card::Num_9);
    c1.card[3].setDecor(Card::Club);
    c1.card[3].setNum(Card::Num_8);
    c1.card[4].setDecor(Card::Diamond);
    c1.card[4].setNum(Card::Num_7);
    QVERIFY(cc.isOnePair(c1)==true);//一对测试

    //高牌，什么也不是
    CompareCards::Cards c0;
    c0.card[0].setDecor(Card::Spade);
    c0.card[0].setNum(Card::Num_A);
    c0.card[1].setDecor(Card::Heart);
    c0.card[1].setNum(Card::Num_9);
    c0.card[2].setDecor(Card::Diamond);
    c0.card[2].setNum(Card::Num_8);
    c0.card[3].setDecor(Card::Club);
    c0.card[3].setNum(Card::Num_7);
    c0.card[4].setDecor(Card::Diamond);
    c0.card[4].setNum(Card::Num_4);
    QVERIFY(cc.isOnePair(c0)==false);//高牌
}

void TexasPokerTest::case_checkTwoPair()
{
    CompareCards cc;
    ///两对
    //两对
    CompareCards::Cards c2;
    c2.card[0].setDecor(Card::Spade);
    c2.card[0].setNum(Card::Num_4);
    c2.card[1].setDecor(Card::Heart);
    c2.card[1].setNum(Card::Num_4);
    c2.card[2].setDecor(Card::Diamond);
    c2.card[2].setNum(Card::Num_9);
    c2.card[3].setDecor(Card::Club);
    c2.card[3].setNum(Card::Num_7);
    c2.card[4].setDecor(Card::Diamond);
    c2.card[4].setNum(Card::Num_7);
    QVERIFY(cc.isTwoPair(c2)==true);//两对测试

    ///非两对
    //四条
    CompareCards::Cards c7;
    c7.card[0].setDecor(Card::Spade);
    c7.card[0].setNum(Card::Num_4);
    c7.card[1].setDecor(Card::Heart);
    c7.card[1].setNum(Card::Num_4);
    c7.card[2].setDecor(Card::Diamond);
    c7.card[2].setNum(Card::Num_4);
    c7.card[3].setDecor(Card::Club);
    c7.card[3].setNum(Card::Num_4);
    c7.card[4].setDecor(Card::Club);
    c7.card[4].setNum(Card::Num_7);
    QVERIFY(cc.isTwoPair(c7)==false);//四条

    //葫芦
    CompareCards::Cards c6;
    c6.card[0].setDecor(Card::Spade);
    c6.card[0].setNum(Card::Num_4);
    c6.card[1].setDecor(Card::Heart);
    c6.card[1].setNum(Card::Num_4);
    c6.card[2].setDecor(Card::Diamond);
    c6.card[2].setNum(Card::Num_4);
    c6.card[3].setDecor(Card::Club);
    c6.card[3].setNum(Card::Num_7);
    c6.card[4].setDecor(Card::Diamond);
    c6.card[4].setNum(Card::Num_7);
    QVERIFY(cc.isTwoPair(c6)==true);//葫芦测试

    //三条不能是葫芦不能是四条
    CompareCards::Cards c3;
    c3.card[0].setDecor(Card::Spade);
    c3.card[0].setNum(Card::Num_4);
    c3.card[1].setDecor(Card::Heart);
    c3.card[1].setNum(Card::Num_4);
    c3.card[2].setDecor(Card::Diamond);
    c3.card[2].setNum(Card::Num_4);
    c3.card[3].setDecor(Card::Club);
    c3.card[3].setNum(Card::Num_8);
    c3.card[4].setDecor(Card::Diamond);
    c3.card[4].setNum(Card::Num_7);
    QVERIFY(cc.isTwoPair(c3)==false);//三条测试

    //一对不能含两对和葫芦
    CompareCards::Cards c1;
    c1.card[0].setDecor(Card::Spade);
    c1.card[0].setNum(Card::Num_4);
    c1.card[1].setDecor(Card::Heart);
    c1.card[1].setNum(Card::Num_4);
    c1.card[2].setDecor(Card::Diamond);
    c1.card[2].setNum(Card::Num_9);
    c1.card[3].setDecor(Card::Club);
    c1.card[3].setNum(Card::Num_8);
    c1.card[4].setDecor(Card::Diamond);
    c1.card[4].setNum(Card::Num_7);
    QVERIFY(cc.isTwoPair(c1)==false);//一对测试

    //高牌，什么也不是
    CompareCards::Cards c0;
    c0.card[0].setDecor(Card::Spade);
    c0.card[0].setNum(Card::Num_A);
    c0.card[1].setDecor(Card::Heart);
    c0.card[1].setNum(Card::Num_9);
    c0.card[2].setDecor(Card::Diamond);
    c0.card[2].setNum(Card::Num_8);
    c0.card[3].setDecor(Card::Club);
    c0.card[3].setNum(Card::Num_7);
    c0.card[4].setDecor(Card::Diamond);
    c0.card[4].setNum(Card::Num_4);
    QVERIFY(cc.isTwoPair(c0)==false);//高牌
}

void TexasPokerTest::case_checkThreeKind()
{
    CompareCards cc;
    //包含三条 可能是三条、葫芦、四条
    //四条
    CompareCards::Cards cards1;
    cards1.card[0].setDecor(Card::Spade);
    cards1.card[0].setNum(Card::Num_4);
    cards1.card[1].setDecor(Card::Heart);
    cards1.card[1].setNum(Card::Num_4);
    cards1.card[2].setDecor(Card::Diamond);
    cards1.card[2].setNum(Card::Num_4);
    cards1.card[3].setDecor(Card::Club);
    cards1.card[3].setNum(Card::Num_4);
    cards1.card[4].setDecor(Card::Club);
    cards1.card[4].setNum(Card::Num_7);
    QVERIFY(cc.isThreeKind(cards1)==true);

    //葫芦
    CompareCards::Cards cards2;
    cards2.card[0].setDecor(Card::Spade);
    cards2.card[0].setNum(Card::Num_4);
    cards2.card[1].setDecor(Card::Heart);
    cards2.card[1].setNum(Card::Num_4);
    cards2.card[2].setDecor(Card::Diamond);
    cards2.card[2].setNum(Card::Num_4);
    cards2.card[3].setDecor(Card::Club);
    cards2.card[3].setNum(Card::Num_7);
    cards2.card[4].setDecor(Card::Diamond);
    cards2.card[4].setNum(Card::Num_7);
    QVERIFY(cc.isThreeKind(cards1)==true);

    //三条不能是葫芦不能是四条
    CompareCards::Cards cards3;
    cards3.card[0].setDecor(Card::Spade);
    cards3.card[0].setNum(Card::Num_4);
    cards3.card[1].setDecor(Card::Heart);
    cards3.card[1].setNum(Card::Num_4);
    cards3.card[2].setDecor(Card::Diamond);
    cards3.card[2].setNum(Card::Num_4);
    cards3.card[3].setDecor(Card::Club);
    cards3.card[3].setNum(Card::Num_8);
    cards3.card[4].setDecor(Card::Diamond);
    cards3.card[4].setNum(Card::Num_7);
    QVERIFY(cc.isThreeKind(cards3)==true);

    //不包含三条
    //高牌，什么也不是
    CompareCards::Cards card4;
    card4.card[0].setDecor(Card::Spade);
    card4.card[0].setNum(Card::Num_A);
    card4.card[1].setDecor(Card::Heart);
    card4.card[1].setNum(Card::Num_9);
    card4.card[2].setDecor(Card::Diamond);
    card4.card[2].setNum(Card::Num_8);
    card4.card[3].setDecor(Card::Club);
    card4.card[3].setNum(Card::Num_7);
    card4.card[4].setDecor(Card::Diamond);
    card4.card[4].setNum(Card::Num_4);
    QVERIFY(cc.isThreeKind(card4)==false);
}

void TexasPokerTest::case_checkStraight()
{
    CompareCards cc;
    //顺子
    CompareCards::Cards c0;
    c0.card[0].setDecor(Card::Spade);
    c0.card[0].setNum(Card::Num_5);
    c0.card[1].setDecor(Card::Heart);
    c0.card[1].setNum(Card::Num_6);
    c0.card[2].setDecor(Card::Diamond);
    c0.card[2].setNum(Card::Num_8);
    c0.card[3].setDecor(Card::Club);
    c0.card[3].setNum(Card::Num_7);
    c0.card[4].setDecor(Card::Diamond);
    c0.card[4].setNum(Card::Num_4);
    QVERIFY(cc.isStraight(c0)==true);//顺子

    //非顺子
    CompareCards::Cards c1;
    c1.card[0].setDecor(Card::Spade);
    c1.card[0].setNum(Card::Num_A);
    c1.card[1].setDecor(Card::Heart);
    c1.card[1].setNum(Card::Num_9);
    c1.card[2].setDecor(Card::Diamond);
    c1.card[2].setNum(Card::Num_8);
    c1.card[3].setDecor(Card::Club);
    c1.card[3].setNum(Card::Num_7);
    c1.card[4].setDecor(Card::Diamond);
    c1.card[4].setNum(Card::Num_4);
    QVERIFY(cc.isStraight(c1)==false);
}

//测试同花
void TexasPokerTest::case_checkFlush()
{
    CompareCards cc;
    //同花
    CompareCards::Cards cards1;
    cards1.card[0].setDecor(Card::Spade);
    cards1.card[0].setNum(Card::Num_10);
    cards1.card[1].setDecor(Card::Spade);
    cards1.card[1].setNum(Card::Num_J);
    cards1.card[2].setDecor(Card::Spade);
    cards1.card[2].setNum(Card::Num_Q);
    cards1.card[3].setDecor(Card::Spade);
    cards1.card[3].setNum(Card::Num_K);
    cards1.card[4].setDecor(Card::Spade);
    cards1.card[4].setNum(Card::Num_A);
    QVERIFY(cc.isFlush(cards1)==true);

    //非同花
    CompareCards::Cards cards2;
    cards2.card[0].setDecor(Card::Spade);
    cards2.card[0].setNum(Card::Num_10);
    cards2.card[1].setDecor(Card::Spade);
    cards2.card[1].setNum(Card::Num_J);
    cards2.card[2].setDecor(Card::Spade);
    cards2.card[2].setNum(Card::Num_Q);
    cards2.card[3].setDecor(Card::Spade);
    cards2.card[3].setNum(Card::Num_K);
    cards2.card[4].setDecor(Card::Heart);
    cards2.card[4].setNum(Card::Num_A);
    QVERIFY(cc.isFlush(cards2)==false);
}

//测试葫芦
void TexasPokerTest::case_checkFullhouse()
{
    CompareCards cc;
    ///葫芦
    //葫芦
    Cards c6;
    c6.card[0].setDecor(Card::Spade;
    c6.card[0].setNum(Num_4;
    c6.card[1].setDecor(Card::Heart;
    c6.card[1].setNum(Num_4;
    c6.card[2].setDecor(Card::Diamond;
    c6.card[2].setNum(Num_4;
    c6.card[3].setDecor(Card::Club;
    c6.card[3].setNum(Num_7;
    c6.card[4].setDecor(Card::Diamond;
    c6.card[4].setNum(Num_7;
    QVERIFY(cc.isFullHouse(c6)==true);//葫芦测试

    ///非葫芦
    //四条
    Cards c7;
    c7.card[0].setDecor(Card::Spade;
    c7.card[0].setNum(Num_4;
    c7.card[1].setDecor(Card::Heart;
    c7.card[1].setNum(Num_4;
    c7.card[2].setDecor(Card::Diamond;
    c7.card[2].setNum(Num_4;
    c7.card[3].setDecor(Card::Club;
    c7.card[3].setNum(Num_4;
    c7.card[4].setDecor(Card::Club;
    c7.card[4].setNum(Num_7;
    QVERIFY(cc.isFullHouse(c7)==false);//四条

    //三条不能是葫芦不能是四条
    Cards c3;
    c3.card[0].setDecor(Card::Spade;
    c3.card[0].setNum(Num_4;
    c3.card[1].setDecor(Card::Heart;
    c3.card[1].setNum(Num_4;
    c3.card[2].setDecor(Card::Diamond;
    c3.card[2].setNum(Num_4;
    c3.card[3].setDecor(Card::Club;
    c3.card[3].setNum(Num_8;
    c3.card[4].setDecor(Card::Diamond;
    c3.card[4].setNum(Num_7;
    QVERIFY(cc.isFullHouse(c3)==false);//三条测试

    //两对
    Cards c2;
    c2.card[0].setDecor(Card::Spade;
    c2.card[0].setNum(Num_4;
    c2.card[1].setDecor(Card::Heart;
    c2.card[1].setNum(Num_4;
    c2.card[2].setDecor(Card::Diamond;
    c2.card[2].setNum(Num_9;
    c2.card[3].setDecor(Card::Club;
    c2.card[3].setNum(Num_7;
    c2.card[4].setDecor(Card::Diamond;
    c2.card[4].setNum(Num_7;
    QVERIFY(cc.isFullHouse(c2)==false);//两对测试

    //一对不能含两对和葫芦
    Cards c1;
    c1.card[0].setDecor(Card::Spade;
    c1.card[0].setNum(Num_4;
    c1.card[1].setDecor(Card::Heart;
    c1.card[1].setNum(Num_4;
    c1.card[2].setDecor(Card::Diamond;
    c1.card[2].setNum(Num_9;
    c1.card[3].setDecor(Card::Club;
    c1.card[3].setNum(Num_8;
    c1.card[4].setDecor(Card::Diamond;
    c1.card[4].setNum(Num_7;
    QVERIFY(cc.isFullHouse(c1)==false);//一对测试

    //高牌，什么也不是
    Cards c0;
    c0.card[0].setDecor(Card::Spade;
    c0.card[0].setNum(Num_A;
    c0.card[1].setDecor(Card::Heart;
    c0.card[1].setNum(Num_9;
    c0.card[2].setDecor(Card::Diamond;
    c0.card[2].setNum(Num_8;
    c0.card[3].setDecor(Card::Club;
    c0.card[3].setNum(Num_7;
    c0.card[4].setDecor(Card::Diamond;
    c0.card[4].setNum(Num_4;
    QVERIFY(cc.isFullHouse(c0)==false);//高牌
}

//四条
void TexasPokerTest::case_checkFourKind()
{
    //包含
    Cards c0;
    c0.card[0].setDecor(Card::Spade;
    c0.card[0].setNum(Num_A;
    c0.card[1].setDecor(Card::Heart;
    c0.card[1].setNum(Num_A;
    c0.card[2].setDecor(Card::Diamond;
    c0.card[2].setNum(Num_A;
    c0.card[3].setDecor(Card::Club;
    c0.card[3].setNum(Num_A;
    c0.card[4].setDecor(Card::Diamond;
    c0.card[4].setNum(Num_4;
    QVERIFY(isFourKing(c0)==true);

    //不包含
    Cards c1;
    c1.card[0].setDecor(Card::Spade;
    c1.card[0].setNum(Num_A;
    c1.card[1].setDecor(Card::Heart;
    c1.card[1].setNum(Num_A;
    c1.card[2].setDecor(Card::Diamond;
    c1.card[2].setNum(Num_A;
    c1.card[3].setDecor(Card::Club;
    c1.card[3].setNum(Num_4;
    c1.card[4].setDecor(Card::Diamond;
    c1.card[4].setNum(Num_4;
    QVERIFY(isFourKing(c1)==false);
}

//测试最大是否为A
void TexasPokerTest::case_checkA()
{
    //不包含
    Cards c0;
    c0.card[0].setDecor(Card::Spade;
    c0.card[0].setNum(Num_A;
    c0.card[1].setDecor(Card::Heart;
    c0.card[1].setNum(Num_A;
    c0.card[2].setDecor(Card::Diamond;
    c0.card[2].setNum(Num_9;
    c0.card[3].setDecor(Card::Club;
    c0.card[3].setNum(Num_8;
    c0.card[4].setDecor(Card::Diamond;
    c0.card[4].setNum(Num_7;
    QVERIFY(isHighA(c0)==true);

    //包含
    Cards c1;
    c1.card[0].setDecor(Card::Spade;
    c1.card[0].setNum(Num_A;
    c1.card[1].setDecor(Card::Heart;
    c1.card[1].setNum(Num_9;
    c1.card[2].setDecor(Card::Diamond;
    c1.card[2].setNum(Num_8;
    c1.card[3].setDecor(Card::Club;
    c1.card[3].setNum(Num_7;
    c1.card[4].setDecor(Card::Diamond;
    c1.card[4].setNum(Num_4;
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
    c9.card[0].setDecor(Card::Spade;
    c9.card[0].setNum(Num_10;
    c9.card[1].setDecor(Card::Spade;
    c9.card[1].setNum(Num_J;
    c9.card[2].setDecor(Card::Spade;
    c9.card[2].setNum(Num_Q;
    c9.card[3].setDecor(Card::Spade;
    c9.card[3].setNum(Num_K;
    c9.card[4].setDecor(Card::Spade;
    c9.card[4].setNum(Num_A;
    c9.status=RoyalFlush;

    //同花顺 不能是皇家同花顺
    c8.card[0].setDecor(Card::Spade;
    c8.card[0].setNum(Num_4;
    c8.card[1].setDecor(Card::Spade;
    c8.card[1].setNum(Num_3;
    c8.card[2].setDecor(Card::Spade;
    c8.card[2].setNum(Num_5;
    c8.card[3].setDecor(Card::Spade;
    c8.card[3].setNum(Num_6;
    c8.card[4].setDecor(Card::Spade;
    c8.card[4].setNum(Num_7;
    c8.status=StraightFlush;

    //四条
    c7.card[0].setDecor(Card::Spade;
    c7.card[0].setNum(Num_4;
    c7.card[1].setDecor(Card::Heart;
    c7.card[1].setNum(Num_4;
    c7.card[2].setDecor(Card::Diamond;
    c7.card[2].setNum(Num_4;
    c7.card[3].setDecor(Card::Club;
    c7.card[3].setNum(Num_4;
    c7.card[4].setDecor(Card::Club;
    c7.card[4].setNum(Num_7;
    c7.status=FourOfaKind;

    //葫芦
    c6.card[0].setDecor(Card::Spade;
    c6.card[0].setNum(Num_4;
    c6.card[1].setDecor(Card::Heart;
    c6.card[1].setNum(Num_4;
    c6.card[2].setDecor(Card::Diamond;
    c6.card[2].setNum(Num_4;
    c6.card[3].setDecor(Card::Club;
    c6.card[3].setNum(Num_7;
    c6.card[4].setDecor(Card::Diamond;
    c6.card[4].setNum(Num_7;
    c6.status=FullHouse;

    //同花 不能是顺子 不能是皇家同花顺
    c5.card[0].setDecor(Card::Heart;
    c5.card[0].setNum(Num_2;
    c5.card[1].setDecor(Card::Heart;
    c5.card[1].setNum(Num_4;
    c5.card[2].setDecor(Card::Heart;
    c5.card[2].setNum(Num_8;
    c5.card[3].setDecor(Card::Heart;
    c5.card[3].setNum(Num_K;
    c5.card[4].setDecor(Card::Heart;
    c5.card[4].setNum(Num_Q;
    c5.status=Flush;

    //顺子不能是同花、不能是皇家同花顺
    c4.card[0].setDecor(Card::Club;
    c4.card[0].setNum(Num_5;
    c4.card[1].setDecor(Card::Heart;
    c4.card[1].setNum(Num_4;
    c4.card[2].setDecor(Card::Spade;
    c4.card[2].setNum(Num_6;
    c4.card[3].setDecor(Card::Diamond;
    c4.card[3].setNum(Num_8;
    c4.card[4].setDecor(Card::Club;
    c4.card[4].setNum(Num_7;
    c4.status=Straight;

    //三条不能是葫芦不能是四条
    c3.card[0].setDecor(Card::Spade;
    c3.card[0].setNum(Num_4;
    c3.card[1].setDecor(Card::Heart;
    c3.card[1].setNum(Num_4;
    c3.card[2].setDecor(Card::Diamond;
    c3.card[2].setNum(Num_4;
    c3.card[3].setDecor(Card::Club;
    c3.card[3].setNum(Num_8;
    c3.card[4].setDecor(Card::Diamond;
    c3.card[4].setNum(Num_7;
    c3.status=ThreeOfaKind;

    //两对
    c2.card[0].setDecor(Card::Spade;
    c2.card[0].setNum(Num_4;
    c2.card[1].setDecor(Card::Heart;
    c2.card[1].setNum(Num_4;
    c2.card[2].setDecor(Card::Diamond;
    c2.card[2].setNum(Num_9;
    c2.card[3].setDecor(Card::Club;
    c2.card[3].setNum(Num_7;
    c2.card[4].setDecor(Card::Diamond;
    c2.card[4].setNum(Num_7;
    c2.status=TwoPair;

    //一对不能含两对和葫芦
    c1.card[0].setDecor(Card::Spade;
    c1.card[0].setNum(Num_4;
    c1.card[1].setDecor(Card::Heart;
    c1.card[1].setNum(Num_4;
    c1.card[2].setDecor(Card::Diamond;
    c1.card[2].setNum(Num_9;
    c1.card[3].setDecor(Card::Club;
    c1.card[3].setNum(Num_8;
    c1.card[4].setDecor(Card::Diamond;
    c1.card[4].setNum(Num_7;
    c1.status=OnePair;

    //高牌，什么也不是
    c0.card[0].setDecor(Card::Spade;
    c0.card[0].setNum(Num_A;
    c0.card[1].setDecor(Card::Heart;
    c0.card[1].setNum(Num_9;
    c0.card[2].setDecor(Card::Diamond;
    c0.card[2].setNum(Num_8;
    c0.card[3].setDecor(Card::Club;
    c0.card[3].setNum(Num_7;
    c0.card[4].setDecor(Card::Diamond;
    c0.card[4].setNum(Num_4;
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
    c9.card[0].setDecor(Card::Spade;
    c9.card[0].setNum(Num_10;
    c9.card[1].setDecor(Card::Spade;
    c9.card[1].setNum(Num_J;
    c9.card[2].setDecor(Card::Spade;
    c9.card[2].setNum(Num_Q;
    c9.card[3].setDecor(Card::Spade;
    c9.card[3].setNum(Num_K;
    c9.card[4].setDecor(Card::Spade;
    c9.card[4].setNum(Num_A;
    c9.status=RoyalFlush;

    //同花顺 不能是皇家同花顺
    c8.card[0].setDecor(Card::Spade;
    c8.card[0].setNum(Num_4;
    c8.card[1].setDecor(Card::Spade;
    c8.card[1].setNum(Num_3;
    c8.card[2].setDecor(Card::Spade;
    c8.card[2].setNum(Num_5;
    c8.card[3].setDecor(Card::Spade;
    c8.card[3].setNum(Num_6;
    c8.card[4].setDecor(Card::Spade;
    c8.card[4].setNum(Num_7;
    c8.status=StraightFlush;

    //四条
    c7.card[0].setDecor(Card::Spade;
    c7.card[0].setNum(Num_4;
    c7.card[1].setDecor(Card::Heart;
    c7.card[1].setNum(Num_4;
    c7.card[2].setDecor(Card::Diamond;
    c7.card[2].setNum(Num_4;
    c7.card[3].setDecor(Card::Club;
    c7.card[3].setNum(Num_4;
    c7.card[4].setDecor(Card::Club;
    c7.card[4].setNum(Num_7;
    c7.status=FourOfaKind;

    //葫芦
    c6.card[0].setDecor(Card::Spade;
    c6.card[0].setNum(Num_4;
    c6.card[1].setDecor(Card::Heart;
    c6.card[1].setNum(Num_4;
    c6.card[2].setDecor(Card::Diamond;
    c6.card[2].setNum(Num_4;
    c6.card[3].setDecor(Card::Club;
    c6.card[3].setNum(Num_7;
    c6.card[4].setDecor(Card::Diamond;
    c6.card[4].setNum(Num_7;
    c6.status=FullHouse;

    //同花 不能是顺子 不能是皇家同花顺
    c5.card[0].setDecor(Card::Heart;
    c5.card[0].setNum(Num_2;
    c5.card[1].setDecor(Card::Heart;
    c5.card[1].setNum(Num_4;
    c5.card[2].setDecor(Card::Heart;
    c5.card[2].setNum(Num_8;
    c5.card[3].setDecor(Card::Heart;
    c5.card[3].setNum(Num_K;
    c5.card[4].setDecor(Card::Heart;
    c5.card[4].setNum(Num_Q;
    c5.status=Flush;

    //顺子不能是同花、不能是皇家同花顺
    c4.card[0].setDecor(Card::Club;
    c4.card[0].setNum(Num_5;
    c4.card[1].setDecor(Card::Heart;
    c4.card[1].setNum(Num_4;
    c4.card[2].setDecor(Card::Spade;
    c4.card[2].setNum(Num_6;
    c4.card[3].setDecor(Card::Diamond;
    c4.card[3].setNum(Num_8;
    c4.card[4].setDecor(Card::Club;
    c4.card[4].setNum(Num_7;
    c4.status=Straight;

    //三条不能是葫芦不能是四条
    c3.card[0].setDecor(Card::Spade;
    c3.card[0].setNum(Num_4;
    c3.card[1].setDecor(Card::Heart;
    c3.card[1].setNum(Num_4;
    c3.card[2].setDecor(Card::Diamond;
    c3.card[2].setNum(Num_4;
    c3.card[3].setDecor(Card::Club;
    c3.card[3].setNum(Num_8;
    c3.card[4].setDecor(Card::Diamond;
    c3.card[4].setNum(Num_7;
    c3.status=ThreeOfaKind;

    //两对
    c2.card[0].setDecor(Card::Spade;
    c2.card[0].setNum(Num_4;
    c2.card[1].setDecor(Card::Heart;
    c2.card[1].setNum(Num_4;
    c2.card[2].setDecor(Card::Diamond;
    c2.card[2].setNum(Num_9;
    c2.card[3].setDecor(Card::Club;
    c2.card[3].setNum(Num_7;
    c2.card[4].setDecor(Card::Diamond;
    c2.card[4].setNum(Num_7;
    c2.status=TwoPair;

    //一对不能含两对和葫芦
    c1.card[0].setDecor(Card::Spade;
    c1.card[0].setNum(Num_4;
    c1.card[1].setDecor(Card::Heart;
    c1.card[1].setNum(Num_4;
    c1.card[2].setDecor(Card::Diamond;
    c1.card[2].setNum(Num_9;
    c1.card[3].setDecor(Card::Club;
    c1.card[3].setNum(Num_8;
    c1.card[4].setDecor(Card::Diamond;
    c1.card[4].setNum(Num_7;
    c1.status=OnePair;

    //高牌，什么也不是
    c0.card[0].setDecor(Card::Spade;
    c0.card[0].setNum(Num_A;
    c0.card[1].setDecor(Card::Heart;
    c0.card[1].setNum(Num_9;
    c0.card[2].setDecor(Card::Diamond;
    c0.card[2].setNum(Num_8;
    c0.card[3].setDecor(Card::Club;
    c0.card[3].setNum(Num_7;
    c0.card[4].setDecor(Card::Diamond;
    c0.card[4].setNum(Num_4;
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
    c0.card[0].setDecor(Card::Spade;
    c0.card[0].setNum(Num_A;
    c0.card[1].setDecor(Card::Heart;
    c0.card[1].setNum(Num_9;
    c0.card[2].setDecor(Card::Diamond;
    c0.card[2].setNum(Num_8;
    c0.card[3].setDecor(Card::Club;
    c0.card[3].setNum(Num_7;
    c0.card[4].setDecor(Card::Diamond;
    c0.card[4].setNum(Num_4;
    c0.status=HighCard;
    // A > B
    Cards temp;
    temp.card[0].setDecor(Card::Diamond;
    temp.card[0].setNum(Num_A;
    temp.card[1].setDecor(Card::Spade;
    temp.card[1].setNum(Num_J;
    temp.card[2].setDecor(Card::Club;
    temp.card[2].setNum(Num_6;
    temp.card[3].setDecor(Card::Spade;
    temp.card[3].setNum(Num_4;
    temp.card[4].setDecor(Card::Heart;
    temp.card[4].setNum(Num_2;
    temp.status=HighCard;
    QVERIFY(CardsCompare(temp,c0)==1);
    // A<B
    QVERIFY(CardsCompare(c0,temp)==2);
    // A==B
    temp.card[0].setDecor(Card::Diamond;
    temp.card[0].setNum(Num_A;
    temp.card[1].setDecor(Card::Spade;
    temp.card[1].setNum(Num_9;
    temp.card[2].setDecor(Card::Club;
    temp.card[2].setNum(Num_8;
    temp.card[3].setDecor(Card::Spade;
    temp.card[3].setNum(Num_7;
    temp.card[4].setDecor(Card::Heart;
    temp.card[4].setNum(Num_4;
    temp.status=HighCard;
    QVERIFY(CardsCompare(temp,c0)==0);
}

void TexasPokerTest::case_OnePairCompare()
{
    // A > B 对子大
    Cards c1;
    c1.card[0].setDecor(Card::Diamond;
    c1.card[0].setNum(Num_A;
    c1.card[1].setDecor(Card::Spade;
    c1.card[1].setNum(Num_A;
    c1.card[2].setDecor(Card::Club;
    c1.card[2].setNum(Num_J;
    c1.card[3].setDecor(Card::Spade;
    c1.card[3].setNum(Num_8;
    c1.card[4].setDecor(Card::Heart;
    c1.card[4].setNum(Num_6;
    c1.status=OnePair;
    c1.Data.pair.pairc=Num_A;
    c1.Data.pair.c[0]=Num_J;
    c1.Data.pair.c[1]=Num_8;
    c1.Data.pair.c[2]=Num_6;

    Cards temp;
    temp.card[0].setDecor(Card::Diamond;
    temp.card[0].setNum(Num_2;
    temp.card[1].setDecor(Card::Spade;
    temp.card[1].setNum(Num_2;
    temp.card[2].setDecor(Card::Club;
    temp.card[2].setNum(Num_A;
    temp.card[3].setDecor(Card::Spade;
    temp.card[3].setNum(Num_J;
    temp.card[4].setDecor(Card::Heart;
    temp.card[4].setNum(Num_6;
    temp.status=OnePair;
    temp.Data.pair.pairc=Num_2;
    temp.Data.pair.c[0]=Num_A;
    temp.Data.pair.c[1]=Num_J;
    temp.Data.pair.c[2]=Num_A;
    QVERIFY(CardsCompare(c1,temp)==1);//a > b
    QVERIFY(CardsCompare(temp,c1)==2);//a < b
    // A > B 对子一样 但是单牌大
    temp.card[0].setDecor(Card::Diamond;
    temp.card[0].setNum(Num_A;
    temp.card[1].setDecor(Card::Spade;
    temp.card[1].setNum(Num_A;
    temp.card[2].setDecor(Card::Club;
    temp.card[2].setNum(Num_J;
    temp.card[3].setDecor(Card::Spade;
    temp.card[3].setNum(Num_8;
    temp.card[4].setDecor(Card::Heart;
    temp.card[4].setNum(Num_4;
    temp.status=OnePair;
    temp.Data.pair.pairc=Num_A;
    temp.Data.pair.c[0]=Num_J;
    temp.Data.pair.c[1]=Num_8;
    temp.Data.pair.c[2]=Num_4;
    QVERIFY(CardsCompare(c1,temp)==1);//a > b
    QVERIFY(CardsCompare(temp,c1)==2);//a < b
    // A = B
    temp.card[0].setDecor(Card::Diamond;
    temp.card[0].setNum(Num_A;
    temp.card[1].setDecor(Card::Spade;
    temp.card[1].setNum(Num_A;
    temp.card[2].setDecor(Card::Club;
    temp.card[2].setNum(Num_J;
    temp.card[3].setDecor(Card::Spade;
    temp.card[3].setNum(Num_8;
    temp.card[4].setDecor(Card::Heart;
    temp.card[4].setNum(Num_7;
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
    c1.card[0].setDecor(Card::Diamond;
    c1.card[0].setNum(Num_A;
    c1.card[1].setDecor(Card::Spade;
    c1.card[1].setNum(Num_A;
    c1.card[2].setDecor(Card::Club;
    c1.card[2].setNum(Num_J;
    c1.card[3].setDecor(Card::Spade;
    c1.card[3].setNum(Num_J;
    c1.card[4].setDecor(Card::Heart;
    c1.card[4].setNum(Num_6;
    c1.status=TwoPair;
    c1.Data.pairs.pairc1=Num_A;
    c1.Data.pairs.pairc2=Num_J;
    c1.Data.pairs.c=Num_6;

    Cards c2;
    c2.card[0].setDecor(Card::Diamond;
    c2.card[0].setNum(Num_J;
    c2.card[1].setDecor(Card::Spade;
    c2.card[1].setNum(Num_J;
    c2.card[2].setDecor(Card::Club;
    c2.card[2].setNum(Num_8;
    c2.card[3].setDecor(Card::Spade;
    c2.card[3].setNum(Num_8;
    c2.card[4].setDecor(Card::Heart;
    c2.card[4].setNum(Num_6;
    c2.status=TwoPair;
    c2.Data.pairs.pairc1=Num_J;
    c2.Data.pairs.pairc2=Num_8;
    c2.Data.pairs.c=Num_6;
    QVERIFY(CardsCompare(c1,c2)==1);//A>B
    QVERIFY(CardsCompare(c2,c1)==2);//A<B

    // A > B 对子一样大，单牌不一样大
    Cards c3;
    c3.card[0].setDecor(Card::Diamond;
    c3.card[0].setNum(Num_A;
    c3.card[1].setDecor(Card::Spade;
    c3.card[1].setNum(Num_A;
    c3.card[2].setDecor(Card::Club;
    c3.card[2].setNum(Num_J;
    c3.card[3].setDecor(Card::Spade;
    c3.card[3].setNum(Num_J;
    c3.card[4].setDecor(Card::Heart;
    c3.card[4].setNum(Num_2;
    c3.status=TwoPair;
    c3.Data.pairs.pairc1=Num_A;
    c3.Data.pairs.pairc2=Num_J;
    c3.Data.pairs.c=Num_2;
    QVERIFY(CardsCompare(c1,c3)==1);//A>B
    QVERIFY(CardsCompare(c3,c1)==2);//A<B

    // A = B
    Cards c4;
    c4.card[0].setDecor(Card::Diamond;
    c4.card[0].setNum(Num_A;
    c4.card[1].setDecor(Card::Spade;
    c4.card[1].setNum(Num_A;
    c4.card[2].setDecor(Card::Club;
    c4.card[2].setNum(Num_J;
    c4.card[3].setDecor(Card::Spade;
    c4.card[3].setNum(Num_J;
    c4.card[4].setDecor(Card::Heart;
    c4.card[4].setNum(Num_6;
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
    c1.card[0].setDecor(Card::Diamond;
    c1.card[0].setNum(Num_A;
    c1.card[1].setDecor(Card::Spade;
    c1.card[1].setNum(Num_A;
    c1.card[2].setDecor(Card::Club;
    c1.card[2].setNum(Num_A;
    c1.card[3].setDecor(Card::Spade;
    c1.card[3].setNum(Num_J;
    c1.card[4].setDecor(Card::Heart;
    c1.card[4].setNum(Num_6;
    c1.status=ThreeOfaKind;
    c1.Data.three.threec=Num_A;
    c1.Data.three.c[0]=Num_J;
    c1.Data.three.c[1]=Num_6;

    Cards c2;
    c2.card[0].setDecor(Card::Diamond;
    c2.card[0].setNum(Num_J;
    c2.card[1].setDecor(Card::Spade;
    c2.card[1].setNum(Num_J;
    c2.card[2].setDecor(Card::Club;
    c2.card[2].setNum(Num_J;
    c2.card[3].setDecor(Card::Spade;
    c2.card[3].setNum(Num_8;
    c2.card[4].setDecor(Card::Heart;
    c2.card[4].setNum(Num_6;
    c2.status=ThreeOfaKind;
    c2.Data.three.threec=Num_J;
    c2.Data.three.c[0]=Num_8;
    c2.Data.three.c[1]=Num_6;
    QVERIFY(CardsCompare(c1,c2)==1);//A>B
    QVERIFY(CardsCompare(c2,c1)==2);//A<B

    // A > B 三条一样大，单牌不一样大
    Cards c3;
    c3.card[0].setDecor(Card::Diamond;
    c3.card[0].setNum(Num_A;
    c3.card[1].setDecor(Card::Spade;
    c3.card[1].setNum(Num_A;
    c3.card[2].setDecor(Card::Club;
    c3.card[2].setNum(Num_A;
    c3.card[3].setDecor(Card::Spade;
    c3.card[3].setNum(Num_J;
    c3.card[4].setDecor(Card::Heart;
    c3.card[4].setNum(Num_2;
    c3.status=ThreeOfaKind;
    c3.Data.three.threec=Num_A;
    c3.Data.three.c[0]=Num_J;
    c3.Data.three.c[1]=Num_2;
    QVERIFY(CardsCompare(c1,c3)==1);//A>B
    QVERIFY(CardsCompare(c3,c1)==2);//A<B

    // A = B
    Cards c4;
    c4.card[0].setDecor(Card::Diamond;
    c4.card[0].setNum(Num_A;
    c4.card[1].setDecor(Card::Spade;
    c4.card[1].setNum(Num_A;
    c4.card[2].setDecor(Card::Club;
    c4.card[2].setNum(Num_A;
    c4.card[3].setDecor(Card::Spade;
    c4.card[3].setNum(Num_J;
    c4.card[4].setDecor(Card::Heart;
    c4.card[4].setNum(Num_6;
    c4.status=ThreeOfaKind;
    c4.Data.three.threec=Num_A;
    c4.Data.three.c[0]=Num_J;
    c4.Data.three.c[1]=Num_6;
    QVERIFY(CardsCompare(c1,c4)==0);//A=B
}

void TexasPokerTest::case_StraightCompare()
{
    // A > B 顺子比较大
    Cards c1;
    c1.card[0].setDecor(Card::Diamond;
    c1.card[0].setNum(Num_A;
    c1.card[1].setDecor(Card::Spade;
    c1.card[1].setNum(Num_K;
    c1.card[2].setDecor(Card::Club;
    c1.card[2].setNum(Num_Q;
    c1.card[3].setDecor(Card::Spade;
    c1.card[3].setNum(Num_J;
    c1.card[4].setDecor(Card::Heart;
    c1.card[4].setNum(Num_10;
    c1.status=Straight;
    c1.Data.straight.start = Num_A;
    c1.Data.straight.end = Num_10;

    Cards c2;
    c2.card[0].setDecor(Card::Diamond;
    c2.card[0].setNum(Num_J;
    c2.card[1].setDecor(Card::Spade;
    c2.card[1].setNum(Num_10;
    c2.card[2].setDecor(Card::Club;
    c2.card[2].setNum(Num_9;
    c2.card[3].setDecor(Card::Spade;
    c2.card[3].setNum(Num_8;
    c2.card[4].setDecor(Card::Heart;
    c2.card[4].setNum(Num_7;
    c2.status=Straight;
    c2.Data.straight.start = Num_J;
    c2.Data.straight.end = Num_7;
    QVERIFY(CardsCompare(c1,c2)==1);//A>B
    QVERIFY(CardsCompare(c2,c1)==2);//A<B

    // A = B
    Cards c3;
    c3.card[0].setDecor(Card::Diamond;
    c3.card[0].setNum(Num_A;
    c3.card[1].setDecor(Card::Spade;
    c3.card[1].setNum(Num_K;
    c3.card[2].setDecor(Card::Club;
    c3.card[2].setNum(Num_Q;
    c3.card[3].setDecor(Card::Spade;
    c3.card[3].setNum(Num_J;
    c3.card[4].setDecor(Card::Heart;
    c3.card[4].setNum(Num_10;
    c3.status=Straight;
    c3.Data.straight.start = Num_A;
    c3.Data.straight.end = Num_10;
    QVERIFY(CardsCompare(c1,c3)==0);//A=B
}

void TexasPokerTest::case_FlushCompare()
{
    // A > B 单牌比较大
    Cards c1;
    c1.card[0].setDecor(Card::Diamond;
    c1.card[0].setNum(Num_A;
    c1.card[1].setDecor(Card::Diamond;
    c1.card[1].setNum(Num_J;
    c1.card[2].setDecor(Card::Diamond;
    c1.card[2].setNum(Num_8;
    c1.card[3].setDecor(Card::Diamond;
    c1.card[3].setNum(Num_5;
    c1.card[4].setDecor(Card::Diamond;
    c1.card[4].setNum(Num_2;
    c1.status=Flush;

    Cards c2;
    c2.card[0].setDecor(Card::Spade;
    c2.card[0].setNum(Num_J;
    c2.card[1].setDecor(Card::Spade;
    c2.card[1].setNum(Num_10;
    c2.card[2].setDecor(Card::Spade;
    c2.card[2].setNum(Num_9;
    c2.card[3].setDecor(Card::Spade;
    c2.card[3].setNum(Num_4;
    c2.card[4].setDecor(Card::Spade;
    c2.card[4].setNum(Num_3;
    c2.status=Flush;
    QVERIFY(CardsCompare(c1,c2)==1);//A>B
    QVERIFY(CardsCompare(c2,c1)==2);//A<B

    // A = B
    Cards c3;
    c3.card[0].setDecor(Card::Club;
    c3.card[0].setNum(Num_A;
    c3.card[1].setDecor(Card::Club;
    c3.card[1].setNum(Num_J;
    c3.card[2].setDecor(Card::Club;
    c3.card[2].setNum(Num_8;
    c3.card[3].setDecor(Card::Club;
    c3.card[3].setNum(Num_5;
    c3.card[4].setDecor(Card::Club;
    c3.card[4].setNum(Num_2;
    c3.status=Flush;
    QVERIFY(CardsCompare(c1,c3)==0);//A=B
}

void TexasPokerTest::case_FullhouseCompare()
{
    // A > B 三条比较大
    Cards c1;
    c1.card[0].setDecor(Card::Diamond;
    c1.card[0].setNum(Num_A;
    c1.card[1].setDecor(Card::Spade;
    c1.card[1].setNum(Num_A;
    c1.card[2].setDecor(Card::Club;
    c1.card[2].setNum(Num_A;
    c1.card[3].setDecor(Card::Heart;
    c1.card[3].setNum(Num_5;
    c1.card[4].setDecor(Card::Diamond;
    c1.card[4].setNum(Num_5;
    c1.status=FullHouse;
    c1.Data.full.threec = Num_A;
    c1.Data.full.pair = Num_5;

    Cards c2;
    c2.card[0].setDecor(Card::Spade;
    c2.card[0].setNum(Num_J;
    c2.card[1].setDecor(Card::Heart;
    c2.card[1].setNum(Num_J;
    c2.card[2].setDecor(Card::Club;
    c2.card[2].setNum(Num_J;
    c2.card[3].setDecor(Card::Club;
    c2.card[3].setNum(Num_4;
    c2.card[4].setDecor(Card::Spade;
    c2.card[4].setNum(Num_4;
    c2.status=FullHouse;
    c2.Data.full.threec = Num_J;
    c2.Data.full.pair = Num_4;
    QVERIFY(CardsCompare(c1,c2)==1);//A>B
    QVERIFY(CardsCompare(c2,c1)==2);//A<B

    // A > B 对子比较大
    Cards c3;
    c3.card[0].setDecor(Card::Spade;
    c3.card[0].setNum(Num_A;
    c3.card[1].setDecor(Card::Diamond;
    c3.card[1].setNum(Num_A;
    c3.card[2].setDecor(Card::Club;
    c3.card[2].setNum(Num_A;
    c3.card[3].setDecor(Card::Spade;
    c3.card[3].setNum(Num_4;
    c3.card[4].setDecor(Card::Club;
    c3.card[4].setNum(Num_4;
    c3.status=FullHouse;
    c3.Data.full.threec = Num_A;
    c3.Data.full.pair = Num_4;
    QVERIFY(CardsCompare(c1,c3)==1);//A>B
    QVERIFY(CardsCompare(c3,c1)==2);//A<B

    // A = B
    Cards c4;
    c4.card[0].setDecor(Card::Club;
    c4.card[0].setNum(Num_A;
    c4.card[1].setDecor(Card::Spade;
    c4.card[1].setNum(Num_A;
    c4.card[2].setDecor(Card::Diamond;
    c4.card[2].setNum(Num_A;
    c4.card[3].setDecor(Card::Club;
    c4.card[3].setNum(Num_5;
    c4.card[4].setDecor(Card::Diamond;
    c4.card[4].setNum(Num_5;
    c4.status=FullHouse;
    c4.Data.full.threec = Num_A;
    c4.Data.full.pair = Num_5;
    QVERIFY(CardsCompare(c1,c4)==0);//A=B
}

void TexasPokerTest::case_FourCompare()
{
    // A > B 四条比较大
    Cards c1;
    c1.card[0].setDecor(Card::Diamond;
    c1.card[0].setNum(Num_A;
    c1.card[1].setDecor(Card::Spade;
    c1.card[1].setNum(Num_A;
    c1.card[2].setDecor(Card::Club;
    c1.card[2].setNum(Num_A;
    c1.card[3].setDecor(Card::Heart;
    c1.card[3].setNum(Num_A;
    c1.card[4].setDecor(Card::Diamond;
    c1.card[4].setNum(Num_5;
    c1.status=FourOfaKind;
    c1.Data.four.fourc = Num_A;
    c1.Data.four.c = Num_5;

    Cards c2;
    c2.card[0].setDecor(Card::Spade;
    c2.card[0].setNum(Num_J;
    c2.card[1].setDecor(Card::Heart;
    c2.card[1].setNum(Num_J;
    c2.card[2].setDecor(Card::Club;
    c2.card[2].setNum(Num_J;
    c2.card[3].setDecor(Card::Diamond;
    c2.card[3].setNum(Num_J;
    c2.card[4].setDecor(Card::Spade;
    c2.card[4].setNum(Num_4;
    c2.status=FourOfaKind;
    c2.Data.four.fourc = Num_J;
    c2.Data.four.c = Num_4;
    QVERIFY(CardsCompare(c1,c2)==1);//A>B
    QVERIFY(CardsCompare(c2,c1)==2);//A<B

    // A > B 单牌比较大
    Cards c3;
    c3.card[0].setDecor(Card::Spade;
    c3.card[0].setNum(Num_A;
    c3.card[1].setDecor(Card::Diamond;
    c3.card[1].setNum(Num_A;
    c3.card[2].setDecor(Card::Club;
    c3.card[2].setNum(Num_A;
    c3.card[3].setDecor(Card::Spade;
    c3.card[3].setNum(Num_A;
    c3.card[4].setDecor(Card::Club;
    c3.card[4].setNum(Num_4;
    c3.status=FourOfaKind;
    c3.Data.four.fourc = Num_A;
    c3.Data.four.c = Num_4;
    QVERIFY(CardsCompare(c1,c3)==1);//A>B
    QVERIFY(CardsCompare(c3,c1)==2);//A<B

    // A = B
    Cards c4;
    c4.card[0].setDecor(Card::Club;
    c4.card[0].setNum(Num_A;
    c4.card[1].setDecor(Card::Spade;
    c4.card[1].setNum(Num_A;
    c4.card[2].setDecor(Card::Diamond;
    c4.card[2].setNum(Num_A;
    c4.card[3].setDecor(Card::Club;
    c4.card[3].setNum(Num_A;
    c4.card[4].setDecor(Card::Diamond;
    c4.card[4].setNum(Num_5;
    c4.status=FourOfaKind;
    c4.Data.four.fourc = Num_A;
    c4.Data.four.c = Num_5;
    QVERIFY(CardsCompare(c1,c4)==0);//A=B
}

void TexasPokerTest::case_StraightFlushCompare()
{
    // A > B 顺子比较大
    Cards c1;
    c1.card[0].setDecor(Card::Diamond;
    c1.card[0].setNum(Num_A;
    c1.card[1].setDecor(Card::Diamond;
    c1.card[1].setNum(Num_K;
    c1.card[2].setDecor(Card::Diamond;
    c1.card[2].setNum(Num_Q;
    c1.card[3].setDecor(Card::Diamond;
    c1.card[3].setNum(Num_J;
    c1.card[4].setDecor(Card::Diamond;
    c1.card[4].setNum(Num_10;
    c1.status=StraightFlush;
    c1.Data.straight.start = Num_A;
    c1.Data.straight.end = Num_10;

    Cards c2;
    c2.card[0].setDecor(Card::Spade;
    c2.card[0].setNum(Num_J;
    c2.card[1].setDecor(Card::Spade;
    c2.card[1].setNum(Num_10;
    c2.card[2].setDecor(Card::Spade;
    c2.card[2].setNum(Num_9;
    c2.card[3].setDecor(Card::Spade;
    c2.card[3].setNum(Num_8;
    c2.card[4].setDecor(Card::Spade;
    c2.card[4].setNum(Num_7;
    c2.status=StraightFlush;
    c2.Data.straight.start = Num_J;
    c2.Data.straight.end = Num_7;
    QVERIFY(CardsCompare(c1,c2)==1);//A>B
    QVERIFY(CardsCompare(c2,c1)==2);//A<B

    // A = B
    Cards c3;
    c3.card[0].setDecor(Card::Club;
    c3.card[0].setNum(Num_A;
    c3.card[1].setDecor(Card::Club;
    c3.card[1].setNum(Num_K;
    c3.card[2].setDecor(Card::Club;
    c3.card[2].setNum(Num_Q;
    c3.card[3].setDecor(Card::Club;
    c3.card[3].setNum(Num_J;
    c3.card[4].setDecor(Card::Club;
    c3.card[4].setNum(Num_10;
    c3.status=StraightFlush;
    c3.Data.straight.start = Num_A;
    c3.Data.straight.end = Num_10;
    QVERIFY(CardsCompare(c1,c3)==0);//A=B
}

void TexasPokerTest::case_check7Cards_HighCards()
{
    Cards output;//输出结果
    QList<Card> high;
    Card c1;
    c1.setDecor(Spade;
    c1.setNum(Num_A;
    high.append(c1);
    Card c2;
    c2.setDecor(Club;
    c2.setNum(Num_Q;
    high.append(c2);
    Card c3;
    c3.setDecor(Diamond;
    c3.setNum(Num_10;
    high.append(c3);
    Card c4;
    c4.setDecor(Heart;
    c4.setNum(Num_9;
    high.append(c4);
    Card c5;
    c5.setDecor(Spade;
    c5.setNum(Num_6;
    high.append(c5);
    Card c6;
    c6.setDecor(Club;
    c6.setNum(Num_5;
    high.append(c6);
    Card c7;
    c7.setDecor(Heart;
    c7.setNum(Num_2;
    high.append(c7);

    check7Cards(high,output);
    QVERIFY(output.status==HighCard);
    QVERIFY(output.card[0].setNum(=Num_A);
    QVERIFY(output.card[1].setNum(=Num_Q);
    QVERIFY(output.card[2].setNum(=Num_10);
    QVERIFY(output.card[3].setNum(=Num_9);
    QVERIFY(output.card[4].setNum(=Num_6);
    //*-同花顺
    //*-皇家同花顺
}

void TexasPokerTest::case_check7Cards_OnePair()
{
    Cards output;//输出结果
    QList<Card> high;
    Card c1;
    c1.setDecor(Spade;
    c1.setNum(Num_A;
    high.append(c1);
    Card c2;
    c2.setDecor(Club;
    c2.setNum(Num_Q;
    high.append(c2);
    Card c3;
    c3.setDecor(Diamond;
    c3.setNum(Num_10;
    high.append(c3);
    Card c4;
    c4.setDecor(Heart;
    c4.setNum(Num_9;
    high.append(c4);
    Card c5;
    c5.setDecor(Club;
    c5.setNum(Num_A;
    high.append(c5);
    Card c6;
    c6.setDecor(Club;
    c6.setNum(Num_5;
    high.append(c6);
    Card c7;
    c7.setDecor(Heart;
    c7.setNum(Num_2;
    high.append(c7);

    check7Cards(high,output);
    QVERIFY(output.status==OnePair);
    QVERIFY(output.card[0].setNum(=Num_A);
    QVERIFY(output.card[1].setNum(=Num_A);
    QVERIFY(output.card[2].setNum(=Num_Q);
    QVERIFY(output.card[3].setNum(=Num_10);
    QVERIFY(output.card[4].setNum(=Num_9);
}

void TexasPokerTest::case_check7Cards_TwoPair()
{
    Cards output;//输出结果
    QList<Card> high;
    Card c1;
    c1.setDecor(Spade;
    c1.setNum(Num_A;
    high.append(c1);
    Card c2;
    c2.setDecor(Club;
    c2.setNum(Num_Q;
    high.append(c2);
    Card c3;
    c3.setDecor(Diamond;
    c3.setNum(Num_10;
    high.append(c3);
    Card c4;
    c4.setDecor(Heart;
    c4.setNum(Num_2;
    high.append(c4);
    Card c5;
    c5.setDecor(Club;
    c5.setNum(Num_A;
    high.append(c5);
    Card c6;
    c6.setDecor(Club;
    c6.setNum(Num_5;
    high.append(c6);
    Card c7;
    c7.setDecor(Heart;
    c7.setNum(Num_Q;
    high.append(c7);

    check7Cards(high,output);
    QVERIFY(output.status==TwoPair);
    QVERIFY(output.card[0].setNum(=Num_A);
    QVERIFY(output.card[1].setNum(=Num_A);
    QVERIFY(output.card[2].setNum(=Num_Q);
    QVERIFY(output.card[3].setNum(=Num_Q);
    QVERIFY(output.card[4].setNum(=Num_10);
}

void TexasPokerTest::case_check7Cards_Three()
{
    Cards output;//输出结果
    QList<Card> high;
    Card c1;
    c1.setDecor(Spade;
    c1.setNum(Num_A;
    high.append(c1);
    Card c2;
    c2.setDecor(Club;
    c2.setNum(Num_Q;
    high.append(c2);
    Card c3;
    c3.setDecor(Diamond;
    c3.setNum(Num_4;
    high.append(c3);
    Card c4;
    c4.setDecor(Heart;
    c4.setNum(Num_2;
    high.append(c4);
    Card c5;
    c5.setDecor(Club;
    c5.setNum(Num_A;
    high.append(c5);
    Card c6;
    c6.setDecor(Club;
    c6.setNum(Num_5;
    high.append(c6);
    Card c7;
    c7.setDecor(Heart;
    c7.setNum(Num_A;
    high.append(c7);

    check7Cards(high,output);
    QVERIFY(output.status==ThreeOfaKind);
    QVERIFY(output.card[0].setNum(=Num_A);
    QVERIFY(output.card[1].setNum(=Num_A);
    QVERIFY(output.card[2].setNum(=Num_A);
    QVERIFY(output.card[3].setNum(=Num_Q);
    QVERIFY(output.card[4].setNum(=Num_5);
}

void TexasPokerTest::case_check7Cards_Straight()
{
    Cards output;//输出结果
    QList<Card> high;
    Card c1;
    c1.setDecor(Spade;
    c1.setNum(Num_K;
    high.append(c1);
    Card c2;
    c2.setDecor(Club;
    c2.setNum(Num_Q;
    high.append(c2);
    Card c3;
    c3.setDecor(Diamond;
    c3.setNum(Num_10;
    high.append(c3);
    Card c4;
    c4.setDecor(Heart;
    c4.setNum(Num_J;
    high.append(c4);
    Card c5;
    c5.setDecor(Club;
    c5.setNum(Num_2;
    high.append(c5);
    Card c6;
    c6.setDecor(Club;
    c6.setNum(Num_5;
    high.append(c6);
    Card c7;
    c7.setDecor(Heart;
    c7.setNum(Num_9;
    high.append(c7);

    check7Cards(high,output);
    QVERIFY(output.status==Straight);
    QVERIFY(output.card[0].setNum(=Num_K);
    QVERIFY(output.card[1].setNum(=Num_Q);
    QVERIFY(output.card[2].setNum(=Num_J);
    QVERIFY(output.card[3].setNum(=Num_10);
    QVERIFY(output.card[4].setNum(=Num_9);
}

void TexasPokerTest::case_check7Cards_Flush()
{
    Cards output;//输出结果
    QList<Card> high;
    Card c1;
    c1.setDecor(Spade;
    c1.setNum(Num_K;
    high.append(c1);
    Card c2;
    c2.setDecor(Club;
    c2.setNum(Num_4;
    high.append(c2);
    Card c3;
    c3.setDecor(Club;
    c3.setNum(Num_10;
    high.append(c3);
    Card c4;
    c4.setDecor(Heart;
    c4.setNum(Num_J;
    high.append(c4);
    Card c5;
    c5.setDecor(Club;
    c5.setNum(Num_2;
    high.append(c5);
    Card c6;
    c6.setDecor(Club;
    c6.setNum(Num_5;
    high.append(c6);
    Card c7;
    c7.setDecor(Club;
    c7.setNum(Num_9;
    high.append(c7);

    check7Cards(high,output);
    QVERIFY(output.status==Flush);
    QVERIFY(output.card[0].setNum(=Num_10);
    QVERIFY(output.card[1].setNum(=Num_9);
    QVERIFY(output.card[2].setNum(=Num_5);
    QVERIFY(output.card[3].setNum(=Num_4);
    QVERIFY(output.card[4].setNum(=Num_2);
}

void TexasPokerTest::case_check7Cards_Fullhouse()
{
    Cards output;//输出结果
    QList<Card> high;
    Card c1;
    c1.setDecor(Spade;
    c1.setNum(Num_K;
    high.append(c1);
    Card c2;
    c2.setDecor(Club;
    c2.setNum(Num_4;
    high.append(c2);
    Card c3;
    c3.setDecor(Spade;
    c3.setNum(Num_10;
    high.append(c3);
    Card c4;
    c4.setDecor(Heart;
    c4.setNum(Num_J;
    high.append(c4);
    Card c5;
    c5.setDecor(Club;
    c5.setNum(Num_K;
    high.append(c5);
    Card c6;
    c6.setDecor(Club;
    c6.setNum(Num_J;
    high.append(c6);
    Card c7;
    c7.setDecor(Diamond;
    c7.setNum(Num_K;
    high.append(c7);

    check7Cards(high,output);
    QVERIFY(output.status==FullHouse);
    QVERIFY(output.card[0].setNum(=Num_K);
    QVERIFY(output.card[1].setNum(=Num_K);
    QVERIFY(output.card[2].setNum(=Num_K);
    QVERIFY(output.card[3].setNum(=Num_J);
    QVERIFY(output.card[4].setNum(=Num_J);
}

void TexasPokerTest::case_check7Cards_Four()
{
    Cards output;//输出结果
    QList<Card> high;
    Card c1;
    c1.setDecor(Spade;
    c1.setNum(Num_K;
    high.append(c1);
    Card c2;
    c2.setDecor(Heart;
    c2.setNum(Num_K;
    high.append(c2);
    Card c3;
    c3.setDecor(Spade;
    c3.setNum(Num_10;
    high.append(c3);
    Card c4;
    c4.setDecor(Heart;
    c4.setNum(Num_J;
    high.append(c4);
    Card c5;
    c5.setDecor(Club;
    c5.setNum(Num_K;
    high.append(c5);
    Card c6;
    c6.setDecor(Club;
    c6.setNum(Num_J;
    high.append(c6);
    Card c7;
    c7.setDecor(Diamond;
    c7.setNum(Num_K;
    high.append(c7);

    check7Cards(high,output);
    QVERIFY(output.status==FourOfaKind);
    QVERIFY(output.card[0].setNum(=Num_K);
    QVERIFY(output.card[1].setNum(=Num_K);
    QVERIFY(output.card[2].setNum(=Num_K);
    QVERIFY(output.card[3].setNum(=Num_K);
    QVERIFY(output.card[4].setNum(=Num_J);
}

void TexasPokerTest::case_check7Cards_StraightFlush()
{
    CompareCards cc;
    CompareCards::Cards output;//输出结果
    QList<Card> high;
    Card c1;
    c1.setDecor(Card::Heart;
    c1.setNum(Card::Num_2;
    high.append(c1);
    Card c2;
    c2.setDecor(Card::Heart;
    c2.setNum(Card::Num_4;
    high.append(c2);
    Card c3;
    c3.setDecor(Card::Heart;
    c3.setNum(Card::Num_10;
    high.append(c3);
    Card c4;
    c4.setDecor(Card::Heart;
    c4.setNum(Card::Num_J;
    high.append(c4);
    Card c5;
    c5.setDecor(Card::Heart;
    c5.setNum(Card::Num_Q;
    high.append(c5);
    Card c6;
    c6.setDecor(Card::Heart;
    c6.setNum(Card::Num_9;
    high.append(c6);
    Card c7;
    c7.setDecor(Card::Heart;
    c7.setNum(Card::Num_K;
    high.append(c7);

    cc.check7Cards(high,output);
    QVERIFY(output.status         ==CompareCards::StraightFlush);
    QVERIFY(output.card[0].num()==Card::Num_K);
    QVERIFY(output.card[1].setNum(=Card::Num_Q);
    QVERIFY(output.card[2].setNum(=Card::Num_J);
    QVERIFY(output.card[3].setNum(=Card::Num_10);
    QVERIFY(output.card[4].setNum(=Card::Num_9);
}

void TexasPokerTest::case_check7Cards_RoyalFlush()
{
    CompareCards cc;
    CompareCards::Cards output;//输出结果
    QList<Card> high;
    Card c1;
    c1.setDecor(Card::Heart;
    c1.setNum(Card::Num_2;
    high.append(c1);
    Card c2;
    c2.setDecor(Card::Heart;
    c2.setNum(Card::Num_A;
    high.append(c2);
    Card c3;
    c3.setDecor(Card::Heart;
    c3.setNum(Card::Num_10;
    high.append(c3);
    Card c4;
    c4.setDecor(Card::Heart;
    c4.setNum(Card::Num_J;
    high.append(c4);
    Card c5;
    c5.setDecor(Card::Heart;
    c5.setNum(Card::Num_Q;
    high.append(c5);
    Card c6;
    c6.setDecor(Card::Heart;
    c6.setNum(Card::Num_9;
    high.append(c6);
    Card c7;
    c7.setDecor(Card::Heart;
    c7.setNum(Card::Num_K;
    high.append(c7);

    cc.check7Cards(high,output);
    QVERIFY(output.status       ==CompareCards::RoyalFlush);
    QVERIFY(output.card[0].num()==Card::Num_A);
    QVERIFY(output.card[1].setNum(=Card::Num_K);
    QVERIFY(output.card[2].setNum(=Card::Num_Q);
    QVERIFY(output.card[3].setNum(=Card::Num_J);
    QVERIFY(output.card[4].setNum(=Card::Num_10);
}
