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
    Cards resultCards;
    QList<Card> inputCards;
    for(int i=0;i<7;i++){
        inputCards.append(curCards[i]);
    }
    Poker::instance()->checkCards(inputCards,resultCards);
    qDebug()<<resultCards.status;
    ui->lineUser1Type->setText(Poker::instance()->getBrandType(resultCards.status));
}

