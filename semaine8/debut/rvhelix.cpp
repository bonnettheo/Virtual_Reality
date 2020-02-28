#include "rvhelix.h"

RVHelix::RVHelix(double radius, double pitch)
    :RVCurve()
{
    m_numWindings = 3;
    m_radius = radius;
    m_frequency = 1;
    m_pitch = pitch;
    m_maxT = M_PI * 2  * m_numWindings;

    m_FSFileName = ":/shaders/FS_simple.fsh";
    m_VSFileName = ":/shaders/VS_simpler.vsh";
}

double RVHelix::radius() const
{
    return m_radius;
}

void RVHelix::setRadius(double radius)
{
    m_radius = radius;
}

double RVHelix::frequency() const
{
    return m_frequency;
}

void RVHelix::setFrequency(double frequency)
{
    m_frequency = frequency;
}

double RVHelix::pitch() const
{
    return m_pitch;
}

void RVHelix::setPitch(double pitch)
{
    m_pitch = pitch;
}

float RVHelix::x(double t)
{
    return float(m_radius*qCos(m_frequency*t));
}

float RVHelix::y(double t)
{
    return float(m_pitch * m_frequency * t / 2 * M_PI);
}

float RVHelix::z(double t)
{
    return float(m_radius*qSin(m_frequency*t));
}

double RVHelix::numWindings() const
{
    return m_numWindings;
}

void RVHelix::setNumWindings(double numWindings)
{
    m_numWindings = numWindings;
}
