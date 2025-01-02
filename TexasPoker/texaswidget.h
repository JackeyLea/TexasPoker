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
