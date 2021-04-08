#include "SelfControl/SelfButtonWidget.h"

SelfButtonWidget::SelfButtonWidget(QWidget *parent)
    : QPushButton(parent)
{}

SelfButtonWidget::~SelfButtonWidget(){}

void SelfButtonWidget::enterEvent(QEvent*)
{
    setCursor(QCursor(Qt::PointingHandCursor));
}

void SelfButtonWidget::leaveEvent(QEvent*)
{
    setCursor(QCursor(Qt::ArrowCursor));
}
