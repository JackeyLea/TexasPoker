#include "texaswidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TexasWidget w;
    w.show();
    return a.exec();
}
