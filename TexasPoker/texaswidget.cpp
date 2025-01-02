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
    // 5张公共牌
    m_pLabelPub[0] = ui->labelFlop1;
    m_pLabelPub[1] = ui->labelFlop2;
    m_pLabelPub[2] = ui->labelFlop3;
    m_pLabelPub[3] = ui->labelTurn;
    m_pLabelPub[4] = ui->labelRiver;
    // 用户1
    m_pLabelUser1[0] = ui->labelPerflop1User1;
    m_pLabelUser1[1] = ui->labelPerflop2User1;
    // 用户2
    m_pLabelUser2[0] = ui->labelPerflop1User2;
    m_pLabelUser2[1] = ui->labelPerflop2User2;
    // 用户3
    m_pLabelUser3[0] = ui->labelPerflop1User3;
    m_pLabelUser3[1] = ui->labelPerflop2User3;
}

TexasWidget::~TexasWidget()
{
    delete ui;
}

// void TexasWidget::on_btn_Gen_clicked()
// {
//     //先生成5张公共牌
//     QList<Card> cards = Generator::instance()->getCards();
//     assert(cards.size()==5);

//     for(int i=0;i<5;i++){
//         Card c = cards[i];
//         QString path = QString(":/resources/images/%1%2.svg").arg(c.CardDecor).arg(c.CardNum);
//         label[i]->setPixmap(QPixmap(path));
//     }

//     //生成玩家1牌
//     QList<Card> cards2 = Generator::instance()->get2Cards();
//     assert(cards2.size()==2);
//     for(int i=0;i<2;i++){
//         Card c = cards2[i];
//         QString path = QString(":/resources/images/%1%2.svg").arg(c.CardDecor).arg(c.CardNum);
//         label[i+5]->setPixmap(QPixmap(path));
//     }

//     //生成玩家2牌
//     QList<Card> cards3 = Generator::instance()->get2Cards();
//     assert(cards3.size()==2);
//     for(int i=0;i<2;i++){
//         Card c = cards3[i];
//         QString path = QString(":/resources/images/%1%2.svg").arg(c.CardDecor).arg(c.CardNum);
//         label[i+7]->setPixmap(QPixmap(path));
//     }

//     //组合玩家1的牌
//     QList<Card> cardsPlayer1 = cards + cards2;
//     Cards r1;
//     check7Cards(cardsPlayer1,r1);

//     //判断牌型
//     ui->lineEditBrand->setText(getBrandType(r1.status));

//     //组合玩家2的牌
//     QList<Card> cardsPlayer2 = cards + cards3;
//     Cards r2;
//     check7Cards(cardsPlayer2,r2);

//     //判断牌型
//     ui->lineEditBrand2->setText(getBrandType(r2.status));

//     //对比最终结果
//     char r = CardsCompare(r1,r2);
//     switch(r){
//     case 0:
//         ui->lineEditResult->setText("平局");
//         break;
//     case 1:
//         ui->lineEditResult->setText("玩家A赢");
//         break;
//     case 2:
//         ui->lineEditResult->setText("玩家B赢");
//         break;
//     default:
//         ui->lineEditResult->setText("异常");
//         break;
//     }
// }
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
