#include "rvsphere.h"

RVSphere::RVSphere(double r)
    :RVSurface()
{
    m_radius = r;
    m_minS = 0;
    m_maxS = 2 * M_PI;
    m_minT = - M_PI_2;
    m_maxT = + M_PI_2;
}

RVSphere::~RVSphere()
{ }



float RVSphere::x(double s, double t)
{
    return float(m_radius*qCos(t)*qCos(s)) ;
}

float RVSphere::y(double s, double t)
{
    return float(m_radius*qSin(t));
}

float RVSphere::z(double s, double t)
{
    return float(m_radius* qCos(t)*qSin(s));
}

void RVSphere::update(float time)
{
    int vitAngulaire = 30; //en degré par seconde
    this->rotate(time*vitAngulaire*0.001, QVector3D(1, 0, 0));
    // this->setPosition(m_trajectory->pos(time*0.001));
}

double RVSphere::radius() const
{
    return m_radius;
}

void RVSphere::setRadius(double radius)
{
    m_radius = radius;
}

