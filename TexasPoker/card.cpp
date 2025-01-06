#include "card.h"

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
    // NOTHING
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
