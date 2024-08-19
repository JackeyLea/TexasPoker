#ifndef TEXASWIDGET_H
#define TEXASWIDGET_H

#include <QWidget>

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

    void displayCard();

private slots:
    void on_comboBoxNum_currentTextChanged(const QString &txt);

    void on_comboBoxDecor_currentTextChanged(const QString &txt);

private:
    Ui::TexasWidget *ui;

    int decor;
    int num;
};
#endif // TEXASWIDGET_H
