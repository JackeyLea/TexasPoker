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
    void on_btn_Gen_clicked();

private:
    Ui::TexasWidget *ui;

    QLabel* label[9];//对应界面两个用户的5+2+2张牌
};
#endif // TEXASWIDGET_H
