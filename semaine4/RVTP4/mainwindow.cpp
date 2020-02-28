#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::changeAmbientLight()
{
    RVLight* lumiere = ui->widgetRV->light();
    QColor col = QColorDialog::getColor(lumiere->ambient(), this);
    if (col.isValid()) {
        QString qss = QString("background-color: %1;\n border: 1px solid black;\n border-radius: 5px;").arg(col.name());
        ui->ambientButton->setStyleSheet(qss);
        lumiere->setAmbient(col);
    }
}


void MainWindow::changeDiffuseLight()
{
    RVLight* lumiere = ui->widgetRV->light();
    QColor col = QColorDialog::getColor(lumiere->diffuse(), this);
    if (col.isValid()) {
        QString qss = QString("background-color: %1;\n border: 1px solid black;\n border-radius: 5px;").arg(col.name());
        ui->diffuseButton->setStyleSheet(qss);
        lumiere->setDiffuse(col);
    }
}


void MainWindow::changeSpecularLight()
{
    RVLight* lumiere = ui->widgetRV->light();
    QColor col = QColorDialog::getColor(lumiere->specular(), this);
    if (col.isValid()) {
        QString qss = QString("background-color: %1;\n border: 1px solid black;\n border-radius: 5px;").arg(col.name());
        ui->specularButton->setStyleSheet(qss);
        lumiere->setSpecular(col);
    }
}
