/////////////////////
/// \author JackeyLea
/// \date 2025.01.02
/// \note 游戏设置类
/////////////////////

#ifndef SETUPWIDGET_H
#define SETUPWIDGET_H

#include <QWidget>

#include "texaswidget.h"

namespace Ui {
class SetupWidget;
}

class SetupWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SetupWidget(QWidget *parent = nullptr);
    ~SetupWidget();

private slots:
    void on_btnJoin_clicked();

    void on_btnCance_clicked();

private:
    Ui::SetupWidget *ui;

    TexasWidget *m_pTexasWidget;
};

#endif // SETUPWIDGET_H
