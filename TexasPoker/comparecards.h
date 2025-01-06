//////////////////////
/// \author JackeyLea
/// \date 2024-02-16
/// \brief 扑克牌基础定义
//////////////////////

#ifndef COMPARECARDS_H
#define COMPARECARDS_H

#include <QString>
#include <QDebug>

#include "card.h"

class CompareCards
{
public:
    //牌型 5张牌组成一种牌型
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

    ///////////////////
    /// 一对
    /// \brief 一对牌值
    ///
    struct OnePairCards{
        Card::Number pairc;//一对对应的数值
        Card::Number c[3];
    };

    struct TwoPairCards{
        Card::Number pairc1;//第一对对应数值
        Card::Number pairc2;//
        Card::Number c;
    };

    struct ThreeKindCards{
        Card::Number threec;//三条对应的数值
        Card::Number c[2];
    };

    struct FullHouseCards{
        Card::Number threec;//三条
        Card::Number pair;//一对
    };

    struct FourKindCards{
        Card::Number fourc;//四条
        Card::Number c;
    };

    struct StraightCards{
        Card::Number start;
        Card::Number end;
    };

    //结果牌
    struct Cards{
        BrandType status;//是杂牌还是对子、顺子，减少后续判断时间
        Card card[5];//5张牌
        union {
            OnePairCards pair;
            TwoPairCards pairs;
            ThreeKindCards three;
            FullHouseCards full;
            FourKindCards four;
            StraightCards straight;//顺子
        }Data;
    };

    CompareCards();

    ///
    /// \brief getBrandType 获取牌型对应的字符串
    /// \param bt
    /// \return 字符串
    ///
    QString getBrandType(BrandType bt);

    ///
    /// 检测5张牌中有没有重复的牌
    /// \brief isDuplicate
    /// \param cards
    /// \return
    ///
    bool isDuplicate(Cards cards);

    /// 判断5张牌的数字是否一样
    /// \brief is5
    /// \param cards
    /// \return
    ///
    bool is5(Cards cards);

    /// 捋顺5张牌顺序 从大到小
    /// \brief straightCards
    /// \param cards
    ///
    void straightCards(Cards &cards);

    ///
    /// 输出5张牌
    /// \brief printCards
    /// \param cards
    ///
    void printCards(Cards cards){
        for(int i=0;i<5;i++){
            qDebug()<<cards.card[i].num();
        }
    }

    /// 判断5张牌中是否包含A
    /// \brief isHighA
    /// \param cards
    /// \return
    ///
    bool isHighA(Cards cards);

    /// \brief isFlush 判断5张牌是否是同花
    /// \param cards
    /// \return
    ///
    bool isFlush(Cards cards);

    /// \brief isStraight 判断是否是顺子
    /// \param cards
    /// \return
    ///
    bool isStraight(Cards &cards);

    /// 判断是否包含四条
    /// \brief isFourKing
    /// \param cards
    /// \return
    ///
    bool isFourKing(Cards &cards);

    /// 判断是否是三条，如果是4条也是真
    /// \brief isThreeKind
    /// \param cards
    /// \return
    ///
    bool isThreeKind(Cards &cards);

    /// 是否是葫芦/三带二
    /// \brief isFullHouse
    /// \param cards
    /// \return
    ///
    bool isFullHouse(Cards &cards);

    /// 判断是否是两对
    /// \brief isTwoPair
    /// \param cards
    /// \return
    ///
    bool isTwoPair(Cards &cards);

    /// 判断是否是一对
    /// \brief isOnePair
    /// \param cards
    /// \return
    ///
    bool isOnePair(Cards &cards);

    ///
    /// 5张公共牌，2张玩家牌，从这7张牌里面获得最大牌型的组合
    /// \brief check7Cards
    /// \param input
    /// \param output
    ///
    void check7Cards(QList<Card> input,Cards &output);

    /// 检测5张牌可组成的牌型
    /// \brief checkBranchType
    /// \param cards
    /// \return
    ///
    void checkBranchType(Cards &cards);

    /// 比牌层级
    /// \brief The CompareType enum
    ///
    enum CompareType{
        //只对比牌型
        CardsType=0,
        //在比牌型的基础上对比数值
        CardNum,
    };

    /// 比较两个玩家各自5张牌牌型大小
    /// \brief CardsCompare
    /// \param cards1
    /// \param cards2
    /// \param compareType 对比颗粒度
    /// \return 1表示cards1赢 0表示平局 2表示cards2赢 -1表示异常

    int CardsCompare(Cards cards1,Cards cards2,int compareType=CardNum);
};

#endif // COMPARECARDS_H
