#include "ComSetWidget.h"

ComSetWidget::ComSetWidget(QWidget *parent)
    : QGroupBox(parent)
{
    //设置提示语
    setTitle(QStringLiteral("串口设置"));

    try{
        //初始化控件变量
        QLabel* labIndex=new QLabel();
        QLabel* labRate=new QLabel();
        QLabel* labData=new QLabel();
        QLabel* labParity=new QLabel();
        QLabel* labStop=new QLabel();
        comIndex=new QComboBox();
        comRate=new QComboBox();
        comData=new QComboBox();
        comParity=new QComboBox();
        comStop=new QComboBox();
        btnOpen=new SelfButtonWidget();

        //设置标签文字
        labIndex->setText(QStringLiteral("选串口："));
        labRate->setText(QStringLiteral("波特率："));
        labData->setText(QStringLiteral("数据位："));
        labParity->setText(QStringLiteral("校验位："));
        labStop->setText(QStringLiteral("停止位："));
        btnOpen->setText(QStringLiteral("打开串口"));

        //初始化可用串口
        foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()){
            QSerialPort serial;
            serial.setPort(info);
            if(serial.open(QIODevice::ReadWrite)){
                comIndex->addItem(info.portName());
                serial.close();
            }
        }

        //初始化波特率
        comRate->addItem(QStringLiteral("300"));
        comRate->addItem(QStringLiteral("600"));
        comRate->addItem(QStringLiteral("1200"));
        comRate->addItem(QStringLiteral("2400"));
        comRate->addItem(QStringLiteral("4800"));
        comRate->addItem(QStringLiteral("9600"));
        comRate->addItem(QStringLiteral("14400"));
        comRate->addItem(QStringLiteral("19200"));
        comRate->addItem(QStringLiteral("38400"));
        comRate->addItem(QStringLiteral("56000"));
        comRate->addItem(QStringLiteral("57600"));
        comRate->addItem(QStringLiteral("115200"));
        comRate->addItem(QStringLiteral("230400"));
        comRate->addItem(QStringLiteral("460800"));
        comRate->addItem(QStringLiteral("921600"));
        comRate->setCurrentText(QStringLiteral("9600"));

        //初始化数据位
        comData->addItem(QStringLiteral("5"));
        comData->addItem(QStringLiteral("6"));
        comData->addItem(QStringLiteral("7"));
        comData->addItem(QStringLiteral("8"));
        comData->setCurrentText(QStringLiteral("8"));

        //初始化校验位
        comParity->addItem(QStringLiteral("None"));
        comParity->addItem(QStringLiteral("Odd"));
        comParity->addItem(QStringLiteral("Even"));
        comParity->addItem(QStringLiteral("Space"));
        comParity->addItem(QStringLiteral("Mark"));
        comParity->setCurrentText(QStringLiteral("None"));

        //初始化停止位
        comStop->addItem(QStringLiteral("1"));
        comStop->addItem(QStringLiteral("2"));
        comStop->setCurrentText(QStringLiteral("1"));

        //设置布局
        QGridLayout* bodyLayout=new QGridLayout();
        bodyLayout->setMargin(0);
        bodyLayout->setSpacing(10);
        bodyLayout->addWidget(labIndex,0,0);
        bodyLayout->addWidget(comIndex,0,1);
        bodyLayout->addWidget(labRate,1,0);
        bodyLayout->addWidget(comRate,1,1);
        bodyLayout->addWidget(labData,2,0);
        bodyLayout->addWidget(comData,2,1);
        bodyLayout->addWidget(labParity,3,0);
        bodyLayout->addWidget(comParity,3,1);
        bodyLayout->addWidget(labStop,4,0);
        bodyLayout->addWidget(comStop,4,1);

        QVBoxLayout* mainLayout=new QVBoxLayout();
        mainLayout->setSpacing(10);
        mainLayout->addLayout(bodyLayout);
        mainLayout->addWidget(btnOpen);

        setLayout(mainLayout);

        //添加信号与槽
        connect(btnOpen,&SelfButtonWidget::clicked,this,&ComSetWidget::SlotBtnOpen);
    }
    catch(...){}
}

ComSetWidget::~ComSetWidget(){}

void ComSetWidget::SlotBtnOpen()
{
    SerialPort serialPort={0};
    serialPort.portName=comIndex->currentText();
    serialPort.baudRate=comRate->currentText().toInt();
    switch(comData->currentText().toInt()){
    case 5:
        serialPort.dataBits=QSerialPort::Data5;
        break;
    case 6:
        serialPort.dataBits=QSerialPort::Data6;
        break;
    case 7:
        serialPort.dataBits=QSerialPort::Data7;
        break;
    case 8:
        serialPort.dataBits=QSerialPort::Data8;
        break;
    default:
        serialPort.dataBits=QSerialPort::UnknownDataBits;
        break;
    }
    QString parityStr=comParity->currentText();
    if(parityStr==QStringLiteral("None")){
        serialPort.parity=QSerialPort::NoParity;
    }
    else if(parityStr==QStringLiteral("Odd")){
        serialPort.parity=QSerialPort::OddParity;
    }
    else if(parityStr==QStringLiteral("Even")){
        serialPort.parity=QSerialPort::EvenParity;
    }
    else if(parityStr==QStringLiteral("Space")){
        serialPort.parity=QSerialPort::SpaceParity;
    }
    else if(parityStr==QStringLiteral("Mark")){
        serialPort.parity=QSerialPort::MarkParity;
    }
    else{
        serialPort.parity=QSerialPort::UnknownParity;
    }
    switch(comStop->currentText().toInt()){
    case 1:
        serialPort.stopBits=QSerialPort::OneStop;
        break;
    case 2:
        serialPort.stopBits=QSerialPort::TwoStop;
        break;
    default:
        serialPort.stopBits=QSerialPort::UnknownStopBits;
    }
    serialPort.flowCtrl=QSerialPort::NoFlowControl;

    if(btnOpen->text()==QStringLiteral("打开串口")){
        btnOpen->setText(QStringLiteral("关闭串口"));
    }
    else{
        btnOpen->setText(QStringLiteral("打开串口"));
    }
    //发送信号
    emit ComConnect(serialPort);
}
