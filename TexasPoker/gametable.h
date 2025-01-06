///////////////////
/// \author JackeyLea
/// \date 2025.01.06
/// \note 游戏牌桌类 玩家 总筹码
///////////////////

#ifndef GAMETABLE_H
#define GAMETABLE_H

#include "gameplayer.h"

class GameTable
{
public:
    GameTable();

    /// 设置大盲注大小
    /// \brief setBigBlind
    /// \param bb
    ///
    void setBigBlind(uint bb);

    /// 设置是否无限加注
    /// \brief setNoLimitRaise
    /// \param noLimit
    ///
    void setNoLimitRaise(bool noLimit);

    /// 检测玩家是否存在
    /// \brief checkPlayerIsExist
    /// \param newPlayer
    /// \return
    ///
    bool checkPlayerIsExist(GamePlayer newPlayer);

    /// 牌桌添加玩家
    /// \brief addPlayer
    /// \param player
    ///
    void addPlayer(GamePlayer player);

    /// 删除指定玩家
    /// \brief delPlayer
    /// \param existedPlayer
    ///
    void delPlayer(GamePlayer existedPlayer);

    /// 重置牌桌信息
    /// \brief clear
    ///
    void clear();

private:
    uint m_unBigBlind;//牌桌大盲注大小
    bool m_bNoLimitRaise;//是否无限加注
    uint m_unRaiseTime;//当前加注次数
    uint m_unRaiseLoop;//加注轮数 一轮最多加注3次，最多有2轮
    uint m_unTotalChips;//当前牌桌的总筹码数
    QList<GamePlayer> m_lPlayers;//当前牌桌的玩家，一次游戏最少2人，最多22人，一般是2-10
    QList<Card> m_lFlop;//3张公共牌
    // 玩家ID <操作,操作参数>
    // 比如 玩家1 下注 500
    QList<QPair<int,QPair<int, int>>> m_lActions;//记录玩家操作
};

#endif // GAMETABLE_H
