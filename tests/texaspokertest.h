////////////////////////
/// \author JackeyLea
/// \date 2024-01-14
/// \brief 单元测试类
////////////////////////

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

    ///
    ///  不同顺子对比
    /// \brief case_StraightCompare
    ///
    void case_StraightCompare();

    ///
    /// 不同同花比较
    /// \brief case_FlushCompare
    ///
    void case_FlushCompare();

    ///
    /// 不同葫芦比较
    /// \brief case_FullhouseCompare
    ///
    void case_FullhouseCompare();

    ///
    /// 不同四条对比
    /// \brief case_FourCompare
    ///
    void case_FourCompare();

    ///
    /// 不同同花顺比较
    /// \brief case_StraightFlushCompare
    ///
    void case_StraightFlushCompare();

    ///
    /// 检测7选5功能是否正常
    /// 要能正确的检测出高牌，有多个高牌时要能正确检测出大的那个
    /// \brief case_check7Cards
    ///
    void case_check7Cards_HighCards();

    ///
    /// 检测一对，并取最大的一个
    /// \brief case_check7Cards_OnePair
    ///
    void case_check7Cards_OnePair();

    ///
    /// 检测两对，并取最大的一个
    /// \brief case_check7Cards_TwoPair
    ///
    void case_check7Cards_TwoPair();

    ///
    /// 检测三条，并取最大的一个
    /// \brief case_check7Cards_Three
    ///
    void case_check7Cards_Three();

    ///
    /// 检测顺子，并取最大的一个
    /// \brief case_check7Cards_Straight
    ///
    void case_check7Cards_Straight();

    ///
    /// 检测同花，并取最大的一个
    /// \brief case_check7Cards_Flush
    ///
    void case_check7Cards_Flush();

    ///
    /// 检测葫芦，并取最大的一个
    /// \brief case_check7Cards_Fullhouse
    ///
    void case_check7Cards_Fullhouse();

    ///
    /// 检测四条，并取最大的一个
    /// \brief case_check7Cards_Four
    ///
    void case_check7Cards_Four();

    ///
    /// 检测同花顺，并取最大的一个
    /// \brief case_check7Cards_StraightFlush
    ///
    void case_check7Cards_StraightFlush();

    ///
    /// 检测皇家同花顺，并取最大的一个
    /// \brief case_check7Cards_RoyalFlush
    ///
    void case_check7Cards_RoyalFlush();
};

#endif // TEXASPOKERTEST_H
