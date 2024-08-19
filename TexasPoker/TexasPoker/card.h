////////////////////////////////////////
/// \author JackeyLea
/// \date 2024-02-16
/// \brief 扑克牌基础定义
////////////////////////////////////////

#ifndef CARD_H
#define CARD_H

#include <QString>

///牌花色
enum Decor{
    ///黑桃
    Spade=0,
    ///红桃
    Heart,
    ///方块
    Diamond,
    ///梅花
    Club,
};

///牌大小
enum Number{
    Num_2=2,
    Num_3=3,
    Num_4=4,
    Num_5=5,
    Num_6=6,
    Num_7=7,
    Num_8=8,
    Num_9=9,
    Num_10=10,
    Num_J=11,
    Num_Q=12,
    Num_K=13,
    Num_A=14
};

///牌 一张牌由花色和数字组成，比如黑桃A
struct Card{
    Decor CardDecor;//花色
    Number CardNum;//数字
};

///牌型 5张牌组成一种牌型
enum BrandType{
    None=-1,//无状态
    HighCard=0,//高牌 无以下任意情况，取牌中最大数
    OnePair,//一对
    TwoPair,//两对
    ThreeOfaKind,//三条 三张同数
    Straight,//顺子
    Flush,//同花 数字不做要求
    FullHouse,//葫芦 3带2
    FourOfaKind,//四条 四张同数
    StraightFlush,//同花顺 同色顺子
    RoyalFlush,//皇家同花顺 同色的10JQKA
};

inline QString getBrandType(BrandType bt){
    QString r=QString("异常");

    switch (bt) {
    case -1:
        r=QString("异常");
        break;
    case 0:
        r=QString("高牌");
        break;
    case 1:
        r=QString("一对");
        break;
    case 2:
        r=QString("两对");
        break;
    case 3:
        r=QString("三条");
        break;
    case 4:
        r=QString("顺子");
        break;
    case 5:
        r=QString("同花");
        break;
    case 6:
        r=QString("葫芦");
        break;
    case 7:
        r=QString("四条");
        break;
    case 8:
        r=QString("同花顺");
        break;
    case 9:
        r=QString("皇家同花顺");
        break;
    default:
        r=QString("无效");
        break;
    }

    return r;
}

#endif // CARD_H
