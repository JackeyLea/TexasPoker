#include "card.h"

#include <assert.h>

Card::Card()
    :m_eDecor(DecorNone)
    ,m_eNumber(NumNone)
{
    // NOTHING
}

Card::Card(Decor dec, Number num)
    :m_eDecor(dec)
    ,m_eNumber(num)
{
    assert(dec != Decor::DecorNone);
    assert(num != Number::NumNone);
}

void Card::setDecor(Decor dec)
{
    m_eDecor = dec;
}

void Card::Card::setNum(Number num)
{
    m_eNumber = num;
}

Card::Number Card::num()
{
    return m_eNumber;
}

Card::Decor Card::decor()
{
    return m_eDecor;
}

void Card::clear()
{
    m_eDecor = DecorNone;
    m_eNumber = NumNone;
}

QString Card::name()
{
    QString name;

    switch(m_eDecor){
    case Spade:
        name+="黑桃";
        break;
    case Heart:
        name+="红桃";
        break;
    case Diamond:
        name+="方片";
        break;
    case Club:
        name+="梅花";
        break;
    default:
        name+="无效花色";
        break;
    }

    switch(m_eNumber){
    case Num_2:
    case Num_3:
    case Num_4:
    case Num_5:
    case Num_6:
    case Num_7:
    case Num_8:
    case Num_9:
    case Num_10:
        name+=QString("%1").arg((int)m_eNumber);
        break;
    case Num_J:
        name+="J";
        break;
    case Num_Q:
        name+="Q";
        break;
    case Num_K:
        name+="K";
        break;
    case Num_A:
        name+="A";
        break;
    default:
        name+="无效数字";
        break;
    }

    return name;
}
