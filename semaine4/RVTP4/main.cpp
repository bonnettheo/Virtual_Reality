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
#include "qopenglskyboxwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    QOpenGLSkyboxWidget w(":/textures/skybox/front.jpg",
//                               ":/textures/skybox/back.jpg",
//                               ":/textures/skybox/top.jpg",
//                               ":/textures/skybox/bottom.jpg",
//                               ":/textures/skybox/left.jpg",
//                               ":/textures/skybox/right.jpg");

    MainWindow w;
    w.setWindowTitle("Réalité Virtuelle: TP 4");
    w.show();
    return a.exec();
}
