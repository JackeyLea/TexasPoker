#include "gametable.h"


GameTable::GameTable()
{

}

void GameTable::setBigBlind(uint bb)
{
    //判断
    assert(bb%2==0);//大盲注决定小盲注，大盲注必须是2的倍数
    m_unBigBlind = bb;
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
        GamePlayer player = m_lPlayers[i];
        if(player.seatID() == seatID){
            break;
        }
    }
    return player;
}

void GameTable::clear()
{
    m_lFlop.clear();
    m_lPlayers.clear();
    m_lActions.clear();
}
