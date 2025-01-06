////////////////////
/// \author JackeyLea
/// \date 2025.01.06
/// \note 玩家类
////////////////////
#ifndef GAMEPLAYER_H
#define GAMEPLAYER_H

#include <QList>

#include "card.h"

class GamePlayer
{
public:
    GamePlayer();
    GamePlayer(uint playerID,uint seatID,uint chips);

    /// 设置玩家底牌
    /// \brief setCards
    /// \param preflop
    ///
    void setCards(QList<Card> preflop);

    /// 获取玩家的底牌
    /// \brief cards
    /// \return
    ///
    QList<Card> cards();

    /// 设置玩家ID
    /// \brief setPlayerID
    /// \param id
    ///
    void setPlayerID(uint id);

    /// 获取玩家ID
    /// \brief playerID
    /// \return
    ///
    uint playerID();

    /// 设置玩家座位号
    /// \brief setSeatID
    /// \param id
    ///
    void setSeatID(uint id);

    /// 获取座位号
    /// \brief seatID
    /// \return
    ///
    uint seatID();

    /// 获取当前已押上的筹码总数
    /// \brief betChip
    ///
    uint betChip();

    /// 上一把押的筹码数
    /// \brief preChip
    /// \return
    ///
    uint preChip();

    /// 设置玩家所拥有的筹码总数
    /// \brief setChips
    /// \param count
    ///
    void setChips(uint count);

    /// 当前拥有的筹码
    /// \brief chips
    /// \return
    ///
    uint chips();

private:
    QList<Card> m_preflop;//当前玩家所拥有的2张底牌
    uint m_unPlayerID;//玩家ID 从0开始
    uint m_unSeatID;//座位ID 以荷官左手边为0，顺时针排序
    uint m_unBetChip;//已经押上的所有筹码总数
    uint m_unPreChip;//上一把押的筹码数
    uint m_unChips;//当前拥有的筹码数
};

#endif // GAMEPLAYER_H
