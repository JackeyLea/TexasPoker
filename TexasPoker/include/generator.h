///////////////////
/// \author JackeyLea
/// \date 2024.08.19
/// \note 发牌类
///////////////////

#ifndef GENERATOR_H
#define GENERATOR_H

#include "card.h"

#include <QList>

class Generator
{
public:
    ///
    /// 单例对象函数
    /// \brief instance
    /// \return
    ///
    static Generator* instance();

    /// 重新发牌
    /// \brief startNewGame
    ///
    void startNewGame();

    ///
    /// 获取一张不重复的牌
    /// \brief getCard
    /// \return
    ///
    Card getCard();

    ///
    /// 获取2张不重复的牌
    /// \brief get2Cards
    /// \return
    ///
    QList<Card> get2Cards();

    /// 获取3张不重复的牌 flop
    /// \brief get3Cards
    /// \return
    ///
    QList<Card> get3Cards();

    ///
    /// 检测此牌是否存在
    /// \brief checkExistCard
    /// \param c
    /// \return
    ///
    bool checkExistCard(Card c);

private:
    ///
    /// 构造函数
    /// \brief Generator
    ///
    Generator(){}

    QList<Card> m_lExistCard;//记录已经发过的牌

    static Generator *s_instance;//单例模式
};

#endif // GENERATOR_H
