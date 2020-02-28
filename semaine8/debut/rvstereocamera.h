#ifndef RVSTEREOCAMERA_H
#define RVSTEREOCAMERA_H

/*!
  \file rvstereocamera.h
  \brief Déclaration de la classe RVStereoCamera.
  \author  Leo Donati
  \date    2019-2020
  \version 5.0

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia
*/

#define RV_CAMERA_MONO 0
#define RV_CAMERA_LEFT 1
#define RV_CAMERA_RIGHT 2

#include <QtMath>
#include "rvcamera.h"

class RVStereoCamera : public RVCamera
{
public:
    RVStereoCamera();

    QMatrix4x4 viewMatrix() override;
    QMatrix4x4 projectionMatrix() override;

    float eyeDistance() const;
    void setEyeDistance(float eyeDistance);

    float focalDistance() const;
    void setFocalDistance(float focalDistance);

    int cameraType() const;
    void setCameraType(int cameraType);

protected:
    QMatrix4x4 leftViewMatrix();
    QMatrix4x4 rightViewMatrix();
    QMatrix4x4 leftProjectionMatrix();
    QMatrix4x4 rightProjectionMatrix();

    float m_eyeDistance;
    float m_focalDistance;
    int m_cameraType;
};

#endif // RVSTEREOCAMERA_H
