/*!
  \file main.cpp
  \brief Tutoriel n°8
  \author  Leo Donati
  \date    2019-2020
  \version 8.0

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia

  Tuto 8
*/
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowTitle("Réalité Virtuelle: Tuto 8");
    w.show();
    return a.exec();
}
