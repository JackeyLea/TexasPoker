#ifndef GENERATOR_H
#define GENERATOR_H

#include "card.h"

#include <QList>

class Generator
{
public:
    static Generator* instance();

    Card getIndepentCard();
    QList<Card> getCards();

    bool checkExistCard(Card c);

private:
    Generator();

    QList<Card> existCard;

    static Generator *s_instance;
};

#endif // GENERATOR_H
