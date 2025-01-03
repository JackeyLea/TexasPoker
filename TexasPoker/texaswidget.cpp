#include "texaswidget.h"
#include "ui_texaswidget.h"

#include "card.h"
#include "generator.h"

#include <QMessageBox>

TexasWidget::TexasWidget(uint BB, bool isNoLimit, uint chips, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TexasWidget)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/resources/images/poker.svg"));

    //初始化变量
    m_sTableInfo.clear();
    m_sTableInfo.bb = BB;
    m_sTableInfo.isNoLimit = isNoLimit;
    for(int i=0;i<2;i++){
        m_sTableInfo.user[i].chip=chips;
    }
    //刷新界面
    updateTableInfo();

    //关联界面牌 简化操作
    // 5张公共牌
    m_pLabelPub[0] = ui->labelFlop1;
    m_pLabelPub[1] = ui->labelFlop2;
    m_pLabelPub[2] = ui->labelFlop3;
    m_pLabelPub[3] = ui->labelTurn;
    m_pLabelPub[4] = ui->labelRiver;
    // 用户1
    m_pLabelUser1[0] = ui->labelPerflop1User2;
    m_pLabelUser1[1] = ui->labelPerflop2User2;
    // 用户2
    m_pLabelUser2[0] = ui->labelPerflop1User1;
    m_pLabelUser2[1] = ui->labelPerflop2User1;
}

TexasWidget::~TexasWidget()
{
    delete ui;
}

void TexasWidget::updateTableInfo()
{
    //玩家1
    ui->labelUser2Chip->setText(QString::number(m_sTableInfo.user[0].chip));
    //玩家2
    ui->labelUser1Chip->setText(QString::number(m_sTableInfo.user[1].chip));
    //界面
    ui->txtBet->setText(QString::number(m_sTableInfo.bet));
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

void TexasWidget::on_btnStart_clicked()
{
    ////游戏开始
    m_sTableInfo.eGameFlow=NotStart;
    m_sTableInfo.eBetFlow=NoBet;
    ///发底牌
    m_sTableInfo.eGameFlow= Perflop;
    //用户1
    QList<Card> cards = Generator::instance()->get2Cards();
    assert(cards.size()==2);
    m_sTableInfo.user[0].perflop1 = cards[0];
    m_sTableInfo.user[0].perflop2 = cards[1];
    m_sTableInfo.actionList.append(qMakePair(0,qMakePair(Perflop,-1)));
    //用户1是自己，需要显示牌
    for(int i=0;i<2;i++){
        Card c = cards[i];
        QString path = QString(":/resources/images/%1%2.svg").arg(c.CardDecor).arg(c.CardNum);
        m_pLabelUser2[i]->setPixmap(QPixmap(path));
    }
    //用户2
    QList<Card> cards2 = Generator::instance()->get2Cards();
    assert(cards2.size()==2);
    m_sTableInfo.user[1].perflop1 = cards2[0];
    m_sTableInfo.user[1].perflop2 = cards2[1];
    m_sTableInfo.actionList.append(qMakePair(1,qMakePair(Perflop,-1)));

    ///下盲注 TODO 开发初期使用默认值
    m_sTableInfo.eBetFlow = Bet;
    //用户1 需要手动操作
    ui->txtUser1Bet->setEnabled(true);
    ui->btnUser1Call->setEnabled(true);
    ui->btnUser1Fold->setEnabled(true);
    ui->btnUser1Raise->setEnabled(true);
    //如果是新局 就是小盲注
    if(m_bNewGame){
        ui->txtUser1Bet->setText(QString::number(m_sTableInfo.bb/2));//小盲注
    }
    // 等待用户操作

    updateTableInfo();
}

void TexasWidget::on_btnUser1Call_clicked()
{
    //计算跟注需要的筹码 上家押注-自己押注
    uint chips = m_sTableInfo.user[0].bet - m_sTableInfo.user[1].bet;
    m_sTableInfo.bet += chips;
    m_sTableInfo.user[0].bet += chips;
    m_sTableInfo.user[0].chip -= chips;
    m_sTableInfo.actionList.append(qMakePair(1,qMakePair(Call,chips)));

    //用户2
    m_sTableInfo.user[1].bet+=m_sTableInfo.bb;//用户3下大盲注
    m_sTableInfo.user[1].chip -=m_sTableInfo.bb;//下注后筹码减少
    m_sTableInfo.bet += m_sTableInfo.bb;
    m_sTableInfo.actionList.append(qMakePair(2,qMakePair(Bet,m_sTableInfo.bb)));

    updateTableInfo();
}

void TexasWidget::on_btnUser1Raise_clicked()
{
    //加注数值要有效
    uint raiseValue = ui->txtUser1Bet->text().toUInt();
    if(raiseValue <=0){
        QMessageBox::warning(this,tr("警告"),tr("请输入有效数字"));
        return;
    }
    //加注需要大于玩家1的下注
    uint chips = m_sTableInfo.user[0].bet - m_sTableInfo.user[1].bet;
    if(raiseValue <= chips){
        QMessageBox::warning(this,tr("警告"),tr("加注至少要比玩家1下注多"));
        return;
    }

    //玩家2
    m_sTableInfo.bet += raiseValue;
    m_sTableInfo.user[1].bet += raiseValue;
    m_sTableInfo.user[1].chip -= raiseValue;
    m_sTableInfo.actionList.append(qMakePair(1,qMakePair(Raise,raiseValue)));

    updateTableInfo();
}

void TexasWidget::on_btnUser1Fold_clicked()
{

}

void TexasWidget::on_btnUser1Bet_clicked()
{
    uint unBetValue = ui->txtUser1Bet->text().toUInt();
    if(unBetValue==0){
        QMessageBox::warning(this,tr("警告"),tr("请输入需要下注的数"));
        return;
    }
    if(m_bNewGame){
        m_sTableInfo.user[0].bet+=unBetValue;//用户1下小盲注
        m_sTableInfo.user[0].chip -=unBetValue;//下注后筹码减少
        m_sTableInfo.bet += unBetValue;
        m_sTableInfo.actionList.append(qMakePair(0,qMakePair(SmallBlind,unBetValue)));
    }else{

    }

    //用户2 下大盲注
    if(m_sTableInfo.bb > unBetValue){
        //如果大盲注大于玩家1的下注，玩家2至少要持平
        m_sTableInfo.user[1].bet+=unBetValue;//用户2下大盲注
        m_sTableInfo.user[1].chip -=unBetValue;//下注后筹码减少
        m_sTableInfo.bet += 2;
        m_sTableInfo.actionList.append(qMakePair(1,qMakePair(Bet,unBetValue)));
    }else if(m_sTableInfo.bb == unBetValue){
        //这里进行概率计算
    }else{
        //如果大盲注小于玩家1下注
        m_sTableInfo.user[1].bet+=unBetValue;//用户2下大盲注
        m_sTableInfo.user[1].chip -=unBetValue;//下注后筹码减少
        m_sTableInfo.bet += unBetValue;
        m_sTableInfo.actionList.append(qMakePair(1,qMakePair(Bet,unBetValue)));
    }
}

