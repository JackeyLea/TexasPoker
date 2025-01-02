#ifndef SETUPWIDGET_H
#define SETUPWIDGET_H

#include <QWidget>

namespace Ui {
class SetupWidget;
}

class SetupWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SetupWidget(QWidget *parent = nullptr);
    ~SetupWidget();

private:
    Ui::SetupWidget *ui;
};

#endif // SETUPWIDGET_H
