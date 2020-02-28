#ifndef RVBOUNCE_H
#define RVBOUNCE_H

#include "rvcurve.h"



class RVBounce : public RVCurve
{
public:
    RVBounce(float hmax = 10.0f, float tmax = 2.0f, float x = 0.0f, float z = 0.0f);

protected:
    float x(double t);
    float y(double t);
    float z(double t);

    float m_hmax;
    float m_tmax;
    float m_x;
    float m_z;
};

#endif // RVBOUNCE_H
