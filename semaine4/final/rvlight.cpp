#include "rvlight.h"

RVLight::RVLight(QVector3D light_pos, QColor ambient, QColor diffuse, QColor specular)
    : m_position(light_pos), m_ambient(ambient), m_diffuse(diffuse), m_specular(specular)
{

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
