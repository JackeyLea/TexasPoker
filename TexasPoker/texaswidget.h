/////////////////////
/// \author JackeyLea
/// \date 2024.08.19
/// \note 人机交互界面类
/////////////////////

#ifndef TEXASWIDGET_H
#define TEXASWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QMap>
#include <QList>

#include "card.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class TexasWidget;
}
QT_END_NAMESPACE

class TexasWidget : public QWidget
{
    Q_OBJECT

public:
    ///
    /// 构造函数
    /// \brief TexasWidget
    /// \param parent
    ///
    TexasWidget(uint BB,bool isNoLimit,uint chips,uint compareType,QWidget *parent = nullptr);

    ///
    /// 析构函数
    ///
    ~TexasWidget();

    /// 简单的概率计算
    /// \brief getNextAction
    /// \return
    ///
    QPair<int,int> getNextAction();

protected:
    /// 统一更新界面上数据
    /// \brief updateTableInfo
    ///
    void updateTableInfo();

    /// 更新玩家下注数据
    /// \brief updateUserBetInfo
    /// \param userId 玩家索引
    /// \param action 玩家动作
    /// \param value 下注值
    ///
    void updateUserBetInfo(int userId,int action,int value);

private slots:
    /// 游戏开始
    /// \brief on_btnStart_clicked
    ///
    void on_btnStart_clicked();

    /// 跟注
    /// \brief on_btnCall_clicked
    ///
    void on_btnUser1Call_clicked();

    /// 加注
    /// \brief on_btnRaise_clicked
    ///
    void on_btnUser1Raise_clicked();

    /// 弃牌
    /// \brief on_btnFold_clicked
    ///
    void on_btnUser1Fold_clicked();

    /// 下注
    /// \brief on_btnUser1Bet_clicked
    ///
    void on_btnUser1Bet_clicked();

private:
    Ui::TexasWidget *ui;

    QLabel* m_pLabelPub[5];//对应界面5张公共牌
    QLabel* m_pLabelUser1[2];//用户1
    QLabel* m_pLabelUser2[2];//用户2
    QLabel* m_pLabelUser3[2];//用户3

    TableInfo m_sTableInfo;//记录当前状态

    bool m_bNewGame;//是否是新游戏
    uchar m_unCompareType;
};
#endif // TEXASWIDGET_H
