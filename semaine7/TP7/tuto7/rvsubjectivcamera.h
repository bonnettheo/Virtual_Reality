#ifndef RVSUBJECTIVCAMERA_H
#define RVSUBJECTIVCAMERA_H

#include "rvbounce.h"
#include "rvstereocamera.h"



class RVSubjectivCamera : public RVStereoCamera
{
public:
    RVSubjectivCamera(float yaw = 0.0, float pitch = 0.0);

    void move(float d);
    void turn(float angle);
    void tilt(float angle);
    void lateral(float d);
    void crouch();
    void jump();
    void updatePosition(int t);

    float yaw() const;
    void setYaw(float yaw);

    float pitch() const;
    void setPitch(float pitch);

protected :
    float m_yaw;   // y axis
    float m_pitch; // up down
    bool m_crouch = false;
    bool m_jump = false;
    bool m_got_up = false;
    int m_time = -1;
    RVBounce *m_jump_trajectory;
    QVector3D m_position_before_jump;

private :
    void updateTarget();


    // RVCamera interface
public:
    void setPosition(const QVector3D &position);
};

#endif // RVSUBJECTIVCAMERA_H
