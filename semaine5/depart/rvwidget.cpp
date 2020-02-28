/*!
  \file rvwidget.cpp
  \brief Définition de la classe RVWidget.
  \author  Leo Donati
  \date    2019-2020
  \version 3.0 (tutoriel n°3)

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia
*/
#include "rvbounce.h"
#include "rvhelix.h"
#include "rvwidget.h"

#include <QTime>

RVWidget::RVWidget(QWidget *parent)
    : QOpenGLWidget(parent), QOpenGLFunctions()
{
    m_angularVelocityX = 0;
    m_angularVelocityY = 3;
    m_angularVelocityZ = 0;
    m_timer = new QTimer(this);
    m_time = new QTime();
    m_time->start();
    m_animation = false;

    grabKeyboard();
}

RVWidget::~RVWidget()
{
    makeCurrent();
    delete m_camera;
    delete m_body;
    delete m_plane;
    delete m_world;
    delete m_torus;
    delete m_skybox;
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
    m_camera->setTarget(QVector3D(0, 0, 0));
    m_camera->setZMin(2);
    m_camera->setZMax(500);
    static_cast<RVSphericalCamera*>(m_camera)->setRho(60);

    m_light = new RVLight();

    m_trajectory = new RVBounce();
    m_trajectory->setCamera(m_camera);
    m_trajectory->setPosition(QVector3D(0, 0, 0));
    m_trajectory->setScale(5);
    m_trajectory->initialize();

    m_body = new RVDice();
    m_body->setCamera(m_camera);
    m_body->setPosition(QVector3D());
    m_body->setScale(5);
    m_body->setTexture(":/textures/dice_texture.jpg", false);
    m_body->setLight(m_light);
    m_body->initialize();

    m_plane = new RVPlane();
    m_plane->setScale(3);
    m_plane->setPosition(QVector3D(0, 0, 0));
    m_plane->setCamera(m_camera);
    m_plane->setTexture(":/textures/wood.png");
    m_plane->setLight(m_light);
    m_plane->initialize();

    m_world = new RVSphere(1.0);
    m_world->setCamera(m_camera);
    m_world->setPosition(QVector3D(0, 6, -8));
    m_world->setTexture(":/textures/2k_earth_daymap.jpg");
    m_world->setLight(m_light);
    m_world->setTrajectory(m_trajectory);
    m_world->initialize();

    m_torus = new RVTorus(1.0, 10.0);
    m_torus->setCamera(m_camera);
    m_torus->setPosition(QVector3D(0, 10, 0));
    m_torus->setFS(":/shaders/FS_lit_damier.fsh");
    m_torus->setLight(m_light);
    m_torus->initialize();

    m_skybox = new RVSkyBox();
    m_skybox->setCamera(m_camera);
    m_skybox->setPosition(QVector3D());
    m_skybox->setCubeTexture(":/textures/skybox/left.jpg",
                             ":/textures/skybox/right.jpg",
                             ":/textures/skybox/front.jpg",
                             ":/textures/skybox/back.jpg",
                             ":/textures/skybox/top.jpg",
                             ":/textures/skybox/bottom.jpg");
    m_skybox->setScale(100.0);
    m_skybox->initialize();

    m_scene.append(m_body);
    m_scene.append(m_plane);
    m_scene.append(m_world);
    m_scene.append(m_torus);
    m_scene.append(m_trajectory);
    m_scene.setCamera(m_camera);

    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer->start(10);
}

void RVWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_skybox->setPosition(m_camera->position());
    m_skybox->draw();

    glColorMask(true, false, false, false);
    m_camera->setCameraType(RV_CAMERA_LEFT);

    m_scene.draw();

    glClear(GL_DEPTH_BUFFER_BIT) ;
    glColorMask(false, true, true, false);
    m_camera->setCameraType(RV_CAMERA_RIGHT);

    m_scene.draw();
    glColorMask(true, true, true, false);
}

void RVWidget::resizeGL(int w, int h)
{
    float aspect = float(w)/h;
    m_camera->setAspect(aspect);

    //transformation de viewport
    glViewport(0, 0, w, h);
}

/*void RVWidget::update()
{
    if (m_animation) {
        m_scene.rotate(m_angularVelocityY, QVector3D(0, 1, 0));
    }
    QOpenGLWidget::update();
}*/
void RVWidget::update()
{
   // int t = m_time->restart(); // relative
   int t = m_time->elapsed(); // absolute

    if (m_animation) {
       m_scene.update(float(t));
       m_world->setPosition(m_trajectory->pos(t*0.001));
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
    m_plane->setOpacity(newOpacity * 0.01f);
    m_world->setOpacity(newOpacity * 0.01f);
}

void RVWidget::changeWireFrame(bool b)
{
    m_world->setWireFrame(b);
}

void RVWidget::changeCulling(bool b)
{
    m_body->setCulling(b);
}

void RVWidget::changeScale(int s)
{
    m_world->setScale(s*0.01f);
}

void RVWidget::changeSaturation(int s)
{
    m_body->setGlobalColor(QColor(s, s, s));
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

    QOpenGLWidget::update();
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

