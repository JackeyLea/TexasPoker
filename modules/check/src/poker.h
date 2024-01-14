#ifndef POKER_H
#define POKER_H

#include <QDebug>
//无鬼牌
//最大A

//牌花色
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

//牌大小
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
    Num_A=1,
};

//牌 一张牌由花色和数字组成
struct Card{
    Decor CardDecor;//花色
    Number CardNum;//数字
};

//牌型
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

// 结果牌，一般5张
struct Cards{
    BrandType status;//是杂牌还是对子、顺子，减少后续判断时间
    Card card[5];//5张牌

    Cards(){
        status = None;
        memset(card,0,sizeof(card));
    }
    Cards(Card _card[5]){
        memcpy(card,_card,sizeof(card));
    }
};
//一对
inline bool isOnePair(Cards cards){
    QMap<int,int> map;
    for(int i=0;i<5;i++){
        if(!map.contains(cards.card[i].CardNum)){
            map.insert(cards.card[i].CardNum,1);
        }else{
            map[cards.card[i].CardNum]++;
        }
    }

    int cnt=0;
    bool isThree=false;

    QMap<int, int>::const_iterator i = map.constBegin();
    while (i != map.constEnd()) {
        if(i.value()==2){
            cnt++;
        }else if(i.value()==3){
            isThree=true;
        }
        ++i;
    }
    if((cnt==1) && !isThree){
        return true;
    }else{
        return false;
    }
}

//两对
inline bool isTwoPair(Cards cards){
    QMap<int,int> map;
    for(int i=0;i<5;i++){
        if(!map.contains(cards.card[i].CardNum)){
            map.insert(cards.card[i].CardNum,1);
        }else{
            map[cards.card[i].CardNum]++;
        }
    }

    int cnt=0;

    QMap<int, int>::const_iterator i = map.constBegin();
    while (i != map.constEnd()) {
        if(i.value()==2){
            cnt++;
        }
        ++i;
    }
    if(cnt==2){
        return true;
    }else{
        return false;
    }
}

//四条
inline bool isFourKing(Cards cards){
    QMap<int,int> map;
    for(int i=0;i<5;i++){
        if(!map.contains(cards.card[i].CardNum)){
            map.insert(cards.card[i].CardNum,1);
        }else{
            map[cards.card[i].CardNum]++;
        }
    }

    QMap<int, int>::const_iterator i = map.constBegin();
    while (i != map.constEnd()) {
        if(i.value()==4){
            return true;//不可能出现5张一样的
        }
        ++i;
    }
    return false;
}

//三条
inline bool isThreeKind(Cards cards){
    QMap<int,int> map;
    for(int i=0;i<5;i++){
        if(!map.contains(cards.card[i].CardNum)){
            map.insert(cards.card[i].CardNum,1);
        }else{
            map[cards.card[i].CardNum]++;
        }
    }
    bool isTwo=false,isThree=false;

    QMap<int, int>::const_iterator i = map.constBegin();
    while (i != map.constEnd()) {
        if(i.value()==3){
            isThree = true;
        }else if(i.value()==2){
            isTwo=true;
        }
        ++i;
    }

    //三条有两个条件，一个是三张一样，另一个是两张不一样，否则就是葫芦
    if(!(isTwo) && isThree){
        return true;
    }else{
        return false;
    }
}

//三带二
inline bool isFullHouse(Cards cards){
    QMap<int,int> map;
    for(int i=0;i<5;i++){
        if(!map.contains(cards.card[i].CardNum)){
            map.insert(cards.card[i].CardNum,1);
        }else{
            map[cards.card[i].CardNum]++;
        }
    }
    bool isTwo=false,isThree=false;

    QMap<int, int>::const_iterator i = map.constBegin();
    while (i != map.constEnd()) {
        if(i.value()==3){
            isThree = true;
        }else if(i.value()==2){
            isTwo=true;
        }
        ++i;
    }

    //三条有两个条件，一个是三张一样，另一个是两张不一样，否则就是葫芦
    if(isTwo && isThree){
        return true;
    }else{
        return false;
    }
}

//判断牌是否是同花 5张牌颜色一样
inline bool isFlush(Cards cards){
    for(int i=1;i<5;i++){
        if(cards.card[i].CardDecor!=cards.card[i-1].CardDecor){
            return false;
        }
    }
    return true;
}

//判断最大是否是A
inline bool isA(Cards cards){
    for(int i=0;i<5;i++){
        if(cards.card[i].CardNum==Num_A){
            return true;
        }
    }
    return false;
}

//顺子
inline bool isStraight(Cards cards){
    int num[5];
    for(int i=0;i<5;i++){
        num[i]=cards.card[i].CardNum;
    }
    //排序
    for(int i=0;i<4;i++){
        for(int j=i+1;j<5;j++){
            if(num[j]<num[i]){
                int temp = num[j];
                num[j]=num[i];
                num[i]=temp;
            }
        }
    }

    for(int i=1;i<5;i++){
        if(num[i]-num[i-1]!=1){
            return false;
        }
    }
    return true;
}

//检查牌型
inline BrandType checkBranchType(Cards cards){
    //采用进阶式判断 已经是顺子，颜色一样就是同花顺，最大是A就是皇家同花顺
    bool flush=isFlush(cards);//同花
    bool a=isA(cards);//A
    bool straight=isStraight(cards);//顺子
    bool four=isFourKing(cards);//四套
    bool fullhouse = isFullHouse(cards);//葫芦
    bool three = isThreeKind(cards);//三条
    bool pairs = isTwoPair(cards);//两对
    bool pair = isOnePair(cards);//一对

    //从顶往下判断
    //是否是皇家同花顺
    if(flush && a && straight) return BrandType::RoyalFlush;

    //同花顺
    if(flush && straight && !a) return StraightFlush;

    //四条
    if(four && !flush) return FourOfaKind;

    //葫芦
    if(fullhouse && !flush) return FullHouse;

    //同花
    if(!fullhouse && !four && flush && !straight) return Flush;

    //顺子
    if(straight && !flush) return Straight;

    //三条
    if(!flush && !straight && !four && !fullhouse && three) return ThreeOfaKind;

    //两对
    if(!flush && !straight && pairs) return TwoPair;

    //一对
    if(!flush && !straight && pairs && pair) return OnePair;

    //高牌
    if(!flush && !straight && !four && !fullhouse && !three && !pairs && !pair) return HighCard;

    return None;
}

//只比牌判断输赢，不处理牌
//true为2赢
inline bool isWin(Cards cards1,Cards cards2){
    //如果两者有状态就比较
    if(cards1.status!=None && cards2.status!=None){
        //先比牌型
        if(cards1.status < cards2.status){
            return true;
        }else if(cards1.status == cards2.status){
            //两个牌型相同

        }else if(cards1.status > cards2.status){
            return false;
        }
    }else{
        qDebug()<<"Please check branch type first.";
    }

    return false;
}

class Poker
{
public:
    Poker();
};

#endif // POKER_H
