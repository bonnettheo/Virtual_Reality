#include "rvlightbulb.h"

RVLightBulb::RVLightBulb(double r)
    :RVSphere(r)
{
    m_radius = r;
    m_minS = 0;
    m_maxS = 2 * M_PI;
    m_minT = - M_PI_2;
    m_maxT = + M_PI_2;
}

RVLightBulb::~RVLightBulb()
{ }



float RVLightBulb::x(double s, double t)
{
    return float(m_radius*qCos(t)*qCos(s)) ;
}

float RVLightBulb::y(double s, double t)
{
    return float(m_radius*qSin(t));
}

float RVLightBulb::z(double s, double t)
{
    return float(m_radius* qCos(t)*qSin(s));
}

double RVLightBulb::radius() const
{
    return m_radius;
}

void RVLightBulb::setRadius(double radius)
{
    m_radius = radius;
}

