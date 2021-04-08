#ifndef COMDEBUGTOOL_H
#define COMDEBUGTOOL_H

#include "ComSetWidget/ComSetWidget.h"
#include "ComSendWidget/ComSendWidget.h"
#include "ComStateWidget/ComStateWidget.h"
#include "ComRecvWidget/ComRecvWidget.h"

class ComDebugTool : public QWidget
{
    Q_OBJECT

private:
     QSerialPort* comSerial;

private:
    ComSetWidget* comSetWidget;
    ComSendWidget* comSendWidget;
    ComStateWidget* comStateWidget;
    ComRecvWidget* comRecvWidget;

public:
    ComDebugTool(QWidget *parent = nullptr);
    ~ComDebugTool();

public slots:
    void SlotReadData();
    void SlotSend(QByteArray);
    void SlotComConnect(SerialPort&);
};
#endif
