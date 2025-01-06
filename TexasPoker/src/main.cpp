#include "setupwidget.h"

#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SetupWidget w;
    w.show();
    return a.exec();
}
