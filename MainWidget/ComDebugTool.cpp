#include "ComDebugTool.h"

ComDebugTool::ComDebugTool(QWidget *parent)
    : QWidget(parent)
{
    //设置窗口最小值
    setMinimumSize(540,400);
    resize(540,400);

    //设置窗口标题
    setWindowTitle(QStringLiteral("串口通信调试助手"));

    try {
        comSerial=nullptr;
        //初始化界面变量
        comSetWidget=new ComSetWidget();
        comSendWidget=new ComSendWidget();
        comStateWidget=new ComStateWidget();
        comRecvWidget=new ComRecvWidget();

        //设置控件宽度
        comSetWidget->setFixedWidth(150);
        comStateWidget->setFixedWidth(150);

        //设置布局
        QHBoxLayout* topLayout=new QHBoxLayout();
        topLayout->setSpacing(10);
        topLayout->addWidget(comSetWidget);
        topLayout->addWidget(comSendWidget,1);

        QHBoxLayout* bottomLayout=new QHBoxLayout();
        bottomLayout->setSpacing(10);
        bottomLayout->addWidget(comStateWidget);
        bottomLayout->addWidget(comRecvWidget,1);

        QVBoxLayout* mainLayout=new QVBoxLayout();
        mainLayout->setSpacing(10);
        mainLayout->addLayout(topLayout,1);
        mainLayout->addLayout(bottomLayout,1);

        setLayout(mainLayout);

        //信号与槽
        connect(comSendWidget,&ComSendWidget::Send,this,&ComDebugTool::SlotSend);
        connect(comSetWidget,&ComSetWidget::ComConnect,this,&ComDebugTool::SlotComConnect);
    } catch (...) {}
}

ComDebugTool::~ComDebugTool(){}

void ComDebugTool::SlotComConnect(SerialPort& serialPort)
{
    if(comSerial==nullptr){
        comSerial=new QSerialPort();
        comSerial->setPortName(serialPort.portName);
        comSerial->open(QIODevice::ReadWrite);
        comSerial->setBaudRate(serialPort.baudRate);
        comSerial->setDataBits(serialPort.dataBits);
        comSerial->setParity(serialPort.parity);
        comSerial->setStopBits(serialPort.stopBits);
        comSerial->setFlowControl(serialPort.flowCtrl);
        //设置StateWidget中的状态
        comStateWidget->SetCurrComState(1);
        connect(comSerial,&QSerialPort::readyRead,this,&ComDebugTool::SlotReadData);
    }
    else{
        //设置StateWidget中的状态
        comStateWidget->SetCurrComState(0);
        disconnect(comSerial,&QSerialPort::readyRead,this,&ComDebugTool::SlotReadData);
        delete comSerial;
        comSerial=nullptr;
    }
}

void ComDebugTool::SlotReadData()
{
    if(comSerial==nullptr)
        return;
    QByteArray readBuf;
    readBuf=comSerial->readAll();
    //在RecvWidget界面显示数据
    comRecvWidget->AppendShowMsg(readBuf);
    //在StateWidget增加接收字节数
    comStateWidget->AddRecvLength(readBuf.length());
}

void ComDebugTool::SlotSend(QByteArray sendByte)
{
    if(comSerial==nullptr)
        return;
    //发送到串口
    comSerial->write(sendByte);
    //在StateWidget增加发送字节数
    comStateWidget->AddSendLength(sendByte.length());
}
