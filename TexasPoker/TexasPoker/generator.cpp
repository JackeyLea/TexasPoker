#include "generator.h"

#include <QRandomGenerator>

Generator* Generator::s_instance = NULL;

Generator *Generator::instance()
{
    if(!s_instance){
        s_instance = new Generator();
    }

    s_instance->clearExistCard();

    return s_instance;
}

void Generator::clearExistCard()
{
    existCard.clear();
}

Card Generator::getCard()
{
    Card c;
    do{
        int decor= QRandomGenerator::global()->bounded(0,4);
        int num = QRandomGenerator::global()->bounded(2,15);
        //qDebug()<<decor<<num;
        c.CardDecor=(Decor)decor;
        c.CardNum=(Number)num;
    }while(checkExistCard(c));
    existCard.append(c);

    return c;
}

QList<Card> Generator::getCards()
{
    QList<Card> cards;
    for(int i=0;i<5;i++){
        Card c = getCard();
        cards.append(c);
    }

    return cards;
}

bool Generator::checkExistCard(Card c)
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

Generator::Generator() {}

