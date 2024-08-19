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
    TexasWidget(QWidget *parent = nullptr);
    ~TexasWidget();

private slots:
    void on_btn_Gen_clicked();

private:
    Ui::TexasWidget *ui;

    int decor;
    int num;
    QLabel* label[5];
};
#endif // TEXASWIDGET_H
