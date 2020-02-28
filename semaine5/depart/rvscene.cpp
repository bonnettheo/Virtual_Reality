#include "rvscene.h"

RVScene::RVScene()
    :QList<RVBody *>()
{
    m_camera = nullptr;
}

RVScene::~RVScene()
{
    this->clear();
}

void RVScene::setCamera(RVCamera *camera)
{
    m_camera = camera;
    foreach (RVBody* body, *this) {
       body->setCamera(camera);
    }
}

void RVScene::translate(QVector3D vec)
{
    foreach (RVBody* body, *this) {
       body->translate(vec);
    }
}

void RVScene::rotate(float angle, QVector3D axe)
{
    foreach (RVBody* body, *this) {
            body->rotate(angle, axe);
    }
}

void RVScene::draw()
{
    foreach (RVBody* body, *this) {
       body->draw();
    }
}

void RVScene::update(float time)
{
    foreach (RVBody* body, *this) {
       body->update(time);
    }
}

