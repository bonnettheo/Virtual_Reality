#ifndef RVAIRPLANE_H
#define RVAIRPLANE_H

#include "rvmodel.h"



class RVAirPlane : public RVModel
{
public:
    RVAirPlane(float acceleration = 0, float velocity = 1, QString model = "/home/bonnet/Documents/cours-si5/RV/semaine6/debut/model/GeeBee2.x");
    void update(float t);


    float acceleration() const;
    void setAcceleration(float acceleration);
    void lacetTurn(float angle);
    void setTanguage(float angle);
    void turnPropeller(QVector3D axis);

    float getPropellerSpeed() const;
    void setPropellerSpeed(float value);

    bool getAttach_camera() const;
    void setAttach_camera(bool attach_camera);

    float getVelocity() const;
    void setVelocity(float velocity);

    void setRoulis(float angle);
private:
    float m_velocity;
    float m_acceleration;
    float m_propellerSpeed = 5;
    float m_roulis = 0;
    bool m_attach_camera = true;
    bool m_elasticity = true;

    // RVBody interface
};

#endif // RVAIRPLANE_H
