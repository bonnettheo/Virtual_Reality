#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::createCube()
{
    ui->widgetRV->makeCurrent();
    RVTexCube *m_cube = new RVTexCube();
    m_cube->setPosition(QVector3D(ui->x_value->value(), ui->y_value->value(), ui->z_value->value()));
    m_cube->setOrientation(ui->roulis->value(), ui->tangage->value(), ui->lacet->value());
    ui->widgetRV->addBody(m_cube);
}
