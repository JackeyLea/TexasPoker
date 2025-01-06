//////////////
/// \author JackeyLea
/// \date 2025.01.06
/// \note 一张扑克牌，德州扑克不使用鬼牌，A最大，相同牌型不分花色
//////////////

#ifndef CARD_H
#define CARD_H

class Card
{
public:
    //牌花色
    enum Decor{
        //无花色 未定义
        DecorNone=0,
        //黑桃
        Spade,
        //红桃
        Heart,
        //方块
        Diamond,
        //梅花
        Club,
    };

    //牌大小
    enum Number{
        //无值 未定义
        NumNone=0,
        Num_2=2,
        Num_3,
        Num_4,
        Num_5,
        Num_6,
        Num_7,
        Num_8,
        Num_9,
        Num_10,
        Num_J,
        Num_Q,
        Num_K,
        //方便使用
        Num_A
    };
    Card();
    Card(Decor dec=DecorNone,Number num=NumNone);

    /// 获取花色
    /// \brief decor
    /// \return
    ///
    Decor decor();

    /// 获取数值
    /// \brief num
    /// \return
    ///
    Number num();

    /// 清空牌 设置默认值
    /// \brief clear
    ///
    void clear();
private:
    //牌 一张牌由花色和数字组成，比如黑桃A
    Decor  m_eDecor;//牌 花色
    Number m_eNumber;//牌 数值
};

#endif // CARD_H
