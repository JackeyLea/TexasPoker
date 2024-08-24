#include "generator.h"

#include <QRandomGenerator>
#include <QDebug>

Generator* Generator::s_instance = NULL;

Generator *Generator::instance()
{
    if(!s_instance){
        s_instance = new Generator();
    }

    return s_instance;
}

Card Generator::getIndepentCard()
{
    //当前牌不够数量的时候开启新牌
    if(existCard.size()>=52){
        qDebug()<<"new cards";
        existCard.clear();
    }
    Card c;
    c.clear();
    do{
        c = getCard();
        //qDebug()<<c.CardDecor<<c.CardNum;
    }while(checkExistCard(c));
    existCard.append(c);

    return c;
}

QList<Card> Generator::getCards()
{
    QList<Card> cards;
    for(int i=0;i<5;i++){
        Card c = getIndepentCard();
        cards.append(c);
    }

    return cards;
}

bool Generator::checkExistCard(Card c)
{
    int num = existCard.size();
    if(num==0) return false;
    if(num>=52) return true;

    for(int i=0;i<num;i++){
        Card temp = existCard.at(i);
        if((temp.CardDecor==c.CardDecor)
            && (temp.CardNum==c.CardNum)){
            return true;
        }
    }

    return false;
}
