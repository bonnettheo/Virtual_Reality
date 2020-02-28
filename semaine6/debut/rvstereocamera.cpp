#include "rvstereocamera.h"

RVStereoCamera::RVStereoCamera()
    :RVCamera()
{
    m_eyeDistance = 4.0f;
    m_focalDistance = 60.0f;
    m_cameraType = RV_CAMERA_MONO;
}

QMatrix4x4 RVStereoCamera::viewMatrix()
{
    switch (m_cameraType)
    {
        case RV_CAMERA_LEFT:
            return leftViewMatrix();
        case RV_CAMERA_RIGHT:
            return rightViewMatrix();
        case RV_CAMERA_MONO:
            return RVCamera::viewMatrix();
        default:
            return RVCamera::viewMatrix();
    }
}

QMatrix4x4 RVStereoCamera::projectionMatrix()
{
    switch (m_cameraType)
    {
        case RV_CAMERA_LEFT:
            return leftProjectionMatrix();
        case RV_CAMERA_RIGHT:
            return rightProjectionMatrix();
        case RV_CAMERA_MONO:
            return RVCamera::projectionMatrix();
        default:
            return RVCamera::projectionMatrix();
    }
}

QMatrix4x4 RVStereoCamera::leftViewMatrix()
{
    QVector3D visee = m_target - m_position;
    QVector3D interOeil = QVector3D::crossProduct(visee, m_up);
    interOeil.normalize();
    QVector3D posOeilGauche = m_position + (interOeil * (-m_eyeDistance/2));
    QVector3D cibleGauche = m_target + (interOeil * (-m_eyeDistance/2));

    QMatrix4x4 vue;
    vue.lookAt(posOeilGauche, cibleGauche, m_up);
    return vue;
}

QMatrix4x4 RVStereoCamera::rightViewMatrix()
{
    QVector3D visee = m_target - m_position;
    QVector3D interOeil = QVector3D::crossProduct(visee, m_up);
    interOeil.normalize();
    QVector3D posOeilDroite = m_position + interOeil * (m_eyeDistance/2);
    QVector3D cibleDroite = m_target + interOeil * (+m_eyeDistance/2);

    QMatrix4x4 vue;
    vue.lookAt(posOeilDroite, cibleDroite, m_up);
    return vue;
}

QMatrix4x4 RVStereoCamera::leftProjectionMatrix()
{
    float top, bottom, left, right;
    float tanFovOver2 = qTan(qDegreesToRadians(m_fov/2));

    top = m_zMin * tanFovOver2;
    bottom = - top;

    float a = m_aspect * tanFovOver2 * m_focalDistance;
    float b = a - m_eyeDistance/2;
    float c = a + m_eyeDistance/2;

    left = -b * m_zMin / m_focalDistance;
    right = c * m_zMin / m_focalDistance;

    QMatrix4x4 proj;
    proj.frustum(left, right, bottom, top, m_zMin, m_zMax);
    return proj;
}

QMatrix4x4 RVStereoCamera::rightProjectionMatrix()
{
    float top, bottom, left, right;
    float tanFovOver2 = qTan(qDegreesToRadians(m_fov/2));

    top = m_zMin * tanFovOver2;
    bottom = - top;

    float a = m_aspect * tanFovOver2 * m_focalDistance;
    float b = a - m_eyeDistance/2;
    float c = a + m_eyeDistance/2;

    left = -c * m_zMin / m_focalDistance;
    right = b * m_zMin / m_focalDistance;

    QMatrix4x4 proj;
    proj.frustum(left, right, bottom, top, m_zMin, m_zMax);
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

float RVStereoCamera::focalDistance() const
{
    return m_focalDistance;
}

void RVStereoCamera::setFocalDistance(float focalDistance)
{
    m_focalDistance = focalDistance;
}

float RVStereoCamera::eyeDistance() const
{
    return m_eyeDistance;
}

void RVStereoCamera::setEyeDistance(float eyeDistance)
{
    m_eyeDistance = eyeDistance;
}
