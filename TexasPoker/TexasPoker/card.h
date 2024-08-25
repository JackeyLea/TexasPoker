////////////////////////////////////////
/// \author JackeyLea
/// \date 2024-02-16
/// \brief 扑克牌基础定义
////////////////////////////////////////

#ifndef CARD_H
#define CARD_H

#include <QString>
#include <QRandomGenerator>
#include <QMap>
#include <QDebug>

/*
 * 德州扑克不使用鬼牌
 * A最大
 * 相同牌型不分花色
 */

/////////////////////////////以下是扑克牌的定义////////////////////

//牌花色
enum Decor{
    //黑桃
    Spade=0,
    //红桃
    Heart,
    //方块
    Diamond,
    //梅花
    Club,
};

//牌大小
enum Number{
    Num_None=0,
    Num_2=2,
    Num_3,
    Num_4,
    Num_5,
    Num_6,
    Num_7,
    Num_8,
    Num_9,
    Num_10,
    Num_J,
    Num_Q,
    Num_K,
    Num_A
};

//牌 一张牌由花色和数字组成，比如黑桃A
struct Card{
    Decor CardDecor;//花色
    Number CardNum;//数字

    //牌默认值
    void clear(){
        CardDecor = Spade;
        CardNum = Num_A;
    }//clear
};

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
    Number pairc;//一对对应的数值
    Number c[3];
};

struct TwoPairCards{
    Number pairc1;//第一对对应数值
    Number pairc2;//
    Number c;
};

struct ThreeKindCards{
    Number threec;//三条对应的数值
    Number c[2];
};

struct FullHouseCards{
    Number threec;//三条
    Number pair;//一对
};

struct FourKindCards{
    Number fourc;//四条
    Number c;
};

