#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle(QObject::tr("Logger"));
    w.setWindowIcon(QIcon(":/resources/images/poker.svg"));
    w.show();
    return a.exec();
}
