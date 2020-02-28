#include "rvsphericalcamera.h"

RVSphericalCamera::RVSphericalCamera()
    :RVCamera(), m_rho(10), m_phi(0), m_theta(0)
{
    updatePosition();
}

float RVSphericalCamera::rho() const
{
    return m_rho;
}

void RVSphericalCamera::setRho(float rho)
{
    m_rho = qMax(rho, 0.1f);
    updatePosition();
}

float RVSphericalCamera::phi() const
{
    return m_phi;
}

void RVSphericalCamera::setPhi(float phi)
{
    m_phi = qBound(phi, -1.5f, +1.5f);
    updatePosition();
}

float RVSphericalCamera::theta() const
{
    return m_theta;
}

void RVSphericalCamera::setTheta(float theta)
{
    m_theta = theta;
    updatePosition();
}

void RVSphericalCamera::updatePosition()
{
    float x = m_target.x() + m_rho*qCos(m_phi)*qCos(m_theta);
    float y = m_target.y() + m_rho*qSin(m_phi);
    float z = m_target.z() + m_rho*qCos(m_phi)*qSin(m_theta);
    m_position = QVector3D(x, y, z);
}
