/////////////////////
/// \author JackeyLea
/// \date 2024.08.19
/// \note 人机交互界面类
/////////////////////

#ifndef TEXASWIDGET_H
#define TEXASWIDGET_H

#include <QWidget>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui {
class TexasWidget;
}
QT_END_NAMESPACE

//用户信息
typedef struct _user{
    uint bet;//用户下的筹码
    Card perflop1;
    Card perflop2;
}UserInfo;

//牌桌信息
typedef struct _table{
    uint bb;//大盲注
    bool isNoLimit;//是否无限加注
    uint bet;//总筹码数
    GameFlow eGameFlow;//当前游戏阶段
    BetFlow eBetFlow;//当前下注阶段
    UserInfo user[3];//目前只有3个用户
    Card flop[3];//3张公共牌
    // 用户ID <操作,操作参数>
    // 比如 用户1 下注 500
    QList<QMap<int,QPair<int, int>>> actionList;//记录用户操作
}TableInfo;

class TexasWidget : public QWidget
{
    Q_OBJECT

public:
    ///
    /// 构造函数
    /// \brief TexasWidget
    /// \param parent
    ///
    TexasWidget(QWidget *parent = nullptr);

    ///
    /// 析构函数
    ///
    ~TexasWidget();

private slots:
    /// 游戏开始
    /// \brief on_btnStart_clicked
    ///
    void on_btnStart_clicked();

private:
    Ui::TexasWidget *ui;

    QLabel* m_pLabelPub[5];//对应界面5张公共牌
    QLabel* m_pLabelUser1[2];//用户1
    QLabel* m_pLabelUser2[2];//用户2
    QLabel* m_pLabelUser3[2];//用户3

    TableInfo m_sTableInfo;//记录当前状态
};
#endif // TEXASWIDGET_H
