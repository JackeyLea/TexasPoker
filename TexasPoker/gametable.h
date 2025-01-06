///////////////////
/// \author JackeyLea
/// \date 2025.01.06
/// \note 游戏牌桌类 玩家 总筹码
///////////////////

#ifndef GAMETABLE_H
#define GAMETABLE_H

#include <QDebug>

#include "gameplayer.h"

class GameTable
{
public:
    //流程
    enum GameFlow{
        //未开始
        NotStart=0,
        //发底牌
        Perflop,
        //弃牌
        Flod,
        //发公共牌
        Flop,
        //发第4张牌
        Turn,
        //发第5张牌
        River,
        //比牌
        ShowHand
    };

    //下注流程
    enum BetFlow{
        //未下注
        NoBet=0,
        //小盲注
        SmallBlind,
        //大盲注
        BigBlind,
        //下注
        Bet,
        //加注
        Raise,
        //跟注
        Call,
        //让牌
        Check,
        //全押
        AllIn
    };

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

    /// 获取一位玩家数据
    /// \brief player
    /// \param seatID
    /// \return
    ///
    GamePlayer player(uint seatID);

    /// 重置牌桌信息
    /// \brief clear
    ///
    void clear();

private:
    GameFlow m_eGameFlow;//当前游戏阶段
    BetFlow m_eBetFlow;//当前下注阶段
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
