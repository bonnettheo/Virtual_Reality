#ifndef RVSPHERICALCAMERA_H
#define RVSPHERICALCAMERA_H

#include "rvcamera.h"
#include <QtMath>



class RVSphericalCamera : public RVCamera
{
public:
    RVSphericalCamera(float phi=0, float theta=0, float rho=10);
    void update_position();
    float phi() const;
    void setPhi(float phi);

    float theta() const;
    void setTheta(float theta);

    float rho() const;
    void setRho(float rho);

protected:
    float m_phi, m_theta, m_rho;
};

#endif // RVSPHERICALCAMERA_H
