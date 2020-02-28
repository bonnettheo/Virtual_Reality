#ifndef RVSPHERICALCAMERA_H
#define RVSPHERICALCAMERA_H

#include <QtMath>
#include "rvstereocamera.h"

class RVSphericalCamera : public RVStereoCamera
{
public:
    RVSphericalCamera();

    float rho() const;
    void setRho(float rho);

    float phi() const;
    void setPhi(float phi);

    float theta() const;
    void setTheta(float theta);

protected:
    float m_rho;
    float m_phi;
    float m_theta;

    void updatePosition();
};

#endif // RVSPHERICALCAMERA_H
