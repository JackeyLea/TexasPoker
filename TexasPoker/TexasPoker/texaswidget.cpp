#include "texaswidget.h"
#include "ui_texaswidget.h"

TexasWidget::TexasWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TexasWidget)
    ,decor(0)
    ,num(2)
{
    ui->setupUi(this);

    //设置默认图片
    ui->labelImg->setPixmap(QPixmap(":/resources/images/back.svg"));
}

TexasWidget::~TexasWidget()
{
    delete ui;
}

void TexasWidget::displayCard()
{
    QString path = QString(":/resources/images/%1%2.svg").arg(decor).arg(num);
    ui->labelImg->setPixmap(QPixmap(path));
}


void TexasWidget::on_comboBoxNum_currentTextChanged(const QString &txt)
{
    num = txt.toInt();
    displayCard();
}


void TexasWidget::on_comboBoxDecor_currentTextChanged(const QString &txt)
{
    decor = txt.toInt();
    displayCard();
}

