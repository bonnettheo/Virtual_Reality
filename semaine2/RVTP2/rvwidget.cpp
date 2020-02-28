/*!
  \file rvwidget.cpp
  \brief Définition de la classe RVWidget.
  \author  Leo Donati
  \date    2019-2020
  \version 2.3 (tutoriel n°2)

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia
*/
#include "rvcube.h"
#include "rvplane.h"
#include "rvwidget.h"

RVWidget::RVWidget(QWidget *parent)
    : QOpenGLWidget(parent), QOpenGLFunctions()
{
    m_angularVelocityX = 0;
    m_angularVelocityY = 3;
    m_angularVelocityZ = 0;
    m_timer = new QTimer(this);
    m_animation = false;
}

RVWidget::~RVWidget()
{
    delete m_timer;
    delete m_camera;
    delete m_body;
    delete m_body2;
}

void RVWidget::initializeGL()
{
    initializeOpenGLFunctions();


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.0f, 0.566f, 0.867f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    //glDisable(GL_CULL_FACE);

    m_camera = new RVCamera();
    m_camera->setPosition(QVector3D(0,10,20));
    m_camera->setTarget(QVector3D(0,0,0));
    m_camera->setZMin(10);


    m_body = new RVCube();
    m_body->setCamera(m_camera);
    // m_body->setPosition(QVector3D(0, 0, 0));
    // m_body->initialize();


    m_body2 = new RVPlane(30, 30);
    m_body2->setPosition(QVector3D(0, 0, 0));
    m_body2->setGlobalColor(QVector3D(0, 1, 0));
    m_body2->setCamera(m_camera);
    m_body2->initialize();

    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer->start(10);
}

void RVWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(int i = 0; i < 10; ++i) {
        for(int j = 0; j < 10; ++j) {
            m_body->setPosition(QVector3D((i - 5) * 2, 0, (j - 5)*2));
            m_body->initialize();
            m_body->draw();
        }
    }
    m_body->draw();
    m_body2->draw();
}

void RVWidget::resizeGL(int w, int h)
{
    //Pour tenir compte du changement de format du widget
    float aspect = float(w)/h;
    m_camera->setAspect(aspect);
    //transformation de viewport
    glViewport(0, 0, w, h);
}

void RVWidget::update()
{
    if (m_animation) {
        float angularVelocity = 3.0f;
        m_body->rotate(angularVelocity, QVector3D(0, 1, 0));
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

void RVWidget::changeOpacity(int opacity)
{
    m_body2->setOpacity((float)opacity / 100.0f);
}

void RVWidget::changeWireframe(bool wireframe)
{
    m_body->setWireframe(wireframe);
}

void RVWidget::changeCulling(bool culling)
{
    m_body->setCulling(culling);
}

void RVWidget::changeScale(int scale)
{
    m_body->setScale((float)scale / 100.0);
}

void RVWidget::changeSaturation(int saturation)
{
    float color = (float) (255.0 - saturation) / 255.0;
    m_body->setGlobalColor(QVector3D(color, color, color));
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
    m_body->rotate(angleX, QVector3D(1, 0, 0));
    m_body->rotate(angleY, QVector3D(0, 1, 0));
    m_oldPos = event->pos();

    QOpenGLWidget::update();
}

