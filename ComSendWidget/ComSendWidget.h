#ifndef COMSENDWIDGET_H
#define COMSENDWIDGET_H

#include "Common/Common.h"
#include "Common/SelfControl.h"

class ComSendWidget : public QGroupBox
{
    Q_OBJECT

private:
    qint32 timerId;

private:
    QCheckBox* autoSend;
    QLineEdit* sendCycle;
    QTextEdit* sendData;
    QCheckBox* hexSend;
    SelfButtonWidget* btnSend;

public:
    ComSendWidget(QWidget *parent = nullptr);
    ~ComSendWidget();

protected:
    void timerEvent(QTimerEvent*);

signals:
    void Send(QByteArray);

public:
    void SendBuf();

public slots:
    void SlotBtnClean();
    void SlotBtnSend();
    void SlotStateChanged(int);
};
#endif
