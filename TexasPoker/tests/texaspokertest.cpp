#include "texaspokertest.h"

TexasPokerTest::TexasPokerTest()
{
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
}

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
// WARNING 以下几个函数会将5张牌按由小到大进行排序
void TexasPokerTest::case_checkOnePair()
{
    QVERIFY(isOnePair(c9)==false);//皇家同花顺
    QVERIFY(isOnePair(c8)==false);//同花顺
    QVERIFY(isOnePair(c7)==false);//四条
    QVERIFY(isOnePair(c6)==false);//葫芦测试
    QVERIFY(isOnePair(c5)==false);//同花测试
    QVERIFY(isOnePair(c4)==false);//顺子测试
    QVERIFY(isOnePair(c3)==false);//三条测试
    QVERIFY(isOnePair(c2)==false);//两对测试
    QVERIFY(isOnePair(c1)==true);//一对测试
    QVERIFY(isOnePair(c0)==false);//高牌
}

void TexasPokerTest::case_checkTwoPair()
{
    QVERIFY(isTwoPair(c9)==false);//皇家同花顺
    QVERIFY(isTwoPair(c8)==false);//同花顺
    QVERIFY(isTwoPair(c7)==false);//四条
    QVERIFY(isTwoPair(c6)==false);//葫芦测试
    QVERIFY(isTwoPair(c5)==false);//同花测试
    QVERIFY(isTwoPair(c4)==false);//顺子测试
    QVERIFY(isTwoPair(c3)==false);//三条测试
    QVERIFY(isTwoPair(c2)==true);//两对测试
    QVERIFY(isTwoPair(c1)==false);//一对测试
    QVERIFY(isTwoPair(c0)==false);//高牌
}

void TexasPokerTest::case_checkThreeKind()
{
    QVERIFY(isThreeKind(c9)==false);//皇家同花顺
    QVERIFY(isThreeKind(c8)==false);//同花顺
    QVERIFY(isThreeKind(c7)==false);//四条
    QVERIFY(isThreeKind(c6)==false);//葫芦测试
    QVERIFY(isThreeKind(c5)==false);//同花测试
    QVERIFY(isThreeKind(c4)==false);//顺子测试
    QVERIFY(isThreeKind(c3)==true);//三条测试
    QVERIFY(isThreeKind(c2)==false);//两对测试
    QVERIFY(isThreeKind(c1)==false);//一对测试
    QVERIFY(isThreeKind(c0)==false);//高牌
}

void TexasPokerTest::case_checkStraight()
{
    QVERIFY(isStraight(c9)==true);//皇家同花顺
    QVERIFY(isStraight(c8)==true);//同花顺
    QVERIFY(isStraight(c7)==false);//四条
    QVERIFY(isStraight(c6)==false);//葫芦测试
    QVERIFY(isStraight(c5)==false);//同花测试
    QVERIFY(isStraight(c4)==true);//顺子测试
    QVERIFY(isStraight(c3)==false);//三条测试
    QVERIFY(isStraight(c2)==false);//两对测试
    QVERIFY(isStraight(c1)==false);//一对测试
    QVERIFY(isStraight(c0)==false);//高牌
}

//测试同花
void TexasPokerTest::case_checkFlush()
{
    QVERIFY(isFlush(c9)==true);//皇家同花顺
    QVERIFY(isFlush(c8)==true);//同花顺
    QVERIFY(isFlush(c7)==false);//四条
    QVERIFY(isFlush(c6)==false);//葫芦测试
    QVERIFY(isFlush(c5)==true);//同花测试
    QVERIFY(isFlush(c4)==false);//顺子测试
    QVERIFY(isFlush(c3)==false);//三条测试
    QVERIFY(isFlush(c2)==false);//两对测试
    QVERIFY(isFlush(c1)==false);//一对测试
    QVERIFY(isFlush(c0)==false);//高牌
}

//测试葫芦
void TexasPokerTest::case_checkFullhouse()
{
    QVERIFY(isFullHouse(c9)==false);//皇家同花顺
    QVERIFY(isFullHouse(c8)==false);//同花顺
    QVERIFY(isFullHouse(c7)==false);//四条
    QVERIFY(isFullHouse(c6)==true);//葫芦测试
    QVERIFY(isFullHouse(c5)==false);//同花测试
    QVERIFY(isFullHouse(c4)==false);//顺子测试
    QVERIFY(isFullHouse(c3)==false);//三条测试
    QVERIFY(isFullHouse(c2)==false);//两对测试
    QVERIFY(isFullHouse(c1)==false);//一对测试
    QVERIFY(isFullHouse(c0)==false);//高牌
}

//四条
void TexasPokerTest::case_checkFourKind()
{
    QVERIFY(isFourKing(c9)==false);//皇家同花顺
    QVERIFY(isFourKing(c8)==false);//同花顺
    QVERIFY(isFourKing(c7)==true);//四条
    QVERIFY(isFourKing(c6)==false);//葫芦测试
    QVERIFY(isFourKing(c5)==false);//同花测试
    QVERIFY(isFourKing(c4)==false);//顺子测试
    QVERIFY(isFourKing(c3)==false);//三条测试
    QVERIFY(isFourKing(c2)==false);//两对测试
    QVERIFY(isFourKing(c1)==false);//一对测试
    QVERIFY(isFourKing(c0)==false);//高牌
}

