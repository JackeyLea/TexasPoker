#include "gameplayer.h"

#include <QDebug>

GamePlayer::GamePlayer()
    :m_unPlayerID(0)
    ,m_unSeatID(0)
    ,m_unBetChip(0)
    ,m_unPreChip(0)
    ,m_unChips(0)
{
    // NOTHING
}

GamePlayer::GamePlayer(uint playerID, uint seatID, uint chips)
    :m_unPlayerID(playerID)
    ,m_unSeatID(seatID)
    ,m_unBetChip(0)
    ,m_unPreChip(0)
    ,m_unChips(chips)
{
    // NOTHING
}

void GamePlayer::setCards(QList<Card> preflop)
{
    //校验
    assert(preflop.size()==2);//只能是2张
    assert(preflop[0].decor()!=Card::DecorNone);
    assert(preflop[0].num()!=Card::NumNone);
    assert(preflop[1].decor()!=Card::DecorNone);
    assert(preflop[1].num()!=Card::NumNone);
    //替换
    if(m_preflop.size()==2){
        m_preflop.clear();
    }
    m_preflop.append(preflop);
}

QList<Card> GamePlayer::cards()
{
    return m_preflop;
}

void GamePlayer::setPlayerID(uint id)
{
    m_unPlayerID = id;
}

uint GamePlayer::playerID()
{
    return m_unPlayerID;
}

void GamePlayer::setSeatID(uint id)
{
    m_unSeatID = id;
}

uint GamePlayer::seatID()
{
    return m_unSeatID;
}

void GamePlayer::addBetChip(uint chip)
{
    m_unPreChip = chip;
    m_unBetChip += chip;
    //押注的同时自己拥有的筹码减少
    m_unChips -=chip;
    qDebug()<<m_unBetChip<<m_unChips;
}

uint GamePlayer::betChip()
{
    return m_unBetChip;
}

uint GamePlayer::preChip()
{
    return m_unPreChip;
}

void GamePlayer::setChips(uint count)
{
    m_unChips = count;
}

uint GamePlayer::chips()
{
    qDebug()<<"player chips"<<this<<m_unChips;
    return m_unChips;
}
