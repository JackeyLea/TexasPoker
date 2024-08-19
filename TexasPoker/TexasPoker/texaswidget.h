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

private:
    Ui::TexasWidget *ui;
};
#endif // TEXASWIDGET_H
