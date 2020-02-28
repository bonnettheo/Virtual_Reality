/*!
  \file main.cpp
  \brief Tutoriel n°2
  \author  Leo Donati
  \date    2019-2020
  \version 2.0

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia
*/
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Réalité Virtuelle: Tuto 4");
    w.show();
    return a.exec();
}
