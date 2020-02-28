#include "rvbounce.h"

RVBounce::RVBounce(float hmax, float tmax, float x, float z):
    m_hmax(hmax), m_tmax(tmax), m_x(x), m_z(z)
{

}

float RVBounce::x(double t)
{
    return m_x;
}

float RVBounce::y(double t)
{
    float a = -m_hmax/(m_tmax*m_tmax);
    float b = -2 * a * m_tmax;
    double usable_t = fmod(t, 2*m_tmax);
    return a*usable_t*usable_t + b*usable_t;
}

float RVBounce::z(double t)
{
    return m_z;
}

float RVBounce::hmax() const
{
    return m_hmax;
}
