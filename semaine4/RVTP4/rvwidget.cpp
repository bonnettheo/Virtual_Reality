/*!
  \file rvwidget.cpp
  \brief Définition de la classe RVWidget.
  \author  Leo Donati
  \date    2019-2020
  \version 3.0 (tutoriel n°3)

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia
*/
#include "rvlightbulb.h"
#include "rvspeccube.h"
#include "rvspectorus.h"
#include "rvwidget.h"

RVWidget::RVWidget(QWidget *parent)
    : QOpenGLWidget(parent), QOpenGLFunctions()
{
    m_angularVelocityX = 0;
    m_angularVelocityY = 3;
    m_angularVelocityZ = 0;
    m_timer = new QTimer(this);
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

    m_light = new RVLight();

    m_camera = new RVSphericalCamera();
    m_camera->setAspect(scale);
    m_camera->setIsOrthogonal(false);
    //m_camera->setPosition(QVector3D(10, 10, 10));
    m_camera->setTarget(QVector3D(0, 0, 0));
    m_camera->setZMin(2);
    m_camera->setZMax(500);
    static_cast<RVSphericalCamera*>(m_camera)->setRho(20);

    m_body = new RVSpecCube();
    m_body->setCamera(m_camera);
    m_body->setPosition(QVector3D(0, 0, 0));
    m_body->setScale(5);
    m_body->setGlobalColor(QColor(200, 200, 200));
    // m_body->setTexture(":/textures/dice_texture.jpg", false);

    dynamic_cast<RVSpecCube *>(m_body)->setCubeTex(":/textures/skybox/left.jpg",
                             ":/textures/skybox/right.jpg",
                             ":/textures/skybox/front.jpg",
                             ":/textures/skybox/back.jpg",
                             ":/textures/skybox/top.jpg",
                             ":/textures/skybox/bottom.jpg");
    m_body->setLight(m_light);
    m_body->initialize();

    m_dice = new RVDice();
    m_dice->setCamera(m_camera);
    m_dice->setPosition(QVector3D(10, 0, 0));
    m_dice->setScale(5);
    m_dice->setTexture(":/textures/dice_texture.jpg", false);
    m_dice->setLight(m_light);
    m_dice->initialize();

    m_cube = new RVCube();
    m_cube->setCamera(m_camera);
    m_cube->setPosition(QVector3D(QVector3D(-10, 0, 0)));
    m_cube->setScale(5);
    // m_body->setTexture(":/textures/dice_texture.jpg", false);
    m_cube->setLight(m_light);
    m_cube->initialize();

    m_plane = new RVPlane();
    m_plane->setScale(3);
    m_plane->setPosition(QVector3D(0, 0, 0)); //-10, -40));
    m_plane->setCamera(m_camera);
    m_plane->setTexture(":/textures/wood.png");
    m_plane->setLight(m_light);
    m_plane->initialize();

    m_world = new RVSphere(5.0);
    m_world->setCamera(m_camera);
    m_world->setPosition(QVector3D(0, 6, -80));
    m_world->setTexture(":/textures/2k_earth_daymap.jpg");
    //dynamic_cast<RVSphere*>(m_world)->setTexture(":/textures/2k_earth_nightmap.jpg");
    m_world->setLight(m_light);
    m_world->initialize();

    m_torus = new RVSpecTorus(1.0, 8.0);
    m_torus->setCamera(m_camera);
    m_torus->setPosition(QVector3D(0, 6, -10));
    // m_torus->setFS(":/shaders/FS_texture_damier.fsh");
    m_torus->setLight(m_light);
    dynamic_cast<RVSpecTorus *>(m_torus)->setTorusTex(":/textures/skybox/left.jpg",
                             ":/textures/skybox/right.jpg",
                             ":/textures/skybox/front.jpg",
                             ":/textures/skybox/back.jpg",
                             ":/textures/skybox/top.jpg",
                             ":/textures/skybox/bottom.jpg");
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
    m_scene.append(m_cube);
    m_scene.append(m_dice);
    m_scene.append(m_plane);
    m_scene.append(m_world);
    m_scene.append(m_torus);
    m_scene.setCamera(m_camera);

    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer->start(10);
}

void RVWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_skybox->setPosition(m_camera->position());
      m_skybox->draw();
//    m_body->draw();
//    m_plane->draw();
//    m_world->draw();
//    m_torus->draw();
      m_scene.draw();
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
    if (m_animation) {
//        m_body->rotate(m_angularVelocityY, QVector3D(0, 1, 0));
//        m_world->rotate(m_angularVelocityY, QVector3D(0, 1, 0));
        QVector3D p = m_light->position();
        QVector3D a(0.0, 0.0, 0.0);
        QMatrix4x4 m;

        m.translate(-a.x(), -a.y(), -a.z());
        p = m*p;

        m.setToIdentity();
        m.rotate(1, 0.0, 1.0, 0.0);
        p = m*p;

        m.setToIdentity();
        m.translate(a.x(), a.y(), a.z());
        p = m*p;

        m_light->setPosition(p);
        //m_scene.rotate(m_angularVelocityY, QVector3D(0, 1, 0));
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

void RVWidget::changeSpecCoeff(int newCoeff)
{
    m_scene.setSpecCoeff(float(20*(newCoeff))/50.0f);
}

void RVWidget::changeLightX(double x)
{
    QVector3D pos = QVector3D(m_light->position());
    pos.setX(x);
    m_light->setPosition(pos);
}

void RVWidget::changeLightY(double y)
{
    QVector3D pos = QVector3D(m_light->position());
    pos.setY(y);
    m_light->setPosition(pos);
}

void RVWidget::changeLightZ(double z)
{
    QVector3D pos = QVector3D(m_light->position());
    pos.setZ(z);
    m_light->setPosition(pos);
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

RVLight *RVWidget::light() const
{
    return m_light;
}

void RVWidget::setLight(RVLight *light)
{
    m_light = light;
}

