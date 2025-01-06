#include "comparecards.h"

CompareCards::CompareCards()
{
    // NOTHING
}

QString CompareCards::getBrandType(BrandType bt)
{
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

bool CompareCards::isDuplicate(Cards cards)
{
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

bool CompareCards::is5(Cards cards)
{
    if((cards.card[0].num() == cards.card[1].num()) &&
        (cards.card[0].num() == cards.card[2].num()) &&
        (cards.card[0].num() == cards.card[3].num()) &&
        (cards.card[0].num() == cards.card[4].num())){
        return true;//5张牌数字一样，这个理论上一副牌中是不可能的
    }//if
    return false;//5张牌数字不一样
}

void CompareCards::straightCards(Cards &cards)
{
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

bool CompareCards::isHighA(Cards cards)
{
    for(int i=0;i<5;i++){
        if(cards.card[i].num()==Card::Num_A){
            //检测到A就可以了
            return true;
        }//if
    }//for
    return false;
}

bool CompareCards::isFlush(Cards cards)
{
    for(int i=1;i<5;i++){
        if(cards.card[i].decor()!=cards.card[i-1].decor()){
            //有一个不同色就不是同花
            return false;
        }//if
    }//for
    return true;
}

bool CompareCards::isStraight(Cards &cards)
{
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

bool CompareCards::isFourKing(Cards &cards)
{
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

bool CompareCards::isThreeKind(Cards &cards)
{
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

bool CompareCards::isFullHouse(Cards &cards)
{
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

bool CompareCards::isTwoPair(Cards &cards)
{
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

bool CompareCards::isOnePair(Cards &cards)
{
    for(int i=0;i<4;i++){
        for(int j=i+1;j<5;j++){
            if(cards.card[i].num() ==  cards.card[j].num()){
                return true;//有一个就行
            }
        }//j
    }//i

    return false;
}

void CompareCards::check7Cards(QList<Card> input, Cards &output)
{
    assert(input.size()==7);

    //当前所有可能组合中最大的那个
    BrandType bt=BrandType::None;//默认情况下是无效

    //c 5 7
    for(int a=0;a<3;a++){
        for(int b=a+1;b<4;b++){
            for(int i=b+1;i<5;i++){
                for(int j=i+1;j<6;j++){
                    for(int z=j+1;z<7;z++){
                        //给5张牌赋值
                        Cards cs;
                        cs.card[0]=input[a];
                        cs.card[1]=input[b];
                        cs.card[2]=input[i];
                        cs.card[3]=input[j];
                        cs.card[4]=input[z];
                        checkBranchType(cs);
                        //可能会出现多个相同牌型，取最大的那个
                        //qDebug()<<cs.status;
                        //如果当前牌型比bt当前值大，直接赋值
                        if(cs.status>bt){
                            bt=cs.status;//赋值
                            output=cs;
                        }else if(cs.status==bt){
                            //如果当前牌型与bt当前值一样大，需要比较那个大
                            //这个函数是用来比较结果的，这里也能用
                            int r= CardsCompare(cs,output);
                            switch(r){
                            case 1:
                                output=cs;
                                break;
                            case 0:
                            case 2:
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    //当前检测到最大牌型为
    // qDebug()<<"max brand type";
    // qDebug()<<output.status;
    // qDebug()<<output.card[0].num()<<output.card[0].CardDecor;
    // qDebug()<<output.card[1].num()<<output.card[1].CardDecor;
    // qDebug()<<output.card[2].num()<<output.card[2].CardDecor;
    // qDebug()<<output.card[3].num()<<output.card[3].CardDecor;
    // qDebug()<<output.card[4].num()<<output.card[4].CardDecor;
}

void CompareCards::checkBranchType(Cards &cards)
{
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
        cards.Data.straight.start = cards.card[0].num();
        cards.Data.straight.end = cards.card[4].num();
        return;
    }

    //四条
    //满足 四条
    //如果是同花就优先判断为四条
    if(four && !flush){
        cards.status = BrandType::FourOfaKind;
        cards.Data.four.fourc = cards.card[0].num();
        cards.Data.four.c = cards.card[4].num();
        return;
    }

    //葫芦
    // 满足 葫芦 不能是 三条 不能是 对子
    // 如果是同花则优先判断为葫芦
    if(fullhouse && !flush && three && pair){
        cards.status = BrandType::FullHouse;
        cards.Data.full.threec = cards.card[0].num();
        cards.Data.full.pair = cards.card[3].num();
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
        cards.Data.straight.start = cards.card[0].num();
        cards.Data.straight.end = cards.card[4].num();
        return;
    }

    //三条
    //满足 不能是同花 不能是四条 不能是葫芦
    //如果是三带二，优先判断为葫芦
    if(!flush && !four && !fullhouse && three){
        cards.status = BrandType::ThreeOfaKind;
        cards.Data.three.threec = cards.card[0].num();
        cards.Data.three.c[0] = cards.card[3].num();
        cards.Data.three.c[1] = cards.card[4].num();
        return;
    }

    //两对
    //满足 不能是同花 不能是一对 不能是三条 不能是四条
    if(!flush && pairs && !three && !four){
        cards.status = BrandType::TwoPair;
        //第一对
        cards.Data.pairs.pairc1 = cards.card[0].num();
        //第二对
        cards.Data.pairs.pairc2 = cards.card[2].num();
        //剩余的数值
        cards.Data.pairs.c = cards.card[4].num();
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
            if(cards.card[i].num() == cards.card[i-1].num()){
                cards.Data.pair.pairc=cards.card[i].num();
            }
        }
        //在判断单牌
        int index=0;
        for(int i=4;i>=0;i--){
            if(cards.Data.pair.pairc != cards.card[i].num()){
                cards.Data.pair.c[index++]=cards.card[i].num();
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

int CompareCards::CardsCompare(Cards cards1, Cards cards2, int compareType)
{
    //首先两个玩家的牌要有效
    if(cards1.status != None && cards2.status != None){
        //此时两个玩家牌都有效
        //先对比牌型
        //qDebug()<<cards1.status<<cards2.status;
        if(cards1.status > cards2.status){
            return 1;//玩家1赢
        }else if(cards1.status == cards2.status){
            //如果仅仅是对比牌型
            if(compareType==CardsType){
                return 0;
            }else if(compareType == CardNum){
            // 不仅对比牌型还要对比数值
                //同牌型要对比类型
                switch(cards1.status){
                case RoyalFlush:
                {
                    //皇家同花顺，如果两个用户都是皇家同花顺就是平局
                    return 0;
                    break;
                }
                case FourOfaKind:
                {
                    //四条
                    // qDebug()<<cards1.Data.four.fourc
                    //          <<cards1.Data.four.c;
                    // qDebug()<<cards2.Data.four.fourc
                    //          <<cards2.Data.four.c;
                    //四条
                    if(cards1.Data.four.fourc > cards2.Data.four.fourc){
                        return 1;
                    }else if(cards1.Data.four.fourc == cards2.Data.four.fourc){
                        //四条一样，判断单牌
                        if(cards1.Data.four.c > cards2.Data.four.c){
                            return 1;
                        }else if(cards1.Data.four.c == cards2.Data.four.c){
                            return 0;//一样
                        }else{
                            return 2;
                        }
                    }else{
                        return 2;
                    }
                    break;
                }
                case FullHouse:
                {
                    //葫芦
                    // qDebug()<<cards1.Data.full.threec
                    //          <<cards1.Data.full.pair;
                    // qDebug()<<cards2.Data.full.threec
                    //          <<cards2.Data.full.pair;
                    //三条
                    if(cards1.Data.full.threec > cards2.Data.full.threec){
                        return 1;
                    }else if (cards1.Data.full.threec == cards2.Data.full.threec){
                        //三条一样，比较对子
                        if(cards1.Data.full.pair > cards2.Data.full.pair){
                            return 1;
                        }else if (cards1.Data.full.pair == cards2.Data.full.pair){
                            return 0;//一样
                        }else{
                            return 2;
                        }
                    }else{
                        return 2;
                    }
                    break;
                }
                case StraightFlush:
                case Straight:
                {
                    //顺子 同花顺
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
                    // qDebug()<<cards1.card[0].num()
                    //          <<cards1.card[1].num()
                    //          <<cards1.card[2].num()
                    //          <<cards1.card[3].num()
                    //          <<cards1.card[4].num();
                    // qDebug()<<cards2.card[0].num()
                    //          <<cards2.card[1].num()
                    //          <<cards2.card[2].num()
                    //          <<cards2.card[3].num()
                    //          <<cards2.card[4].num();
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
                case Flush://同花
                case HighCard://高牌
                {
                    // qDebug()<<cards1.card[0].num()
                    //          <<cards1.card[1].num()
                    //          <<cards1.card[2].num()
                    //          <<cards1.card[3].num()
                    //          <<cards1.card[4].num();
                    // qDebug()<<cards2.card[0].num()
                    //          <<cards2.card[1].num()
                    //          <<cards2.card[2].num()
                    //          <<cards2.card[3].num()
                    //          <<cards2.card[4].num();
                    if(cards1.card[0].num() > cards2.card[0].num()){
                        return 1;
                    }else if(cards1.card[0].num() == cards2.card[0].num()){
                        //最大的相同，比较小的
                        if(cards1.card[1].num() > cards2.card[1].num()){
                            return 1;
                        }else if(cards1.card[1].num() == cards2.card[1].num()){
                            //较大的相同，比较小的
                            if(cards1.card[2].num() > cards2.card[2].num()){
                                return 1;
                            }else if(cards1.card[2].num() == cards2.card[2].num()){
                                //最大的相同，比较小的
                                if(cards1.card[3].num() > cards2.card[3].num()){
                                    return 1;
                                }else if(cards1.card[3].num() == cards2.card[3].num()){
                                    //最大的相同，比较小的
                                    if(cards1.card[4].num() > cards2.card[4].num()){
                                        return 1;
                                    }else if(cards1.card[4].num() == cards2.card[4].num()){
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
            }// if num()
        }else{
            return 2;//玩家2赢
        }
    }else{
        return -1;// None & None
    }

    return -1;//异常
}
