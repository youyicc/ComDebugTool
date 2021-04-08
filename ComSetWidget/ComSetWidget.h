#ifndef COMSETWIDGET_H
#define COMSETWIDGET_H

#include "Common/Common.h"
#include "Common/SelfControl.h"

struct SerialPort
{
    QString portName;
    qint32 baudRate;
    QSerialPort::DataBits dataBits;
    QSerialPort::Parity parity;
    QSerialPort::StopBits stopBits;
    QSerialPort::FlowControl flowCtrl;
};

class ComSetWidget : public QGroupBox
{
    Q_OBJECT

private:
    QComboBox* comIndex;
    QComboBox* comRate;
    QComboBox* comData;
    QComboBox* comParity;
    QComboBox* comStop;
    SelfButtonWidget* btnOpen;

public:
    ComSetWidget(QWidget *parent = nullptr);
    ~ComSetWidget();

signals:
    void ComConnect(SerialPort&);

public slots:
    void SlotBtnOpen();
};
#endif
