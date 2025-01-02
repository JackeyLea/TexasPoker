#include "texaswidget.h"
#include "ui_texaswidget.h"

#include "card.h"
#include "generator.h"

TexasWidget::TexasWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TexasWidget)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/resources/images/poker.svg"));

    //关联界面牌 简化操作
    label[0] = ui->labelImgPub1;
    label[1] = ui->labelImgPub2;
    label[2] = ui->labelImgPub3;
    label[3] = ui->labelImgPub4;
    label[4] = ui->labelImgPub5;
    label[5] = ui->labelImg1Player1;
    label[6] = ui->labelImg2Player1;
    label[7] = ui->labelImg1Player2;
    label[8] = ui->labelImg2Player2;

    //设置默认图片
    for(int i=0;i<9;i++){
        label[i]->setPixmap(QPixmap(":/resources/images/back.svg"));
    }
}

TexasWidget::~TexasWidget()
{
    delete ui;
}

void TexasWidget::on_btn_Gen_clicked()
{
    //先生成5张公共牌
    QList<Card> cards = Generator::instance()->getCards();
    assert(cards.size()==5);

    for(int i=0;i<5;i++){
        Card c = cards[i];
        QString path = QString(":/resources/images/%1%2.svg").arg(c.CardDecor).arg(c.CardNum);
        label[i]->setPixmap(QPixmap(path));
    }

    //生成玩家1牌
    QList<Card> cards2 = Generator::instance()->get2Cards();
    assert(cards2.size()==2);
    for(int i=0;i<2;i++){
        Card c = cards2[i];
        QString path = QString(":/resources/images/%1%2.svg").arg(c.CardDecor).arg(c.CardNum);
        label[i+5]->setPixmap(QPixmap(path));
    }

    //生成玩家2牌
    QList<Card> cards3 = Generator::instance()->get2Cards();
    assert(cards3.size()==2);
    for(int i=0;i<2;i++){
        Card c = cards3[i];
        QString path = QString(":/resources/images/%1%2.svg").arg(c.CardDecor).arg(c.CardNum);
        label[i+7]->setPixmap(QPixmap(path));
    }

    //组合玩家1的牌
    QList<Card> cardsPlayer1 = cards + cards2;
    Cards r1;
    check7Cards(cardsPlayer1,r1);

    //判断牌型
    ui->lineEditBrand->setText(getBrandType(r1.status));

    //组合玩家2的牌
    QList<Card> cardsPlayer2 = cards + cards3;
    Cards r2;
    check7Cards(cardsPlayer2,r2);

    //判断牌型
    ui->lineEditBrand2->setText(getBrandType(r2.status));

    //对比最终结果
    char r = CardsCompare(r1,r2);
    switch(r){
    case 0:
        ui->lineEditResult->setText("平局");
        break;
    case 1:
        ui->lineEditResult->setText("玩家A赢");
        break;
    case 2:
        ui->lineEditResult->setText("玩家B赢");
        break;
    default:
        ui->lineEditResult->setText("异常");
        break;
    }
}
