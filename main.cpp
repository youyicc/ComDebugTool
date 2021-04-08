#include "MainWidget/ComDebugTool.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ComDebugTool mainWidget;
    mainWidget.show();
    return a.exec();
}
