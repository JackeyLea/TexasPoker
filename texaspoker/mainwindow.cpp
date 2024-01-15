#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QRandomGenerator>
#include <QDebug>

#include "poker.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    label[0]= ui->labelShow1;
    label[1]= ui->labelShow2;
    label[2]= ui->labelHide1;
    label[3]= ui->labelHide2;
    label[4]= ui->labelHide3;
    label[5]= ui->labelUser11;
    label[6]= ui->labelUser12;
    label[7]= ui->labelUser21;
    label[8]= ui->labelUser22;

    for(int i=0;i<9;i++){
        label[i]->setPixmap(QPixmap(":/resources/images/back.png"));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnPlay_clicked()
{
    Poker::instance()->clearExistCard();
    curCards.clear();

    for(int i=0;i<9;i++){
        Card c = Poker::instance()->getCard();
        curCards.append(c);
        QString path = QString(":/resources/images/%1%2.png").arg(c.CardDecor).arg(c.CardNum);
        label[i]->setPixmap(QPixmap(path));
    }
}


void MainWindow::on_compare_clicked()
{
    //用户1
    Cards user1OutputCards;
    QList<Card> user1Cards;
    for(int i=0;i<7;i++){
        user1Cards.append(curCards[i]);
    }
    Poker::instance()->checkCards(user1Cards,user1OutputCards);
    qDebug()<<user1OutputCards.status;
    ui->lineUser1Type->setText(Poker::instance()->getBrandType(user1OutputCards.status));

    //用户2
    Cards user2OutputCards;
    QList<Card> user2Cards;
    //公共牌
    for(int i=0;i<5;i++){
        user2Cards.append(curCards[i]);
    }
    user2Cards.append(curCards[7]);
    user2Cards.append(curCards[8]);
    Poker::instance()->checkCards(user2Cards,user2OutputCards);
    qDebug()<<user2OutputCards.status;
    ui->lineUser2Type->setText(Poker::instance()->getBrandType(user2OutputCards.status));

    //结果
    char r = isWin(user1OutputCards,user2OutputCards);
    if(r==1){
        ui->lineResult->setText("用户2胜");
    }else if(r==0){
        ui->lineResult->setText("用户1胜");
    }else if(r==-1){
        ui->lineResult->setText("状态异常");
    }
}

