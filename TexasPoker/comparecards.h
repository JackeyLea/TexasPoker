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
    bool isDuplicate(Cards cards){
        for(int i=0;i<4;i++){
            for(int j=i+1;j<5;j++){
                if((cards.card[i].decor()==cards.card[j].decor()) &&
                    (cards.card[i].num()==cards.card[j].num())){
                    return true;//两张牌重复
                }//if
            }//j
        }//i

        return false;//没有重复的牌
    }

    /// 判断5张牌的数字是否一样
    /// \brief is5
    /// \param cards
    /// \return
    ///
    bool is5(Cards cards){
        if((cards.card[0].num() == cards.card[1].num()) &&
            (cards.card[0].num() == cards.card[2].num()) &&
            (cards.card[0].num() == cards.card[3].num()) &&
            (cards.card[0].num() == cards.card[4].num())){
            return true;//5张牌数字一样，这个理论上一副牌中是不可能的
        }//if
        return false;//5张牌数字不一样
    }

    /// 捋顺5张牌顺序 从大到小
    /// \brief straightCards
    /// \param cards
    ///
    void straightCards(Cards &cards){
        for(int i=0;i<4;i++){
            for(int j=i+1;j<5;j++){
                if(cards.card[i].num()<cards.card[j].num()){
                    Card::Number t = cards.card[j].num();
                    cards.card[j].setNum(cards.card[i].num());
                    cards.card[i].setNum(t);
                }//if
            }//for j
        }//for i
    }

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
        //在数值的基础上对比花色
        CardDecor,
    };

    /// 比较两个玩家各自5张牌牌型大小
    /// \brief CardsCompare
    /// \param cards1
    /// \param cards2
    /// \param compareType 对比颗粒度
    /// \return 1表示cards1赢 0表示平局 2表示cards2赢 -1表示异常

    int CardsCompare(Cards cards1,Cards cards2,int compareType=CardNum);

    ///////////////////////////牌型检测/////////////////////////
    /// 一副牌可能是对子也可能是三带二，至于哪个大不在此判断
    ///

    /// 判断5张牌中是否包含A
    /// \brief isHighA
    /// \param cards
    /// \return
    ///
    bool isHighA(Cards cards){
        for(int i=0;i<5;i++){
            if(cards.card[i].num()==Card::Num_A){
                //检测到A就可以了
                return true;
            }//if
        }//for
        return false;
    }

    /// \brief isFlush 判断5张牌是否是同花
    /// \param cards
    /// \return
    ///
    bool isFlush(Cards cards){
        for(int i=1;i<5;i++){
            if(cards.card[i].decor()!=cards.card[i-1].decor()){
                //有一个不同色就不是同花
                return false;
            }//if
        }//for
        return true;
    }

    /// \brief isStraight 判断是否是顺子
    /// \param cards
    /// \return
    ///
    bool isStraight(Cards &cards){
        //排序
        straightCards(cards);

        for(int i=1;i<5;i++){
            if((cards.card[i-1].num()-cards.card[i].num()) != 1){
                //有一个不是就退出
                return false;
            }//if
        }//for
        return true;
    }

    /// 判断是否包含四条
    /// \brief isFourKing
    /// \param cards
    /// \return
    ///
    bool isFourKing(Cards &cards){
        for(int w=0;w<2;w++){
            for(int x=w+1;x<3;x++){
                for(int y=x+1;y<4;y++){
                    for(int z=y+1;z<5;z++){
                        if(((cards.card[w].num() == cards.card[x].num()) &&
                            (cards.card[w].num() == cards.card[y].num())) &&
                            (cards.card[w].num() == cards.card[z].num())){
                            return true;//有一个就行
                        }
                    }//z
                }//y
            }//x
        }//w
        return false;
    }

    /// 判断是否是三条，如果是4条也是真
    /// \brief isThreeKind
    /// \param cards
    /// \return
    ///
    bool isThreeKind(Cards &cards){
        for(int w=0;w<3;w++){
            for(int x=w+1;x<4;x++){
                for(int y=x+1;y<5;y++){
                        if((cards.card[w].num() == cards.card[x].num()) &&
                             (cards.card[w].num() == cards.card[y].num())){
                            return true;//有一个就行
                        }
                }//y
            }//x
        }//w
        return false;
    }

    /// 是否是葫芦/三带二
    /// \brief isFullHouse
    /// \param cards
    /// \return
    ///
    bool isFullHouse(Cards &cards){
        //先检测三条
        Card::Number three = Card::NumNone;//三条对应的数
        for(int w=0;w<3;w++){
            for(int x=w+1;x<4;x++){
                for(int y=x+1;y<5;y++){
                    if((cards.card[w].num() == cards.card[x].num()) &&
                        (cards.card[w].num() == cards.card[y].num())){
                        three=cards.card[w].num();//有一个就行
                        break;
                    }
                }//y
            }//x
        }//w

        if(three == Card::NumNone) return false;

        //再检测与三条数值不同的一对
        for(int i=0;i<4;i++){
            for(int j=i+1;j<5;j++){
                if((cards.card[i].num() ==  cards.card[j].num()) &&
                    (cards.card[i].num() != three)){
                    return true;//有一个就行
                }
            }//j
        }//i

        return false;
    }

    /// 判断是否是两对
    /// \brief isTwoPair
    /// \param cards
    /// \return
    ///
    bool isTwoPair(Cards &cards){
        //先判断第一对
        Card::Number pair1 = Card::NumNone;
        for(int i=0;i<4;i++){
            for(int j=i+1;j<5;j++){
                if(cards.card[i].num() ==  cards.card[j].num()){
                    pair1=cards.card[i].num();//有一个就行
                    break;
                }
            }//j
        }//i

        if(pair1 == Card::NumNone) return false;

        //在判断第二对
        for(int i=0;i<4;i++){
            for(int j=i+1;j<5;j++){
                if((cards.card[i].num() ==  cards.card[j].num()) &&
                    (cards.card[i].num() != pair1)){
                    return true;//有一个就行
                }
            }//j
        }//i

        //不可能有第3对
        return false;
    }

    /// 判断是否是一对
    /// \brief isOnePair
    /// \param cards
    /// \return
    ///
    bool isOnePair(Cards &cards){
        for(int i=0;i<4;i++){
            for(int j=i+1;j<5;j++){
                if(cards.card[i].num() ==  cards.card[j].num()){
                    return true;//有一个就行
                }
            }//j
        }//i

        return false;
    }

    ///
    /// 5张公共牌，2张玩家牌，从这7张牌里面获得最大牌型的组合
    /// \brief check7Cards
    /// \param input
    /// \param output
    ///
    void check7Cards(QList<Card> input,Cards &output);
};

#endif // COMPARECARDS_H
