#include "texaswidget.h"
#include "ui_texaswidget.h"

#include "card.h"
#include "generator.h"

#include <QMessageBox>
#include <QtMath>

TexasWidget::TexasWidget(uint BB, bool isNoLimit, uint chips, uint compareType, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TexasWidget)
    , m_bNewGame(true)
    , m_unCompareType(compareType)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/resources/images/poker.svg"));

    //初始化变量
    m_sTableInfo.clear();
    m_sTableInfo.setBigBlind(BB);
    m_sTableInfo.setNoLimitRaise(isNoLimit);
    // 添加玩家1
    GamePlayer player1(0,0,chips);
    // 添加玩家到牌桌
    m_sTableInfo.addPlayer(player1);
    // 添加玩家2
    GamePlayer player2(1,1,chips);
    m_sTableInfo.addPlayer(player2);
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

QPair<int, int> TexasWidget::getNextAction()
{
    //当前是盲注状态 下注值为[1,4] * bb
    //2张底牌
    QList<Card> cards = m_sTableInfo.player(1).cards();
    Card c1=cards[0],c2 = cards[1];

    //同花
    if(c1.decor() == c2.decor()){
        //顺子
        if(qAbs(c1.num() - c2.num())==1){//可能是同花顺
            if(c1.num() == Card::Num_A || c2.num() == Card::Num_A){//可能是皇家同花顺
                return qMakePair(GameTable::BigBlind,m_sTableInfo.bigBlind());
            }
            return qMakePair(GameTable::BigBlind,m_sTableInfo.bigBlind());
        }
        //普通同花
        return qMakePair(GameTable::BigBlind,m_sTableInfo.bigBlind());
    }else if(qAbs(c1.num() -c2.num())==1){//顺子
        return qMakePair(GameTable::BigBlind,m_sTableInfo.bigBlind());
    }else if(qAbs(c1.num() - c2.num()) <5){//可能凑顺子
        return qMakePair(GameTable::BigBlind,m_sTableInfo.bigBlind());
    }else if((c1.num() - c2.num())==0){//可能是一对 两对 三条 四条 葫芦
        return qMakePair(GameTable::BigBlind,m_sTableInfo.bigBlind());
    }else{
        //暂时无法判断，保守治疗，大盲注只能是bb或者更大
        return qMakePair(GameTable::BigBlind,m_sTableInfo.bigBlind());
    }
}

void TexasWidget::updateTableInfo()
{
    //玩家1
    ui->labelUser1Chip->setText(QString::number(m_sTableInfo.player(0).chips()));
    //玩家2
    ui->labelUser2Chip->setText(QString::number(m_sTableInfo.player(1).chips()));
    //界面
    ui->txtBet->setText(QString::number(m_sTableInfo.totalChips()));
}

void TexasWidget::updateUserBetInfo(int userId, int action, int value)
{
    m_sTableInfo.addBet(userId,value);//用户下注
    m_sTableInfo.append(qMakePair(1,qMakePair(action,value)));
}

void TexasWidget::on_btnStart_clicked()
{
    ////游戏开始
    Generator::instance()->startNewGame();//发新牌
    m_sTableInfo.setGameStep(GameTable::NotStart);
    m_sTableInfo.setBetStep(GameTable::NoBet);
    ///发底牌
    m_sTableInfo.setGameStep(GameTable::Perflop);
    //用户1
    QList<Card> cards = Generator::instance()->get2Cards();
    assert(cards.size()==2);
    m_sTableInfo.player(0).setCards(cards);
    m_sTableInfo.append(qMakePair(0,qMakePair(GameTable::Perflop,-1)));
    //用户1是自己，需要显示牌
    for(int i=0;i<2;i++){
        Card c = cards[i];
        QString path = QString(":/resources/images/%1%2.svg").arg(c.decor()).arg(c.num());
        m_pLabelUser2[i]->setPixmap(QPixmap(path));
    }
    //用户2
    QList<Card> cards2 = Generator::instance()->get2Cards();
    assert(cards2.size()==2);
    m_sTableInfo.player(1).setCards(cards2);
    m_sTableInfo.append(qMakePair(1,qMakePair(GameTable::Perflop,-1)));

    ///下盲注 TODO 开发初期使用默认值
    m_sTableInfo.setBetStep(GameTable::Bet);
    //用户1 需要手动操作
    ui->txtUser1Bet->setEnabled(true);
    ui->btnUser1Bet->setEnabled(true);
    ui->btnUser1Fold->setEnabled(true);
    ui->btnUser1Raise->setEnabled(true);
    //如果是新局 就是小盲注
    if(m_bNewGame){
        ui->txtUser1Bet->setText(QString::number(m_sTableInfo.bigBlind()/2));//小盲注
    }
    // 等待用户操作

    updateTableInfo();
}

