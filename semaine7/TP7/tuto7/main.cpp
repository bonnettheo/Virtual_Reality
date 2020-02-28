/*!
  \file main.cpp
  \brief Tutoriel n°7
  \author  Leo Donati
  \date    2019-2020
  \version 7.0

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia

  Tuto 7
*/
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowTitle("Réalité Virtuelle: Tuto 7");
    w.show();
    return a.exec();
}
