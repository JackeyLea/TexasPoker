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
    /* 检测牌型判断是否正常
     * 高牌无法独立判断
     * 同花顺由同花和顺子共同判断
     * 皇家同花顺由A、同花、顺子共同判断
     */
};

#endif // TEXASPOKERTEST_H
