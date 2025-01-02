#include "setupwidget.h"
#include "ui_setupwidget.h"

SetupWidget::SetupWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetupWidget)
{
    ui->setupUi(this);
}

SetupWidget::~SetupWidget()
{
    delete ui;
}
