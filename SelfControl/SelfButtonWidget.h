#ifndef SELFBUTTONWIDGET_H
#define SELFBUTTONWIDGET_H

#include "Common/Common.h"

class SelfButtonWidget : public QPushButton
{
    Q_OBJECT

protected:
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);

public:
    SelfButtonWidget(QWidget *parent = 0);
    ~SelfButtonWidget();
};

#endif
