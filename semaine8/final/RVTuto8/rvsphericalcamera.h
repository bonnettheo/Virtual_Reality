#ifndef RVSPHERICALCAMERA_H
#define RVSPHERICALCAMERA_H

/*!
  \file rvsphericalcamera.h
  \brief Déclaration de la classe RVSphericalCamera.
  \author  Leo Donati
  \date    2019-2020
  \version 5.0

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia
*/

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
