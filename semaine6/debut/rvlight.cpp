#include "rvlight.h"

RVLight::RVLight()
{
    m_position = QVector3D(10, 0, 10);
    m_ambient = QColor(100, 100, 100);
    m_diffuse = QColor(255, 255, 255);
    m_specular = QColor(255, 255, 255);
}

QVector3D RVLight::position() const
{
    return m_position;
}

void RVLight::setPosition(const QVector3D &position)
{
    m_position = position;
}

QColor RVLight::ambient() const
{
    return m_ambient;
}

void RVLight::setAmbient(const QColor &ambient)
{
    m_ambient = ambient;
}

QColor RVLight::diffuse() const
{
    return m_diffuse;
}

void RVLight::setDiffuse(const QColor &diffuse)
{
    m_diffuse = diffuse;
}

QColor RVLight::specular() const
{
    return m_specular;
}

void RVLight::setSpecular(const QColor &specular)
{
    m_specular = specular;
}
