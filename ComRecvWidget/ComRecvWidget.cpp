#include "ComRecvWidget.h"

ComRecvWidget::ComRecvWidget(QWidget *parent)
    : QGroupBox(parent)
{
    //设置提示语
    setTitle(QStringLiteral("接收数据"));

    try{
        //初始化控件变量
        editRecv=new QTextEdit();
        hexRecv=new QCheckBox();
        SelfButtonWidget* btnClean=new SelfButtonWidget();

        //设置控件变量文字
        hexRecv->setText(QStringLiteral("十六进制显示"));
        btnClean->setText(QStringLiteral("清空显示"));

        //设置复选框选中
        hexRecv->setCheckState(Qt::Checked);

        //初始化设置布局
        QHBoxLayout* bottomLayout=new QHBoxLayout();
        bottomLayout->setMargin(0);
        bottomLayout->setSpacing(10);
        bottomLayout->addStretch(1);
        bottomLayout->addWidget(hexRecv);
        bottomLayout->addWidget(btnClean);

        QVBoxLayout* mainLayout=new QVBoxLayout();
        mainLayout->setMargin(10);
        mainLayout->setSpacing(10);
        mainLayout->addWidget(editRecv);
        mainLayout->addLayout(bottomLayout);

        setLayout(mainLayout);

        //添加信号与槽
        connect(btnClean,&SelfButtonWidget::clicked,this,&ComRecvWidget::SlotBtnClean);
    }
    catch(...){}
}

ComRecvWidget::~ComRecvWidget(){}

void ComRecvWidget::SlotBtnClean()
{
    editRecv->setText("");
}

void ComRecvWidget::AppendShowMsg(QByteArray& bufArray)
{
    QString tmpMsg="";
    if(hexRecv->checkState()){
        tmpMsg=bufArray.toHex().toUpper();
        int len = tmpMsg.length()/2;
        for(int i=1;i<len;++i){
            tmpMsg.insert(2*i+i-1," ");
        }
    }
    else{
        tmpMsg=bufArray;
    }
    if(editRecv->toPlainText().length()>10000){
        editRecv->setText(tmpMsg);
    }
    else{
        editRecv->setText(editRecv->toPlainText()+tmpMsg);
    }
}