void TexasWidget::on_btnUser1Call_clicked()
{
    //计算跟注需要的筹码 上家押注-自己押注
    // uint chips = m_sTableInfo.user[0].bet - m_sTableInfo.user[1].bet;
    // m_sTableInfo.bet += chips;
    // m_sTableInfo.user[0].bet += chips;
    // m_sTableInfo.user[0].chip -= chips;
    // m_sTableInfo.actionList.append(qMakePair(1,qMakePair(Call,chips)));

    // //用户2
    // m_sTableInfo.user[1].bet+=m_sTableInfo.bb;//用户3下大盲注
    // m_sTableInfo.user[1].chip -=m_sTableInfo.bb;//下注后筹码减少
    // m_sTableInfo.bet += m_sTableInfo.bb;
    // m_sTableInfo.actionList.append(qMakePair(2,qMakePair(Bet,m_sTableInfo.bb)));

    // updateTableInfo();
}

void TexasWidget::on_btnUser1Raise_clicked()
{
    //加注数值要有效
    // uint raiseValue = ui->txtUser1Bet->text().toUInt();
    // if(raiseValue <=0){
    //     QMessageBox::warning(this,tr("警告"),tr("请输入有效数字"));
    //     return;
    // }
    // //加注需要大于玩家1的下注
    // uint chips = m_sTableInfo.user[0].bet - m_sTableInfo.user[1].bet;
    // if(raiseValue <= chips){
    //     QMessageBox::warning(this,tr("警告"),tr("加注至少要比玩家1下注多"));
    //     return;
    // }

    // //玩家2
    // m_sTableInfo.bet += raiseValue;
    // m_sTableInfo.user[1].bet += raiseValue;
    // m_sTableInfo.user[1].chip -= raiseValue;
    // m_sTableInfo.actionList.append(qMakePair(1,qMakePair(Raise,raiseValue)));

    // updateTableInfo();
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
        unBetValue = (unBetValue <= m_sTableInfo.smallBlind()) ? (m_sTableInfo.smallBlind()) : unBetValue;
        updateUserBetInfo(0,m_sTableInfo.smallBlind(),unBetValue);

        //用户2 下大盲注
        if(m_sTableInfo.bigBlind() > unBetValue){
            //如果大盲注大于玩家1的下注，玩家2至少要持平
            updateUserBetInfo(1,m_sTableInfo.bigBlind(),m_sTableInfo.bigBlind());
        }else if(m_sTableInfo.bigBlind() == unBetValue){
            //这里进行概率计算
            QPair<int,int> result = getNextAction();
            updateUserBetInfo(1,result.first,result.second);
            //如果下注大于
        }else{
            //如果大盲注小于玩家1下注，那就至少要持平
            updateUserBetInfo(1,m_sTableInfo.bigBlind(),unBetValue);
        }
        //从小盲注到大盲注，这里有一次加注
        //m_sTableInfo.raiseCnt++;
        //m_sTableInfo.raiseLoop=1;
        m_bNewGame=false;
    }else{

    }

    updateTableInfo();
}
