#include "texaswidget.h"
#include "ui_texaswidget.h"

#include "card.h"
#include "generator.h"

TexasWidget::TexasWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TexasWidget)
{
    ui->setupUi(this);

    label[0] = ui->labelImg1;
    label[1] = ui->labelImg2;
    label[2] = ui->labelImg3;
    label[3] = ui->labelImg4;
    label[4] = ui->labelImg5;

    //设置默认图片
    for(int i=0;i<5;i++){
        label[i]->setPixmap(QPixmap(":/resources/images/back.svg"));
    }
}

TexasWidget::~TexasWidget()
{
    delete ui;
}


void TexasWidget::on_btn_Gen_clicked()
{
    QList<Card> cards = Generator::instance()->getCards();
    assert(cards.size()==5);

    for(int i=0;i<5;i++){
        Card c = cards[i];
        QString path = QString(":/resources/images/%1%2.svg").arg(c.CardDecor).arg(c.CardNum);
        label[i]->setPixmap(QPixmap(path));
    }

    //判断牌型
    Cards cs;
    cs.card[0]=cards[0];
    cs.card[1]=cards[1];
    cs.card[2]=cards[2];
    cs.card[3]=cards[3];
    cs.card[4]=cards[4];
    BrandType bt = checkBranchType(cs);
    ui->lineEditBrand->setText(getBrandType(bt));
}
