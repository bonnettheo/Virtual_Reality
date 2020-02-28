#include "rvsubjectivcamera.h"

RVSubjectivCamera::RVSubjectivCamera(float yaw, float pitch) : RVStereoCamera(), m_yaw(yaw), m_pitch(pitch)
{

}

void RVSubjectivCamera::move(float d)
{
    m_position += d* QVector3D(m_target.x()-m_position.x(), 0 , m_target.z()-m_position.z());
    updateTarget();
}

void RVSubjectivCamera::turn(float angle)
{
    setYaw(m_yaw+angle);
}

void RVSubjectivCamera::tilt(float angle)
{
    setPitch(m_pitch+angle);
}

void RVSubjectivCamera::lateral(float d)
{
    QVector3D horizontal_target = QVector3D(m_target.x()-m_position.x(), 0 , m_target.z()-m_position.z());
    QVector3D axis = QVector3D().crossProduct(QVector3D(0,1,0), horizontal_target); // left direction
    m_position += QVector3D(axis.x(), 0 , axis.z())*d;
    updateTarget();
}

void RVSubjectivCamera::crouch()
{
    if(m_crouch){
        m_position += QVector3D(0, m_position.y(), 0);
    }else{
        m_position += QVector3D(0, -m_position.y()/2, 0);
    }
    updateTarget();
    m_crouch = !m_crouch;
}

void RVSubjectivCamera::updatePosition(int t)
{
    if(m_jump){
        if(m_time == -1){
            m_time = t;
        }
        t = t - m_time;
        this->setPosition(QVector3D(m_position.x(), m_position_before_jump.y() + (m_jump_trajectory->pos(t*0.001)).y(), m_position.z()));
        if(m_jump_trajectory->pos(t*0.001).y() > m_jump_trajectory->hmax()-1){
            m_got_up = true;
        }
        if(m_got_up && m_jump_trajectory->pos(t*0.001).y() < 1){
            m_jump = false;
            m_got_up = false;
            m_time = -1;
        }
    }

}

void RVSubjectivCamera::jump()
{
    if(!m_jump){
        m_position_before_jump = m_position;
        m_jump_trajectory = new RVBounce(m_position.y()/2, 0.5);
        m_jump = true;
    }
}

float RVSubjectivCamera::yaw() const
{
    return m_yaw;
}

void RVSubjectivCamera::setYaw(float yaw)
{
    m_yaw = yaw;
    updateTarget();
}

float RVSubjectivCamera::pitch() const
{
    return m_pitch;
}

void RVSubjectivCamera::setPitch(float pitch)
{
    m_pitch = pitch;
    updateTarget();
}

void RVSubjectivCamera::updateTarget()
{
    float x = qCos(m_pitch) * qCos(m_yaw);
    float y = qSin(m_pitch);
    float z = - qCos(m_pitch) * qSin(m_yaw);
    this->setTarget(m_position + QVector3D(x,y,z));
}

void RVSubjectivCamera::setPosition(const QVector3D &position)
{
    m_position = position;
    updateTarget();
}
