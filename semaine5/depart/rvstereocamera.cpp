#include "rvstereocamera.h"
#include "math.h"

RVStereoCamera::RVStereoCamera(float eyeDistance, float focalDistance, int cameraType):
    RVCamera(), m_eyeDistance(eyeDistance), m_focalDistance(focalDistance), m_cameraType(cameraType)
{

}

float RVStereoCamera::eyeDistance() const
{
    return m_eyeDistance;
}

void RVStereoCamera::setEyeDistance(float eyeDistance)
{
    m_eyeDistance = eyeDistance;
}

float RVStereoCamera::focalDistance() const
{
    return m_focalDistance;
}

void RVStereoCamera::setFocalDistance(float focalDistance)
{
    m_focalDistance = focalDistance;
}

QMatrix4x4 RVStereoCamera::viewMatrix()
{
    switch (m_cameraType) {
    case RV_CAMERA_MONO :
        return RVCamera::viewMatrix();
        break;
    case RV_CAMERA_LEFT :
        return leftViewMatrix();
        break;
    case RV_CAMERA_RIGHT :
        return rightViewMatrix();
        break;
    }
}

QMatrix4x4 RVStereoCamera::projectionMatrix()
{
    switch (m_cameraType) {
    case RV_CAMERA_MONO :
        return RVCamera::projectionMatrix();
        break;
    case RV_CAMERA_LEFT :
        return leftProjectionMatrix();
        break;
    case RV_CAMERA_RIGHT :
        return rightProjectionMatrix();
        break;
    }
}

QMatrix4x4 RVStereoCamera::leftViewMatrix()
{
    QMatrix4x4 view;
    QVector3D v = (m_target-m_position);
    v.crossProduct(v, m_up);
    QVector3D posOG = m_position - (m_eyeDistance/2)*(v/v.length());
    QVector3D cibleOG = m_target - (m_eyeDistance/2)*(v/v.length());

    view.lookAt(posOG, cibleOG, m_up);
    return view;
}

QMatrix4x4 RVStereoCamera::leftProjectionMatrix()
{
    QMatrix4x4 proj;
    if (m_isOrthogonal) {
        proj.ortho(-m_fov * m_aspect/10, m_fov * m_aspect/10, -m_fov/10, m_fov/10, m_zMin, m_zMax);
    }
    else {
        float top = m_zMin * tan((m_fov*M_PI)/360);
        float bottom = -top;


        float a = (m_focalDistance*top)/m_zMin;
        float b = a -(m_eyeDistance/2);
        float c = a +(m_eyeDistance/2);
        float left = (m_zMin * b) / m_focalDistance;
        float right = (m_zMin * c) / m_focalDistance;
        proj.frustum(-left, right, bottom, top, m_zMin, m_zMax);
    }
    return proj;
}

QMatrix4x4 RVStereoCamera::rightViewMatrix()
{
    QMatrix4x4 view;
    QVector3D v = (m_target-m_position);
    v.crossProduct(v, m_up);
    v.normalize();
    QVector3D posOG = m_position + (m_eyeDistance/2)*v;
    QVector3D cibleOG = m_target + (m_eyeDistance/2)*v;

    view.lookAt(posOG, cibleOG, m_up);
    return view;
}

QMatrix4x4 RVStereoCamera::rightProjectionMatrix()
{
    QMatrix4x4 proj;
    if (m_isOrthogonal) {
        proj.ortho(-m_fov * m_aspect/10, m_fov * m_aspect/10, -m_fov/10, m_fov/10, m_zMin, m_zMax);
    }
    else {
        float top = m_zMin * tan((m_fov*M_PI)/360);
        float bottom = -top;


        float a = (m_focalDistance*top)/m_zMin;
        float b = a +(m_eyeDistance/2);
        float c = a - (m_eyeDistance/2);
        float left = (m_zMin * b) / m_focalDistance;
        float right = (m_zMin * c) / m_focalDistance;
        proj.frustum(-left, right, bottom, top, m_zMin, m_zMax);
    }
    return proj;
}

int RVStereoCamera::cameraType() const
{
    return m_cameraType;
}

void RVStereoCamera::setCameraType(int cameraType)
{
    m_cameraType = cameraType;
}
