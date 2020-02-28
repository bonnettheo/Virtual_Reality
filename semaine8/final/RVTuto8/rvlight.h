#ifndef RVLIGHT_H
#define RVLIGHT_H

/*!
  \file rvlight.h
  \brief Déclaration de la classe RVLight.
  \author  Leo Donati
  \date    2019-2020
  \version 5.0

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia
*/

#include <QVector3D>
#include <QColor>

class RVLight
{
public:
    RVLight();

    QVector3D position() const;
    void setPosition(const QVector3D &position);

    QColor ambient() const;
    void setAmbient(const QColor &ambient);

    QColor diffuse() const;
    void setDiffuse(const QColor &diffuse);

    QColor specular() const;
    void setSpecular(const QColor &specular);

private:
    QVector3D m_position;
    QColor m_ambient;
    QColor m_diffuse;
    QColor m_specular;
};

#endif // RVLIGHT_H
