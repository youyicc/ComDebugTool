#include "ComSendWidget.h"

ComSendWidget::ComSendWidget(QWidget *parent)
    : QGroupBox(parent)
{
    //设置提示语
    setTitle(QStringLiteral("发送数据"));

    try{
        timerId=0;
        //初始化控件变量
        autoSend=new QCheckBox();
        sendCycle=new QLineEdit();
        sendData=new QTextEdit();
        hexSend=new QCheckBox();
        QLabel* labCycle=new QLabel();
        QLabel* labTime=new QLabel();
        btnSend=new SelfButtonWidget();
        SelfButtonWidget* btnClean=new SelfButtonWidget();

        //设置控件变量文字
        autoSend->setText(QStringLiteral("自动发送"));
        labCycle->setText(QStringLiteral("发送周期"));
        sendCycle->setText(QStringLiteral("1000"));
        labTime->setText(QStringLiteral("毫秒"));
        hexSend->setText(QStringLiteral("十六进制发送"));
        btnClean->setText(QStringLiteral("清空显示"));
        btnSend->setText(QStringLiteral("手工发送"));

        //设置按钮的宽度
        btnSend->setFixedWidth(100);

        //设置编辑框
        sendCycle->setFixedWidth(50);
        sendCycle->setEnabled(false);
        sendCycle->setAlignment(Qt::AlignCenter);

        //设置复选框选中
        hexSend->setCheckState(Qt::Checked);

        //初始化设置布局
        QHBoxLayout* topLayout=new QHBoxLayout();
        topLayout->setMargin(0);
        topLayout->setSpacing(10);
        topLayout->addStretch(1);
        topLayout->addWidget(autoSend);
        topLayout->addWidget(labCycle);
        topLayout->addWidget(sendCycle);
        topLayout->addWidget(labTime);
        topLayout->addSpacing(2);

        QHBoxLayout* bottomLayout=new QHBoxLayout();
        bottomLayout->setMargin(0);
        bottomLayout->setSpacing(10);
        bottomLayout->addStretch(1);
        bottomLayout->addWidget(hexSend);
        bottomLayout->addWidget(btnClean);
        bottomLayout->addWidget(btnSend);

        QVBoxLayout* mainLayout=new QVBoxLayout();
        mainLayout->setMargin(10);
        mainLayout->setSpacing(10);
        mainLayout->addLayout(topLayout);
        mainLayout->addWidget(sendData);
        mainLayout->addLayout(bottomLayout);

        setLayout(mainLayout);

        //添加信号于槽
        connect(btnClean,&SelfButtonWidget::clicked,this,&ComSendWidget::SlotBtnClean);
        connect(btnSend,&SelfButtonWidget::clicked,this,&ComSendWidget::SlotBtnSend);
        connect(autoSend,&QCheckBox::stateChanged,this,&ComSendWidget::SlotStateChanged);
    }
    catch(...){}
}

ComSendWidget::~ComSendWidget(){}

void ComSendWidget::timerEvent(QTimerEvent*)
{
    SendBuf();
}

void ComSendWidget::SlotBtnClean()
{
    sendData->setText("");
}

void ComSendWidget::SlotStateChanged(int state)
{
    if(state){
        sendCycle->setEnabled(true);
        btnSend->setText(QStringLiteral("开始自动发送"));
    }
    else{
        //关闭定时器
        killTimer(timerId);
        sendCycle->setEnabled(false);
        btnSend->setText(QStringLiteral("手工发送"));
    }
}

void ComSendWidget::SlotBtnSend()
{
    if(autoSend->checkState()){
        if(btnSend->text()==QStringLiteral("开始自动发送")){
            btnSend->setText(QStringLiteral("停止自动发送"));
            //开始定时器
            timerId=startTimer(sendCycle->text().toInt());
        }
        else{
            btnSend->setText(QStringLiteral("开始自动发送"));
            killTimer(timerId);
        }
    }
    else{
        SendBuf();
    }
}

void ComSendWidget::SendBuf()
{
    QString sendMsg=sendData->toPlainText();
    if(sendMsg.length()==0)
        return;
    //去掉空格
    sendMsg.replace(" ","");
    if(hexSend->checkState()){
        emit Send(sendMsg.toUtf8());
    }
    else{
         emit Send(sendMsg.toUtf8().toHex());
    }
}
