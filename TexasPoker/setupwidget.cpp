#include "setupwidget.h"
#include "ui_setupwidget.h"

SetupWidget::SetupWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SetupWidget)
    , m_pTexasWidget(NULL)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/resources/images/poker.svg"));
}

SetupWidget::~SetupWidget()
{
    delete ui;
}

void SetupWidget::on_btnJoin_clicked()
{
    //人数默认不用管
    //盲注大小
    uint blind = ui->txtBB->text().toUInt();
    blind = (blind==0 ? 4 : blind);
    //加注次数
    bool isNoLimit = ui->comboBoxRaiseType->currentIndex();

    if(m_pTexasWidget){
        delete m_pTexasWidget;
    }
    qDebug()<<QString("大盲注%1 是否为无限加注%2").arg(blind).arg(isNoLimit);
    m_pTexasWidget = new TexasWidget(blind,isNoLimit);
    m_pTexasWidget->show();
    this->close();
}

void SetupWidget::on_btnCance_clicked()
{
    this->close();
}
