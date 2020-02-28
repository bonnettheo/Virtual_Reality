#ifndef RVSTEREOCAMERA_H
#define RVSTEREOCAMERA_H

#define RV_CAMERA_MONO 0
#define RV_CAMERA_LEFT 1
#define RV_CAMERA_RIGHT 2


#include "rvcamera.h"



class RVStereoCamera : public RVCamera
{
public:
    RVStereoCamera(float eyeDistance = 2.0f, float focalDistance = 180.0f, int cameraType = RV_CAMERA_MONO);

    float eyeDistance() const;
    void setEyeDistance(float eyeDistance);

    float focalDistance() const;
    void setFocalDistance(float focalDistance);

    QMatrix4x4 viewMatrix() override;
    QMatrix4x4 projectionMatrix() override;

    QMatrix4x4 leftViewMatrix();
    QMatrix4x4 leftProjectionMatrix();
    QMatrix4x4 rightViewMatrix();
    QMatrix4x4 rightProjectionMatrix();

    int cameraType() const;
    void setCameraType(int cameraType);

protected:
    float m_eyeDistance;
    float m_focalDistance;
    int m_cameraType;
};

#endif // RVSTEREOCAMERA_H
