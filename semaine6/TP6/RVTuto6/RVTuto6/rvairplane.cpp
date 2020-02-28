#include "rvairplane.h"
#include "rvsphericalcamera.h"

RVAirPlane::RVAirPlane(float a, float v, QString model) : RVModel(model)
{
    m_acceleration = a;
    m_velocity = v;
}

void RVAirPlane::update(float t)
{
    QVector3D direction = QVector3D(0, 0, -1);
    direction = m_orientation.rotatedVector(direction);
    turnPropeller(direction);
    m_velocity = m_velocity + m_acceleration*(t/1000);

    if(m_elasticity && m_attach_camera){
        m_acceleration -= m_acceleration/10;
        m_velocity -= m_velocity/50;
    }


    QVector3D axis = QVector3D(0, 0, 1);
    axis = m_orientation.rotatedVector(axis);
    this->rotate(-m_roulis/10, axis);
    m_roulis -= m_roulis/10;

    if(m_velocity<0){
        m_acceleration = 0;
        m_velocity = 0;
    }

    this->translate(direction*m_velocity);

    if (m_attach_camera) {
        m_camera->setTarget(m_position);
        if(m_elasticity && m_acceleration>0){
            m_camera->setPosition(m_position + direction*(-70-(m_acceleration*500)));
        } else {
            m_camera->setPosition(m_position + direction*-70);
        }
    }
}

float RVAirPlane::acceleration() const
{
    return m_acceleration;
}

void RVAirPlane::setAcceleration(float acceleration)
{
    m_acceleration = acceleration;
}

void RVAirPlane::lacetTurn(float angle)
{
    QVector3D axis = QVector3D(0, 1, 0);
    axis = m_orientation.rotatedVector(axis);
    this->rotate(angle, axis);
}

void RVAirPlane::setTanguage(float angle)
{
    QVector3D axis = QVector3D(1, 0, 0);
    axis = m_orientation.rotatedVector(axis);
    this->rotate(angle, axis);
}

void RVAirPlane::setRoulis(float angle)
{
    QVector3D axis = QVector3D(0, 0, 1);
    axis = m_orientation.rotatedVector(axis);
    m_roulis += angle;
    this->rotate(angle, axis);

}

void RVAirPlane::turnPropeller(QVector3D axis)
{
    m_propellerSpeed = m_velocity*10;
    m_meshes[2]->rotate(m_propellerSpeed, axis);
}

float RVAirPlane::getPropellerSpeed() const
{
    return m_propellerSpeed;
}

void RVAirPlane::setPropellerSpeed(float value)
{
    m_propellerSpeed = value;
}

bool RVAirPlane::getAttach_camera() const
{
    return m_attach_camera;
}

void RVAirPlane::setAttach_camera(bool attach_camera)
{
    m_attach_camera = attach_camera;
}

float RVAirPlane::getVelocity() const
{
    return m_velocity;
}

void RVAirPlane::setVelocity(float velocity)
{
    m_velocity = velocity;
}
