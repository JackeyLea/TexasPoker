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
    label[5] = ui->labelImg11;
    label[6] = ui->labelImg12;
    label[7] = ui->labelImg13;
    label[8] = ui->labelImg14;
    label[9] = ui->labelImg15;

    //设置默认图片
    for(int i=0;i<10;i++){
        label[i]->setPixmap(QPixmap(":/resources/images/back.svg"));
    }
}

TexasWidget::~TexasWidget()
{
    delete ui;
}


void TexasWidget::on_btn_Gen_clicked()
{
    Generator::instance()->clearExistCard();
    QList<Card> cards = Generator::instance()->getCards();
    assert(cards.size()==5);

    for(int i=0;i<5;i++){
        Card c = cards[i];
        QString path = QString(":/resources/images/%1%2.svg").arg(c.CardDecor).arg(c.CardNum);
        label[i]->setPixmap(QPixmap(path));
    }

    QList<Card> cards2 = Generator::instance()->getCards();
    assert(cards2.size()==5);
    for(int i=0;i<5;i++){
        Card c = cards2[i];
        QString path = QString(":/resources/images/%1%2.svg").arg(c.CardDecor).arg(c.CardNum);
        label[i+5]->setPixmap(QPixmap(path));
    }

    //判断牌型
    Cards cs;
    cs.card[0]=cards[0];
    cs.card[1]=cards[1];
    cs.card[2]=cards[2];
    cs.card[3]=cards[3];
    cs.card[4]=cards[4];
    checkBranchType(cs);
    ui->lineEditBrand->setText(getBrandType(cs.status));

    //玩家2
    Cards cs2;
    cs2.card[0]=cards2[0];
    cs2.card[1]=cards2[1];
    cs2.card[2]=cards2[2];
    cs2.card[3]=cards2[3];
    cs2.card[4]=cards2[4];
    checkBranchType(cs2);
    ui->lineEditBrand2->setText(getBrandType(cs2.status));

    char r = CardsCompare(cs,cs2);
    switch(r){
    case 0:
        ui->labelResult->setText("平局");
        break;
    case 1:
        ui->labelResult->setText("玩家A赢");
        break;
    case 2:
        ui->labelResult->setText("玩家B赢");
        break;
    default:
        ui->labelResult->setText("异常");
        break;
    }
}
