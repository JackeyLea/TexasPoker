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

void Generator::startNewGame()
{
    //开启新牌
    qDebug()<<"new cards";
    m_lExistCard.clear();
}

Card Generator::getCard()
{
    Card c;
    c.clear();
    do{
        int decor= QRandomGenerator::global()->bounded(1,5);
        int num = QRandomGenerator::global()->bounded(2,15);
        c.setDecor((Card::Decor)decor);
        c.setNum((Card::Number)num);
        //qDebug()<<c.decor()<<c.num();
        //qDebug()<<c.decor()<<c.num();
    }while(checkExistCard(c));
    m_lExistCard.append(c);

    return c;
}

QList<Card> Generator::get2Cards()
{
    QList<Card> cards;
    for(int i=0;i<2;i++){
        Card c = getCard();
        cards.append(c);
    }

    return cards;
}

QList<Card> Generator::get3Cards()
{
    QList<Card> cards;
    for(int i=0;i<3;i++){
        Card c = getCard();
        cards.append(c);
    }

    return cards;
}

bool Generator::checkExistCard(Card c)
{
    //如果一副牌已经发完或者还没有发
    int num = m_lExistCard.size();
    if(num==0) return false;
    if(num>=52) return true;

    //花色和数值一样就是相同的牌
    for(int i=0;i<num;i++){
        Card temp = m_lExistCard.at(i);
        if((temp.decor()==c.decor())
            && (temp.num()==c.num())){
            return true;
        }
    }

    return false;
}
