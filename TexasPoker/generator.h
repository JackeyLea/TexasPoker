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

    ///
    /// 获取一张不重复的牌
    /// \brief getIndepentCard
    /// \return
    ///
    Card getIndepentCard();

    ///
    /// 获取5张不重复的牌
    /// \brief getCards
    /// \return
    ///
    QList<Card> getCards();

    ///
    /// 获取2张不重复的牌
    /// \brief get2Cards
    /// \return
    ///
    QList<Card> get2Cards();

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

    QList<Card> existCard;//记录已经发过的牌

    static Generator *s_instance;//单例模式
};

#endif // GENERATOR_H
