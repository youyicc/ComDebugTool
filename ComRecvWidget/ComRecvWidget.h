#ifndef COMRECVWIDGET_H
#define COMRECVWIDGET_H

#include "Common/Common.h"
#include "Common/SelfControl.h"

class ComRecvWidget : public QGroupBox
{
    Q_OBJECT

private:
    QTextEdit* editRecv;
    QCheckBox* hexRecv;

public:
    ComRecvWidget(QWidget *parent = nullptr);
    ~ComRecvWidget();

public:
    void AppendShowMsg(QByteArray&);

public slots:
    void SlotBtnClean();
};
#endif