//测试最大是否为A
void TexasPokerTest::case_checkA()
{
    QVERIFY(isHighA(c9)==true);//皇家同花顺
    QVERIFY(isHighA(c8)==false);//同花顺
    QVERIFY(isHighA(c7)==false);//四条
    QVERIFY(isHighA(c6)==false);//葫芦测试
    QVERIFY(isHighA(c5)==false);//同花测试
    QVERIFY(isHighA(c4)==false);//顺子测试
    QVERIFY(isHighA(c3)==false);//三条测试
    QVERIFY(isHighA(c2)==false);//两对测试
    QVERIFY(isHighA(c1)==false);//一对测试
    QVERIFY(isHighA(c0)==true);//高牌
}

void TexasPokerTest::case_checkBrandType()
{
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
    // A > B
    Cards temp;
    temp.card[0].CardDecor=Decor::Diamond;
    temp.card[0].CardNum=Num_2;
    temp.card[1].CardDecor=Decor::Spade;
    temp.card[1].CardNum=Num_4;
    temp.card[2].CardDecor=Decor::Club;
    temp.card[2].CardNum=Num_6;
    temp.card[3].CardDecor=Decor::Spade;
    temp.card[3].CardNum=Num_J;
    temp.card[4].CardDecor=Decor::Heart;
    temp.card[4].CardNum=Num_A;
    temp.status=HighCard;
    QVERIFY(CardsCompare(temp,c0)==1);
    // A<B
    QVERIFY(CardsCompare(c0,temp)==2);
    // A==B
    temp.card[0].CardDecor=Decor::Diamond;
    temp.card[0].CardNum=Num_4;
    temp.card[1].CardDecor=Decor::Spade;
    temp.card[1].CardNum=Num_7;
    temp.card[2].CardDecor=Decor::Club;
    temp.card[2].CardNum=Num_8;
    temp.card[3].CardDecor=Decor::Spade;
    temp.card[3].CardNum=Num_9;
    temp.card[4].CardDecor=Decor::Heart;
    temp.card[4].CardNum=Num_A;
    temp.status=HighCard;
    QVERIFY(CardsCompare(temp,c0)==0);
}

void TexasPokerTest::case_OnePairCompare()
{
    // A > B 对子大
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
    temp.Data.pair.c[0]=Num_6;
    temp.Data.pair.c[1]=Num_J;
    temp.Data.pair.c[2]=Num_A;
    QVERIFY(CardsCompare(c1,temp)==1);//a > b
    QVERIFY(CardsCompare(temp,c1)==2);//a < b
    // A > B 对子一样 但是单牌大
    temp.card[0].CardDecor=Decor::Diamond;
    temp.card[0].CardNum=Num_4;
    temp.card[1].CardDecor=Decor::Spade;
    temp.card[1].CardNum=Num_4;
    temp.card[2].CardDecor=Decor::Club;
    temp.card[2].CardNum=Num_10;
    temp.card[3].CardDecor=Decor::Spade;
    temp.card[3].CardNum=Num_8;
    temp.card[4].CardDecor=Decor::Heart;
    temp.card[4].CardNum=Num_7;
    temp.status=OnePair;
    temp.Data.pair.pairc=Num_4;
    temp.Data.pair.c[0]=Num_10;
    temp.Data.pair.c[1]=Num_8;
    temp.Data.pair.c[2]=Num_7;
    QVERIFY(CardsCompare(temp,c1)==1);//a > b
    QVERIFY(CardsCompare(c1,temp)==2);//a < b
    // A = B
    temp.card[0].CardDecor=Decor::Diamond;
    temp.card[0].CardNum=Num_4;
    temp.card[1].CardDecor=Decor::Spade;
    temp.card[1].CardNum=Num_4;
    temp.card[2].CardDecor=Decor::Club;
    temp.card[2].CardNum=Num_9;
    temp.card[3].CardDecor=Decor::Spade;
    temp.card[3].CardNum=Num_8;
    temp.card[4].CardDecor=Decor::Heart;
    temp.card[4].CardNum=Num_7;
    temp.status=OnePair;
    temp.Data.pair.pairc=Num_4;
    temp.Data.pair.c[0]=Num_9;
    temp.Data.pair.c[1]=Num_8;
    temp.Data.pair.c[2]=Num_7;
    QVERIFY(CardsCompare(c1,temp)==0);//a > b
}

void TexasPokerTest::case_TwoPairCompare()
{
    // A > B 对子比较大
    Cards temp;
    temp.card[0].CardDecor=Decor::Diamond;
    temp.card[0].CardNum=Num_A;
    temp.card[1].CardDecor=Decor::Spade;
    temp.card[1].CardNum=Num_A;
    temp.card[2].CardDecor=Decor::Club;
    temp.card[2].CardNum=Num_J;
    temp.card[3].CardDecor=Decor::Spade;
    temp.card[3].CardNum=Num_J;
    temp.card[4].CardDecor=Decor::Heart;
    temp.card[4].CardNum=Num_6;
    temp.status=TwoPair;
    temp.Data.pairs.pairc1=Num_A;
    temp.Data.pairs.pairc2=Num_J;
    temp.Data.pairs.c=Num_6;
    QVERIFY(CardsCompare(temp,c2)==1);//A>B
    QVERIFY(CardsCompare(c2,temp)==2);//A<B
}

