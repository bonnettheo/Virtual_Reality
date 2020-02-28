#include "rvwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RVWidget w;
    w.setWindowTitle("Réalité virtuelle TP1");
    w.show();
    return a.exec();
}
