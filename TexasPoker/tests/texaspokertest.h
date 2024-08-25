////////////////////////////////////////
/// \author JackeyLea
/// \date 2024-01-14
/// \brief 单元测试类
////////////////////////////////////////

#ifndef TEXASPOKERTEST_H
#define TEXASPOKERTEST_H

#include <QObject>
#include <QtTest/QTest>

class TexasPokerTest : public QObject
{
    Q_OBJECT

private slots:
    /// 检测getBrandType牌型检测函数
    /// \brief case_checkGetBrandType
    ///
    void case_checkGetBrandType();

    /// 检测牌排序功能
    /// \brief case_checkStraightCards
    ///
    void case_checkStraightCards();

    /// 检测牌中是否有重复牌
    /// \brief case_checkIsDuplicate
    ///
    void case_checkIsDuplicate();

    /// 检测5张牌是否一样
    /// \brief case_checkIs5
    ///
    void case_checkIs5();

    /// 检测一对
    /// \brief case_checkOnePair
    ///
    void case_checkOnePair();

    ///
    /// 判断两对
    /// \brief case_checkTwoPair
    ///
    void case_checkTwoPair();

    ///
    /// 检测三条
    /// \brief case_checkThreeKind
    ///
    void case_checkThreeKind();

    /// 检测顺子
    /// \brief case_checkStraight
    ///
    void case_checkStraight();

    /// 检测同花
    /// \brief case_checkFlush
    ///
    void case_checkFlush();

    ///
    /// 检测葫芦
    /// \brief case_checkFullhouse
    ///
    void case_checkFullhouse();

    ///
    /// 测试四条
    /// \brief case_checkFourKind
    ///
    void case_checkFourKind();

    /// 检测当前5张牌是否包含A
    /// \brief case_checkA
    ///
    void case_checkA();

    /// 检测牌型判断是否正常
    /// 高牌无法独立判断，同花顺由同花和顺子共同判断，皇家同花顺由A、同花、顺子共同判断
    /// \brief case_checkBrandType
    ///
    void case_checkBrandType();

    /// 不同的牌型对比
    /// \brief case_CardsCompare
    ///
    void case_CardsCompare();

    /// 不同高牌对比
    /// \brief case_HighCardCompare
    ///
    void case_HighCardCompare();

    /// 不同一对对比
    /// \brief case_OnePairCompare
    ///
    void case_OnePairCompare();

    /// 不同两对对比
    /// \brief case_TwoPairCompare
    ///
    void case_TwoPairCompare();

    ///
    /// 不同三条对比
    /// \brief case_ThreeCompare
    ///
    void case_ThreeCompare();

    void case_StraightCompare();
};

#endif // TEXASPOKERTEST_H
