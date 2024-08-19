#include "texaswidget.h"
#include "ui_texaswidget.h"

TexasWidget::TexasWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TexasWidget)
{
    ui->setupUi(this);
}

TexasWidget::~TexasWidget()
{
    delete ui;
}
