#include "poker.h"

#include <QRandomGenerator>
#include <QDebug>
#include <iostream>

Poker* Poker::sinstance = NULL;

Poker::Poker()
{

}

Poker *Poker::instance()
{
    if(!sinstance){
        sinstance = new Poker;
    }
    return sinstance;
}

void Poker::clearExistCard()
{
    existCard.clear();
}

Card Poker::getCard()
{
    Card c;
    do{
        int decor= QRandomGenerator::global()->bounded(0,4);
        int num = QRandomGenerator::global()->bounded(1,14);
        //qDebug()<<decor<<num;
        c.CardDecor=(Decor)decor;
        c.CardNum=(Number)num;
    }while(checkExistCard(c));
    existCard.append(c);

    return c;
}

bool Poker::checkExistCard(Card c)
{
    int num = existCard.size();
    if(num==0) return false;

    for(int i=0;i<num;i++){
        Card temp = existCard.at(i);
        if((temp.CardDecor==c.CardDecor)
                && (temp.CardNum==c.CardNum)){
            return true;
        }
    }

    return false;
}

void Poker::checkCards(QList<Card> cards, Cards &output)
{
    assert(cards.size()==7);

    BrandType bt=None;

    for(int a=0;a<3;a++){
        for(int b=a+1;b<4;b++){
            for(int i=b+1;i<5;i++){
                for(int j=i+1;j<6;j++){
                    for(int z=j+1;z<7;z++){
                        Cards cs;
                        cs.card[0]=cards[a];
                        cs.card[1]=cards[b];
                        cs.card[2]=cards[i];
                        cs.card[3]=cards[j];
                        cs.card[4]=cards[z];
                        cs.status=checkBranchType(cs);
                        qDebug()<<cs.status;
                        if(cs.status>=bt){
                            bt=cs.status;
                        }
                    }
                }
            }
        }
    }

    //结果
    for(int a=0;a<3;a++){
        for(int b=a+1;b<4;b++){
            for(int i=b+1;i<5;i++){
                for(int j=i+1;j<6;j++){
                    for(int z=j+1;z<7;z++){
                        Cards cs;
                        cs.card[0]=cards[a];
                        cs.card[1]=cards[b];
                        cs.card[2]=cards[i];
                        cs.card[3]=cards[j];
                        cs.card[4]=cards[z];
                        cs.status=checkBranchType(cs);
                        if(cs.status==bt){
                            output=cs;
                            break;
                        }
                    }
                }
            }
        }
    }
}

QString Poker::getBrandType(BrandType bt)
{
    QString r;

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