struct StraightCards{
    Number start;
    Number end;
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

/////////////////////
/// 获取一张牌，可能重复
/// \brief getCard
/// \return 一张牌
///
inline Card getCard(){
    Card c;
    int decor= QRandomGenerator::global()->bounded(0,4);
    int num = QRandomGenerator::global()->bounded(2,15);
    c.CardDecor=(Decor)decor;
    c.CardNum=(Number)num;
    //qDebug()<<c.CardDecor<<c.CardNum;

    return c;
}

///////////////////////////牌型检测/////////////////////////
/// 一副牌可能是对子也可能是三带二，至于哪个大不在此判断
///

////////////////////////////////////////
/// \brief getBrandType 获取牌型对应的字符串
/// \param bt
/// \return 字符串
///
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

//////////////////////////////////////
/// 捋顺5张牌顺序 从大到小
/// \brief straightCards
/// \param cards
///
inline void straightCards(Cards &cards){
    for(int i=0;i<4;i++){
        for(int j=i+1;j<5;j++){
            if(cards.card[i].CardNum<cards.card[j].CardNum){
                Number t = cards.card[j].CardNum;
                cards.card[j].CardNum = cards.card[i].CardNum;
                cards.card[i].CardNum = t;
            }//if
        }//for j
    }//for i
}

///
/// 输出5张牌
/// \brief printCards
/// \param cards
///
inline void printCards(Cards cards){
    for(int i=0;i<5;i++){
        qDebug()<<cards.card[i].CardNum;
    }
}

////////////////////////////////////
/// 检测5张牌中有没有重复的牌
/// \brief isDuplicate
/// \param cards
/// \return
///
inline bool isDuplicate(Cards cards){
    for(int i=0;i<4;i++){
        for(int j=i+1;j<5;j++){
            if((cards.card[i].CardDecor==cards.card[j].CardDecor) &&
                (cards.card[i].CardNum==cards.card[j].CardNum)){
                return true;//两张牌重复
            }//if
        }//j
    }//i

    return false;//没有重复的牌
}

////////////////////////////
/// 判断5张牌的数字是否一样
/// \brief is5
/// \param cards
/// \return
///
inline bool is5(Cards cards){
    if((cards.card[0].CardNum == cards.card[1].CardNum) &&
        (cards.card[0].CardNum == cards.card[2].CardNum) &&
        (cards.card[0].CardNum == cards.card[3].CardNum) &&
        (cards.card[0].CardNum == cards.card[4].CardNum)){
        return true;//5张牌数字一样，这个理论上一副牌中是不可能的
    }//if
    return false;//5张牌数字不一样
}

////////////////////////////////
/// 判断5张牌中是否包含A
/// \brief isHighA
/// \param cards
/// \return
///
inline bool isHighA(Cards cards){
    for(int i=0;i<5;i++){
        if(cards.card[i].CardNum==Num_A){
            //检测到A就可以了
            return true;
        }//if
    }//for
    return false;
}

////////////////////////////////
/// \brief isFlush 判断5张牌是否是同花
/// \param cards
/// \return
///
inline bool isFlush(Cards cards){
    for(int i=1;i<5;i++){
        if(cards.card[i].CardDecor!=cards.card[i-1].CardDecor){
            //有一个不同色就不是同花
            return false;
        }//if
    }//for
    return true;
}

///////////////////////////////////
/// \brief isStraight 判断是否是顺子
/// \param cards
/// \return
///
inline bool isStraight(Cards &cards){
    //排序
    straightCards(cards);

    for(int i=1;i<5;i++){
        if((cards.card[i-1].CardNum-cards.card[i].CardNum) != 1){
            //有一个不是就退出
            return false;
        }//if
    }//for
    return true;
}

///////////////////////////////////
/// 判断是否包含四条
/// \brief isFourKing
/// \param cards
/// \return
///
inline bool isFourKing(Cards &cards){
    for(int w=0;w<2;w++){
        for(int x=w+1;x<3;x++){
            for(int y=x+1;y<4;y++){
                for(int z=y+1;z<5;z++){
                    if(((cards.card[w].CardNum == cards.card[x].CardNum) &&
                        (cards.card[w].CardNum == cards.card[y].CardNum)) &&
                        (cards.card[w].CardNum == cards.card[z].CardNum)){
                        return true;//有一个就行
                    }
                }//z
            }//y
        }//x
    }//w
    return false;
}

////////////////////////////////////
/// 判断是否是三条
/// \brief isThreeKind
/// \param cards
/// \return
///
inline bool isThreeKind(Cards &cards){
    for(int w=0;w<3;w++){
        for(int x=w+1;x<4;x++){
            for(int y=x+1;y<5;y++){
                    if((cards.card[w].CardNum == cards.card[x].CardNum) &&
                         (cards.card[w].CardNum == cards.card[y].CardNum)){
                        return true;//有一个就行
                    }
            }//y
        }//x
    }//w
    return false;
}

////////////////////////////////////
/// 是否是葫芦/三带二
/// \brief isFullHouse
/// \param cards
/// \return
///
inline bool isFullHouse(Cards &cards){
    //先检测三条
    Number three = Num_None;//三条对应的数
    for(int w=0;w<3;w++){
        for(int x=w+1;x<4;x++){
            for(int y=x+1;y<5;y++){
                if((cards.card[w].CardNum == cards.card[x].CardNum) &&
                    (cards.card[w].CardNum == cards.card[y].CardNum)){
                    three=cards.card[w].CardNum;//有一个就行
                    break;
                }
            }//y
        }//x
    }//w

    if(three == Num_None) return false;

    //再检测与三条数值不同的一对
    for(int i=0;i<4;i++){
        for(int j=i+1;j<5;j++){
            if((cards.card[i].CardNum ==  cards.card[j].CardNum) &&
                (cards.card[i].CardNum != three)){
                return true;//有一个就行
            }
        }//j
    }//i

    return false;
}

//////////////////////////////////
/// 判断是否是两对
/// \brief isTwoPair
/// \param cards
/// \return
///
inline bool isTwoPair(Cards &cards){
    //先判断第一对
    Number pair1 = Num_None;
    for(int i=0;i<4;i++){
        for(int j=i+1;j<5;j++){
            if(cards.card[i].CardNum ==  cards.card[j].CardNum){
                pair1=cards.card[i].CardNum;//有一个就行
                break;
            }
        }//j
    }//i

    if(pair1 == Num_None) return false;

    //在判断第二对
    for(int i=0;i<4;i++){
        for(int j=i+1;j<5;j++){
            if((cards.card[i].CardNum ==  cards.card[j].CardNum) &&
                (cards.card[i].CardNum != pair1)){
                return true;//有一个就行
            }
        }//j
    }//i

    //不可能有第3对
    return false;
}

//////////////////////////////////
/// 判断是否是一对
/// \brief isOnePair
/// \param cards
/// \return
///
inline bool isOnePair(Cards &cards){
    for(int i=0;i<4;i++){
        for(int j=i+1;j<5;j++){
            if(cards.card[i].CardNum ==  cards.card[j].CardNum){
                return true;//有一个就行
            }
        }//j
    }//i

    return false;
}

//////////////////////////////////////////////
/// 检测5张牌颗组成的牌型
/// \brief checkBranchType
/// \param cards
/// \return
///
inline void checkBranchType(Cards &cards){
    ////////////////////判断牌是否有效////////////////////////
    //重复
    if(isDuplicate(cards)){
        cards.status = BrandType::None;
        return;//如果有重复数值重复牌型的牌就退出
    }
    //是否有5张一样的牌
    if(is5(cards)){
        cards.status = BrandType::None;
        return;//如果有重复数值重复牌型的牌就退出
    }
    //统一排序
    straightCards(cards);
    /*
     * 采用进阶式判断
     * 判断是否为顺子
     * 顺子的基础上颜色一样就是同花顺
     * 最大是A就是皇家同花顺
     */
    bool flush=isFlush(cards);//同花
    bool a=isHighA(cards);//A
    bool straight=isStraight(cards);//顺子
    bool four=isFourKing(cards);//四条
    bool fullhouse = isFullHouse(cards);//葫芦
    bool three = isThreeKind(cards);//三条
    bool pairs = isTwoPair(cards);//两对
    bool pair = isOnePair(cards);//一对

    ////////////////////////从顶往下判断//////////////////////////
    //是否是皇家同花顺
    //满足 最大A + 顺子 + 同花
    if(flush && a && straight) {
        cards.status = BrandType::RoyalFlush;
        return;
    }

    //同花顺
    //满足 同花 + 顺子 + 最大不能是A
    if(flush && straight && !a){
        cards.status = BrandType::StraightFlush;
        return;
    }

    //四条
    //满足 四条
    //如果是同花就优先判断为四条
    if(four && !flush){
        cards.status = BrandType::FourOfaKind;
        return;
    }

    //葫芦
    // 满足 葫芦 不能是 三条 不能是 对子
    // 如果是同花则优先判断为葫芦
    if(fullhouse && !flush && three && pair){
        cards.status = BrandType::FullHouse;
        return;
    }

    //同花
    //满足 不能是葫芦 不能是四条 不能是三条 不能是顺子
    if(!fullhouse && !four && flush && !straight){
        cards.status = BrandType::Flush;
        return;
    }

    //顺子
    //满足 不能是同花
    if(straight && !flush){
        cards.status = BrandType::Straight;
        cards.Data.straight.start = cards.card[0].CardNum;
        cards.Data.straight.end = cards.card[4].CardNum;
        return;
    }

    //三条
    //满足 不能是同花 不能是四条 不能是葫芦
    //如果是三带二，优先判断为葫芦
    if(!flush && !four && !fullhouse && three){
        cards.status = BrandType::ThreeOfaKind;
        cards.Data.three.threec = cards.card[0].CardNum;
        cards.Data.three.c[0] = cards.card[3].CardNum;
        cards.Data.three.c[1] = cards.card[4].CardNum;
        return;
    }

    //两对
    //满足 不能是同花 不能是一对 不能是三条 不能是四条
    if(!flush && pairs && !three && !four){
        cards.status = BrandType::TwoPair;
        //第一对
        cards.Data.pairs.pairc1 = cards.card[0].CardNum;
        //第二对
        cards.Data.pairs.pairc2 = cards.card[2].CardNum;
        //剩余的数值
        cards.Data.pairs.c = cards.card[4].CardNum;
        // qDebug()<<cards.Data.pairs.pairc1
        //          <<cards.Data.pairs.pairc2
        //          <<cards.Data.pairs.c1;
        return;
    }

    //一对
    //满足 不能是同花 不能是两对 不能是葫芦 不能是四条 不能是三条
    if(!flush && !pairs && pair && !fullhouse && !four && !three){
        cards.status = BrandType::OnePair;
        // TODO 改进算法 先判断对子
        for(int i=1;i<5;i++){
            if(cards.card[i].CardNum == cards.card[i-1].CardNum){
                cards.Data.pair.pairc=cards.card[i].CardNum;
            }
        }
        //在判断单牌
        int index=0;
        for(int i=4;i>=0;i--){
            if(cards.Data.pair.pairc != cards.card[i].CardNum){
                cards.Data.pair.c[index++]=cards.card[i].CardNum;
            }
        }
        return;
    }

    //高牌
    //不能是同花 不能是顺子 不能是四条 不能是两对 不能是一对 不能是葫芦 不能是三条 可以最大为A
    if(!flush && !straight && !four && !fullhouse && !three && !pairs && !pair){
        cards.status = BrandType::HighCard;
        return;
    }

    //5张牌至少可以组成高牌
    cards.status = BrandType::None;
}

////////////////////////////////////////////////////
/// 比较两个玩家各自5张牌牌型大小
/// \brief CardsCompare
/// \param cards1
/// \param cards2
/// \return 1 表示cards1赢 0表示平局 2表示cards2赢 -1表示异常
///
inline int CardsCompare(Cards cards1,Cards cards2){
    //首先两个玩家的牌要有效
    if(cards1.status != None && cards2.status != None){
        //此时两个玩家牌都有效
        //先对比牌型
        //qDebug()<<cards1.status<<cards2.status;
        if(cards1.status > cards2.status){
            return 1;//玩家1赢
        }else if(cards1.status == cards2.status){
            //同牌型要对比类型
            switch(cards1.status){
            case RoyalFlush:
            {
                //皇家同花顺，如果两个用户都是皇家同花顺就是平局
                return 0;
                break;
            }
            case StraightFlush:
            {
                //同花顺
                break;
            }
            case FourOfaKind:
            {
                //四条
                break;
            }
            case FullHouse:
            {
                //葫芦
                break;
            }
            case Flush:
            {
                // qDebug()<<cards1.card[0].CardNum
                //          <<cards1.card[1].CardNum
                //          <<cards1.card[2].CardNum
                //          <<cards1.card[3].CardNum
                //          <<cards1.card[4].CardNum;
                // qDebug()<<cards2.card[0].CardNum
                //          <<cards2.card[1].CardNum
                //          <<cards2.card[2].CardNum
                //          <<cards2.card[3].CardNum
                //          <<cards2.card[4].CardNum;
                if(cards1.card[0].CardNum > cards2.card[0].CardNum){
                    return 1;
                }else if(cards1.card[0].CardNum == cards2.card[0].CardNum){
                    //最大的相同，比较小的
                    if(cards1.card[1].CardNum > cards2.card[1].CardNum){
                        return 1;
                    }else if(cards1.card[1].CardNum == cards2.card[1].CardNum){
                        //较大的相同，比较小的
                        if(cards1.card[2].CardNum > cards2.card[2].CardNum){
                            return 1;
                        }else if(cards1.card[2].CardNum == cards2.card[2].CardNum){
                            //最大的相同，比较小的
                            if(cards1.card[3].CardNum > cards2.card[3].CardNum){
                                return 1;
                            }else if(cards1.card[3].CardNum == cards2.card[3].CardNum){
                                //最大的相同，比较小的
                                if(cards1.card[4].CardNum > cards2.card[4].CardNum){
                                    return 1;
                                }else if(cards1.card[4].CardNum == cards2.card[4].CardNum){
                                    //5张牌都相同，平局
                                    return 0;//
                                }else{
                                    return 2;//==0
                                }
                            }else{
                                return 2;//==1
                            }
                        }else{
                            return 2;//==2
                        }
                    }else{
                        return 2;//==3
                    }
                }else{
                    return 2;//==4
                }
                break;
            }//flush
            case Straight:
            {
                //顺子
                // qDebug()<<cards1.Data.straight.start
                //          <<cards1.Data.straight.end;
                // qDebug()<<cards2.Data.straight.start
                //          <<cards2.Data.straight.end;
                //起始点
                if(cards1.Data.straight.start > cards2.Data.straight.start){
                    return 1;
                }else if(cards1.Data.straight.start == cards2.Data.straight.start){
                    //结束点
                    if(cards1.Data.straight.end > cards2.Data.straight.end){
                        return 1;
                    }else if(cards1.Data.straight.end == cards2.Data.straight.end){
                        return 0;//一样
                    }else{
                        return 2;
                    }
                }else{
                    return 2;
                }
                break;
            }
            case ThreeOfaKind:
            {
                //三条
                // qDebug()<<cards1.Data.three.threec
                //          <<cards1.Data.three.c[0]
                //          <<cards1.Data.three.c[1];
                // qDebug()<<cards2.Data.three.threec
                //          <<cards2.Data.three.c[0]
                //          <<cards2.Data.three.c[1];
                //三条
                if(cards1.Data.three.threec > cards2.Data.three.threec){
                    return 1;
                }else if(cards1.Data.three.threec == cards2.Data.three.threec){
                    ///三条数一样大，比较两个单牌
                    //单牌1
                    if(cards1.Data.three.c[0] > cards2.Data.three.c[0]){
                        return 1;
                    }else if(cards1.Data.three.c[0] == cards2.Data.three.c[0]){
                        //单牌2
                        if(cards1.Data.three.c[1] > cards2.Data.three.c[1]){
                            return 1;
                        }else if(cards1.Data.three.c[1] == cards2.Data.three.c[1]){
                            return 0;//相同
                        }else{
                            return 2;//单牌2
                        }
                    }else{
                        return 2;//单牌1
                    }
                }else{
                    return 2;//玩家2
                }
                break;
            }
            case TwoPair://两对
            {
                // qDebug()<<cards1.Data.pairs.pairc1
                //          <<cards1.Data.pairs.pairc2
                //          <<cards1.Data.pairs.c;
                // qDebug()<<cards2.Data.pairs.pairc1
                //          <<cards2.Data.pairs.pairc2
                //          <<cards2.Data.pairs.c;
                //大的那个
                if(cards1.Data.pairs.pairc2 > cards2.Data.pairs.pairc2){
                    return 1;
                }else if(cards1.Data.pairs.pairc2 == cards2.Data.pairs.pairc2){
                    //第一对一样大
                    if(cards1.Data.pairs.pairc1 > cards2.Data.pairs.pairc1){
                        return 1;
                    }else if(cards1.Data.pairs.pairc1 == cards2.Data.pairs.pairc1){
                        //第二对一样大
                        if(cards1.Data.pairs.c > cards2.Data.pairs.c){
                            return 1;
                        }else if(cards1.Data.pairs.c == cards2.Data.pairs.c){
                            //一样大
                            return 0;//一样
                        }else{
                            return 2;//单牌
                        }
                    }else{
                        return 2;//对子
                    }
                }else{
                    return 2;//玩家2对子大
                }
                break;// two pair
            }
            case OnePair://一对
            {
                // qDebug()<<cards1.card[0].CardNum
                //          <<cards1.card[1].CardNum
                //          <<cards1.card[2].CardNum
                //          <<cards1.card[3].CardNum
                //          <<cards1.card[4].CardNum;
                // qDebug()<<cards2.card[0].CardNum
                //          <<cards2.card[1].CardNum
                //          <<cards2.card[2].CardNum
                //          <<cards2.card[3].CardNum
                //          <<cards2.card[4].CardNum;
                // qDebug()<<cards1.Data.pair.pairc
                //          <<cards1.Data.pair.c[0]
                //          <<cards1.Data.pair.c[1]
                //          <<cards1.Data.pair.c[2];
                // qDebug()<<cards2.Data.pair.pairc
                //          <<cards2.Data.pair.c[0]
                //          <<cards2.Data.pair.c[1]
                //          <<cards2.Data.pair.c[2];
                if(cards1.Data.pair.pairc > cards2.Data.pair.pairc){
                    return 1;
                }else if(cards1.Data.pair.pairc == cards2.Data.pair.pairc){
                    //对子是一样的
                    if(cards1.Data.pair.c[0] > cards2.Data.pair.c[0]){
                        return 1;
                    }else if(cards1.Data.pair.c[0] == cards2.Data.pair.c[0]){
                        //第二个数
                        if(cards1.Data.pair.c[1] > cards2.Data.pair.c[1]){
                            return 1;
                        }else if(cards1.Data.pair.c[1] == cards2.Data.pair.c[1]){
                            //第三个数
                            if(cards1.Data.pair.c[2] > cards2.Data.pair.c[2]){
                                return 1;// 玩家1大
                            }else if(cards1.Data.pair.c[2] == cards2.Data.pair.c[2]){
                                return 0;//4张牌相同 平局
                            }else{
                                return 2;//玩家2单牌2大
                            }
                        }else{
                            return 2;//玩家2单牌1大
                        }
                    }else{
                        return 2;//玩家2对子大
                    }
                }else{
                    return 2;//牌2型大
                }
                break;//one pair
            }
            case HighCard://高牌
            {
                // qDebug()<<cards1.card[0].CardNum
                //          <<cards1.card[1].CardNum
                //          <<cards1.card[2].CardNum
                //          <<cards1.card[3].CardNum
                //          <<cards1.card[4].CardNum;
                // qDebug()<<cards2.card[0].CardNum
                //          <<cards2.card[1].CardNum
                //          <<cards2.card[2].CardNum
                //          <<cards2.card[3].CardNum
                //          <<cards2.card[4].CardNum;
                if(cards1.card[0].CardNum > cards2.card[0].CardNum){
                    return 1;
                }else if(cards1.card[0].CardNum == cards2.card[0].CardNum){
                    //最大的相同，比较小的
                    if(cards1.card[1].CardNum > cards2.card[1].CardNum){
                        return 1;
                    }else if(cards1.card[1].CardNum == cards2.card[1].CardNum){
                        //较大的相同，比较小的
                        if(cards1.card[2].CardNum > cards2.card[2].CardNum){
                            return 1;
                        }else if(cards1.card[2].CardNum == cards2.card[2].CardNum){
                            //最大的相同，比较小的
                            if(cards1.card[3].CardNum > cards2.card[3].CardNum){
                                return 1;
                            }else if(cards1.card[3].CardNum == cards2.card[3].CardNum){
                                //最大的相同，比较小的
                                if(cards1.card[4].CardNum > cards2.card[4].CardNum){
                                    return 1;
                                }else if(cards1.card[4].CardNum == cards2.card[4].CardNum){
                                    //5张牌都相同，平局
                                    return 0;//
                                }else{
                                    return 2;//==0
                                }
                            }else{
                                return 2;//==1
                            }
                        }else{
                            return 2;//==2
                        }
                    }else{
                        return 2;//==3
                    }
                }else{
                    return 2;//==4
                }
                break;
            }//high card
            default:
            {
                return -1;
                break;
            }//default
            }//switch
        }else{
            return 2;//玩家2赢
        }
    }else{
        return -1;// None & None
    }

    return -1;//异常
}

#endif // CARD_H
