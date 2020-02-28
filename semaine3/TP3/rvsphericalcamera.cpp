#include "rvsphericalcamera.h"

RVSphericalCamera::RVSphericalCamera(float phi, float theta, float rho): m_phi(phi), m_theta(theta), m_rho(rho)
{
    update_position();
}

void RVSphericalCamera::update_position()
{
    float xPos = m_target[0] + m_rho * qCos(m_phi) * qCos(m_theta);
    float yPos = m_target[1] + m_rho * qSin(m_phi);
    float zPos = m_target[2] + m_rho * qCos(m_phi) * qSin(m_theta);
    m_position = QVector3D(xPos, yPos, zPos);
}

float RVSphericalCamera::phi() const
{
    return m_phi;
}

void RVSphericalCamera::setPhi(float phi)
{

    if (-M_PI/2 < phi && phi < M_PI/2){
        m_phi = phi;
        update_position();
    }
}

float RVSphericalCamera::theta() const
{
    return m_theta;
}

void RVSphericalCamera::setTheta(float theta)
{
    m_theta = theta;
    update_position();
}

float RVSphericalCamera::rho() const
{
    return m_rho;
}

void RVSphericalCamera::setRho(float rho)
{
    if (rho <=0)return;
    m_rho = rho;
    update_position();
}
