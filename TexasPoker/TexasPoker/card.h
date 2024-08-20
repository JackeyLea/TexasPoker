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
    Num_A=14
};

//牌 一张牌由花色和数字组成，比如黑桃A
struct Card{
    Decor CardDecor;//花色
    Number CardNum;//数字

    void clear(){
        CardDecor = Spade;
        CardNum = Num_A;
    }
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

//结果牌
struct Cards{
    BrandType status;//是杂牌还是对子、顺子，减少后续判断时间
    Card card[5];//5张牌
};

/////////////////////
/// \brief getCard 获取一张牌，可能重复
/// \return
///
inline Card getCard(){
    Card c;
    int decor= QRandomGenerator::global()->bounded(0,4);
    int num = QRandomGenerator::global()->bounded(2,15);
    c.CardDecor=(Decor)decor;
    c.CardNum=(Number)num;

    return c;
}

///////////////////////////牌型检测/////////////////////////
/// 一副牌可能是对子也可能是三带二，至于哪个大不在此判断
///

////////////////////////////////////////
/// \brief getBrandType 获取牌型对应的字符串
/// \param bt
/// \return
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


////////////////////////////////
/// \brief isHighA 判断5张牌中是否包含A
/// \param cards
/// \return
///
inline bool isHighA(Cards cards){
    for(int i=0;i<5;i++){
        if(cards.card[i].CardNum==Num_A){
            //检测到A就可以了
            return true;
        }
    }
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
        }
    }
    return true;
}

///////////////////////////////////
/// \brief isStraight 判断是否是顺子
/// \param cards
/// \return
///
inline bool isStraight(Cards cards){
    //有个特例10JQKA，数字是10 11 12 13 1
    if(isHighA(cards)){
        QMap<int,int> num;
        num.insert(1,1);
        num.insert(10,1);
        num.insert(11,1);
        num.insert(12,1);
        num.insert(13,1);

        for(int i=0;i<5;i++){
            if(cards.card[i].CardNum==1){
                num[1]=0;
            }else if(cards.card[i].CardNum==10){
                num[10]=0;
            }else if(cards.card[i].CardNum==11){
                num[11]=0;
            }else if(cards.card[i].CardNum==12){
                num[12]=0;
            }else if(cards.card[i].CardNum==13){
                num[13]=0;
            }
        }

        if(num[1]==0&&num[10]==0&&num[11]==0&&num[12]==0&&num[13]==0){
            //此时是顺子
            return true;
        }else{
            return false;
        }
    }else{
        //其它情况
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
                //有一个不是就退出
                return false;
            }
        }
        return true;
    }

    return false;
}

///////////////////////////////////
/// \brief isFourKing 判断四条
/// \param cards
/// \return
///
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

////////////////////////////////////
/// \brief isThreeKind 判断是否是三条
/// \param cards
/// \return
///
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

////////////////////////////////////
/// \brief isFullHouse 是否是葫芦/三带二
/// \param cards
/// \return
///
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

    //葫芦就是三带二，也就是三条加一对
    //三条附加两个条件，一个是三张一样，另一个是两张不一样，否则就是葫芦
    if(isTwo && isThree){
        return true;
    }else{
        return false;
    }
}

//////////////////////////////////
/// \brief isTwoPair 判断是否是两对
/// \param cards
/// \return
///
inline bool isTwoPair(Cards cards){
    //缓存是否有对
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
    if(cnt==2){//此时有两个对子，不存在3个对子的情况
        return true;
    }else{
        return false;
    }
}

//////////////////////////////////
/// \brief isOnePair 判断是否是一对
/// \param cards
/// \return
///
inline bool isOnePair(Cards cards){
    //缓存是否有对
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

    //如果有3张就不是对子而是葫芦
    QMap<int, int>::const_iterator i = map.constBegin();
    while (i != map.constEnd()) {
        if(i.value()==2){
            cnt++;//此时有两个对子，不存在3个对子的情况
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

//////////////////////////////////////////////
/// \brief checkBranchType 检测牌型
/// \param cards
/// \return
///
inline BrandType checkBranchType(Cards cards){
    /*
     * 采用进阶式判断
     * 判断是否为顺子
     * 顺子的基础上颜色一样就是同花顺
     * 最大是A就是皇家同花顺
     */
    bool flush=isFlush(cards);//同花
    bool a=isHighA(cards);//A
    bool straight=isStraight(cards);//顺子
    bool four=isFourKing(cards);//四套
    bool fullhouse = isFullHouse(cards);//葫芦
    bool three = isThreeKind(cards);//三条
    bool pairs = isTwoPair(cards);//两对
    bool pair = isOnePair(cards);//一对

#ifdef DEBUG
    qDebug()<<QString(u8"同花")<<flush;
    qDebug()<<QString(u8"A")<<a;
    qDebug()<<QString(u8"顺子")<<straight;
    qDebug()<<QString(u8"四条")<<four;
    qDebug()<<QString(u8"葫芦")<<fullhouse;
    qDebug()<<QString(u8"三条")<<three;
    qDebug()<<QString(u8"两对")<<pairs;
    qDebug()<<QString(u8"一对")<<pair;
#endif

    //从顶往下判断
    //是否是皇家同花顺
    //满足 最大A + 顺子 + 同花
    if(flush && a && straight) return BrandType::RoyalFlush;

    //同花顺
    //满足 同花+顺子 + 最大不能是A
    if(flush && straight && !a) return BrandType::StraightFlush;

    //四条
    //满足 四条
    //如果是同花就优先判断为四条
    if(four && !flush) return BrandType::FourOfaKind;

    //葫芦
    // 满足 葫芦 不能是 三条 不能是 对子
    // 如果是同花则优先判断为葫芦
    if(fullhouse && !three && !pair && !flush) return BrandType::FullHouse;

    //同花
    //满足 不能是葫芦 不能是四条 不能是三条 不能是顺子
    if(!fullhouse && !four && flush && !straight) return BrandType::Flush;

    //顺子
    //满足 不能是同花
    if(straight && !flush) return BrandType::Straight;

    //三条
    //满足 不能是同花 不能是四条 不能是葫芦
    //如果是三带二，优先判断为葫芦
    if(!flush && !four && !fullhouse && three) return BrandType::ThreeOfaKind;

    //两对
    //满足 不能是同花 不能是一对
    if(!flush && pairs) return BrandType::TwoPair;

    //一对
    //满足 不能是同花 不能是两对
    if(!flush && !pairs && pair) return BrandType::OnePair;

    //高牌
    //不能是同花 不能是顺子 不能是四条 不能是两对 不能是一对 不能是葫芦 不能是三条 可以最大为A
    if(!flush && !straight && !four && !fullhouse && !three && !pairs && !pair) return BrandType::HighCard;
    //5张牌至少可以组成高牌

    return BrandType::None;
}

#endif // CARD_H
