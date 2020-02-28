/*!
  \file rvwidget.cpp
  \brief Définition de la classe RVWidget.
  \author  Leo Donati
  \date    2019-2020
  \version 3.0 (tutoriel n°3)

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia
*/
#include "rvwidget.h"

#include <QPainter>

RVWidget::RVWidget(QWidget *parent)
    : QOpenGLWidget(parent), QOpenGLFunctions()
{
    m_angularVelocityX = 0;
    m_angularVelocityY = 3;
    m_angularVelocityZ = 0;
    m_timer = new QTimer(this);
    m_animation = false;

    grabKeyboard();
    m_time = QTime();
    m_time.start();
}

RVWidget::~RVWidget()
{
    makeCurrent();
    delete m_camera;
    delete m_batiment;
    delete m_sphere;
    delete m_torus;
    delete m_timer;
}

void RVWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.0f, 0.566f, 0.867f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    float scale = float(this->width())/this->height();

    m_camera = new RVSphericalCamera();
    m_camera->setAspect(scale);
    m_camera->setIsOrthogonal(false);
    m_camera->setTarget(QVector3D(0, 50, -100));
    m_camera->setZMin(2);
    m_camera->setZMax(500);
    static_cast<RVSphericalCamera*>(m_camera)->setRho(70);

    m_light = new RVLight();
    m_light->setAmbient(QColor(80, 80, 80));
    m_light->setPosition(QVector3D(0, 150, -100));

    m_batiment = new RVModel("/home/bonnet/Documents/cours-si5/RV/semaine7/debut/model/IUT_INFO.X");
    m_batiment->setCamera(m_camera);
    m_batiment->setLight(m_light);
    m_batiment->initialize();

    m_sphere = new RVSphere(5.0);
    m_sphere->setCamera(m_camera);
    m_sphere->setPosition(QVector3D(0, 50, -100));
    m_sphere->setTexture(":/textures/wood.png");
    m_sphere->setLight(m_light);
    m_sphere->initialize();

    m_torus = new RVTorus(1.0, 10.0);
    m_torus->setCamera(m_camera);
    m_torus->setPosition(QVector3D(200, 50, -100));
    m_torus->setFS(":/shaders/FS_lit_damier.fsh");
    m_torus->setLight(m_light);
    m_torus->initialize();

    m_scene.append(m_batiment);
    m_scene.append(m_sphere);
    m_scene.append(m_torus);
    m_scene.setCamera(m_camera);

    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer->start(10);
}

void RVWidget::paintGL()
{
    QPainter *p = new QPainter(this);
    p->beginNativePainting()
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_camera->setCameraType(RV_CAMERA_MONO);

    m_scene.draw();
    p->endNativePainting()
}

void RVWidget::resizeGL(int w, int h)
{
    float aspect = float(w)/h;
    m_camera->setAspect(aspect);

    //transformation de viewport
    glViewport(0, 0, w, h);
}

void RVWidget::update()
{
    int t = m_time.elapsed();
    //qDebug("temps qui passe = %d ms", t);

    if (m_animation) {
        m_scene.update(float(t));
    }

    QOpenGLWidget::update();
}

void RVWidget::startAnimation()
{
    m_animation = ! m_animation;
    this->update();
}

void RVWidget::changeFov(int newFov)
{
    m_camera->setFov(newFov);
    this->update();
}

void RVWidget::changeOpacity(int newOpacity)
{
    //m_body->setOpacity(newOpacity * 0.01f);
    m_sphere->setOpacity(newOpacity * 0.01f);
}

void RVWidget::changeWireFrame(bool b)
{
    m_sphere->setWireFrame(b);
}

void RVWidget::changeCulling(bool b)
{
    m_batiment->setCulling(b);
}

void RVWidget::changeScale(int s)
{
    m_sphere->setScale(s*0.01f);
}

void RVWidget::changeSaturation(int s)
{
    m_batiment->setGlobalColor(QColor(s, s, s));
}

void RVWidget::changeCameraType(bool b)
{
    m_camera->setIsOrthogonal(!b);
}

void RVWidget::mousePressEvent(QMouseEvent *event)
{
    m_oldPos = event->pos();
}

void RVWidget::mouseMoveEvent(QMouseEvent *event)
{
    float dx = float(event->x() - m_oldPos.x()) / width();
    float dy = float(event->y() - m_oldPos.y()) / height();
    float angleX = 180 * dy;
    float angleY = 180 * dx;
    //m_body->rotate(angleX, QVector3D(1, 0, 0));
    //m_body->rotate(angleY, QVector3D(0, 1, 0));
    float oldPhi = static_cast<RVSphericalCamera*>(m_camera)->phi();
    float oldTheta = static_cast<RVSphericalCamera*>(m_camera)->theta();

    static_cast<RVSphericalCamera*>(m_camera)->setPhi(oldPhi+qDegreesToRadians(angleX));
    static_cast<RVSphericalCamera*>(m_camera)->setTheta(oldTheta+qDegreesToRadians(angleY));

    m_oldPos = event->pos();

    update();
    //QOpenGLWidget::update();
}

void RVWidget::keyPressEvent(QKeyEvent *event)
{
    QVector3D camPos = m_camera->position();
    float deltaX = 0.2f;
    float deltaY = 0.2f;
    switch (event->key())
    {
    case Qt::Key_Left:
        camPos.setX(camPos.x() - deltaX);
        break;
    case Qt::Key_Right:
        camPos.setX(camPos.x() + deltaX);
        break;
    case Qt::Key_Up:
        camPos.setY(camPos.y() + deltaY);
        break;
    case Qt::Key_Down:
        camPos.setY(camPos.y() - deltaY);
        break;
    }
    m_camera->setPosition(camPos);
}

