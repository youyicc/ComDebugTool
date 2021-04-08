#ifndef COMSTATEWIDGET_H
#define COMSTATEWIDGET_H

#include "Common/Common.h"
#include "Common/SelfControl.h"

class ComStateWidget : public QGroupBox
{
    Q_OBJECT

private:
    QLineEdit* editState;
    QLineEdit* editSend;
    QLineEdit* editRecv;

public:
    ComStateWidget(QWidget *parent = nullptr);
    ~ComStateWidget();

public:
    void SetCurrComState(qint32);
    void AddRecvLength(qint32);
    void AddSendLength(qint32);

public slots:
    void SlotBtnClean();
};
#endif
