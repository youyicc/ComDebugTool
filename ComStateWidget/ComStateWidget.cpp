#include "ComStateWidget.h"

ComStateWidget::ComStateWidget(QWidget *parent)
    : QGroupBox(parent)
{
    //设置提示语
    setTitle(QStringLiteral("通讯状态"));

    try{
        //初始化控件变量
        QLabel* labState=new QLabel();
        QLabel* labSend=new QLabel();
        QLabel* labRecv=new QLabel();
        editState=new QLineEdit();
        editSend=new QLineEdit();
        editRecv=new QLineEdit();
        SelfButtonWidget* btnClean=new SelfButtonWidget();

        //设置标签文字
        labState->setText(QStringLiteral("串口状态："));
        labSend->setText(QStringLiteral("发送字节："));
        labRecv->setText(QStringLiteral("接收字节："));
        editState->setText(QStringLiteral("关闭"));
        editSend->setText(QStringLiteral("0"));
        editRecv->setText(QStringLiteral("0"));
        btnClean->setText(QStringLiteral("清除计数"));

        //编辑框文字居中
        editState->setAlignment(Qt::AlignCenter);
        editSend->setAlignment(Qt::AlignCenter);
        editRecv->setAlignment(Qt::AlignCenter);

        //禁用控件
        editState->setEnabled(false);
        editSend->setEnabled(false);
        editRecv->setEnabled(false);

        //设置布局
        QGridLayout* bodyLayout=new QGridLayout();
        bodyLayout->setMargin(0);
        bodyLayout->setSpacing(10);
        bodyLayout->addWidget(labState,0,0);
        bodyLayout->addWidget(editState,0,1);
        bodyLayout->addWidget(labSend,1,0);
        bodyLayout->addWidget(editSend,1,1);
        bodyLayout->addWidget(labRecv,2,0);
        bodyLayout->addWidget(editRecv,2,1);

        QVBoxLayout* mainLayout=new QVBoxLayout();
        mainLayout->setSpacing(10);
        mainLayout->addLayout(bodyLayout);
        mainLayout->addWidget(btnClean);

        setLayout(mainLayout);

        //添加信号与槽
        connect(btnClean,&SelfButtonWidget::clicked,this,&ComStateWidget::SlotBtnClean);
    }
    catch(...){}
}

ComStateWidget::~ComStateWidget(){}

void ComStateWidget::SlotBtnClean()
{
    editSend->setText(QStringLiteral("0"));
    editRecv->setText(QStringLiteral("0"));
}

void ComStateWidget::SetCurrComState(qint32 state)
{
    if(state==1){
        editState->setText(QStringLiteral("打开"));
    }
    else{
        editState->setText(QStringLiteral("关闭"));
    }
}

void ComStateWidget::AddRecvLength(qint32 length)
{
    editRecv->setText(QString("%1").arg(editRecv->text().toInt()+length));
}

void ComStateWidget::AddSendLength(qint32 length)
{
    editSend->setText(QString("%1").arg(editSend->text().toInt()+length));
}
