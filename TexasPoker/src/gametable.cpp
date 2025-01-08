#include "gametable.h"

GameTable::GameTable()
    :m_eGameFlow(NotStart)
    ,m_eBetFlow(NoBet)
    ,m_unBigBlind(0)
    ,m_bNoLimitRaise(false)
    ,m_unRaiseTime(0)
    ,m_unRaiseLoop(0)
    ,m_unTotalChips(0)
{
    m_lActions.clear();
}

GameTable::GameTable(uint bb, bool noLimit)
    :m_eGameFlow(NotStart)
    ,m_eBetFlow(NoBet)
    ,m_unBigBlind(bb)
    ,m_bNoLimitRaise(noLimit)
    ,m_unRaiseTime(0)
    ,m_unRaiseLoop(0)
    ,m_unTotalChips(0)
{
    m_lActions.clear();
}

void GameTable::setGameStep(GameFlow flow)
{
    m_eGameFlow = flow;
}

void GameTable::setBetStep(BetFlow flow)
{
    m_eBetFlow = flow;
}

void GameTable::setBigBlind(uint bb)
{
    //判断
    assert(bb%2==0);//大盲注决定小盲注，大盲注必须是2的倍数
    m_unBigBlind = bb;
}

uint GameTable::bigBlind()
{
    return m_unBigBlind;
}

uint GameTable::smallBlind()
{
    return m_unBigBlind/2;
}

void GameTable::setNoLimitRaise(bool noLimit)
{
    m_bNoLimitRaise = noLimit;
}

bool GameTable::checkPlayerIsExist(GamePlayer newPlayer)
{
    if(m_lPlayers.size()==0) return false;
    for(int i=0;i<m_lPlayers.size();i++){
        GamePlayer player = m_lPlayers[i];
        if(player.playerID() == newPlayer.playerID()){
            return true;
        }
    }
    return false;
}

void GameTable::addPlayer(GamePlayer player)
{
    //检测
    if(checkPlayerIsExist(player)){
        qDebug()<<"This player is in table now.";
        return;//如果玩家已存在就不添加
    }
    m_lPlayers.append(player);
}

void GameTable::delPlayer(GamePlayer existedPlayer)
{
    if(m_lPlayers.size()==0) return;
    for(int i=0;i<m_lPlayers.size();i++){
        GamePlayer player = m_lPlayers[i];
        if(player.playerID() == existedPlayer.playerID()){
            m_lPlayers.remove(i);
        }
    }
}

GamePlayer GameTable::player(uint seatID)
{
    assert(m_lPlayers.size() != 0);

    GamePlayer player;
    for(int i=0;i<m_lPlayers.size();i++){
        player = m_lPlayers[i];
        if(player.seatID() == seatID){
            break;
        }
    }
    return player;
}

uint GameTable::totalChips()
{
    return m_unTotalChips;
}

void GameTable::clear()
{
    m_lFlop.clear();
    m_lPlayers.clear();
    m_lActions.clear();
}

void GameTable::append(QPair<int, QPair<int, int> > action)
{
    m_lActions.append(action);
}

void GameTable::addBet(uint userId, uint chip)
{
    //玩家下注
    player(userId).addBetChip(chip);
    //桌面总筹码
    m_unTotalChips += chip;
    qDebug()<<"总数"<<m_unTotalChips;
}
