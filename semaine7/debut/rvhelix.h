#ifndef RVHELIX_H
#define RVHELIX_H

/*!
  \file rvhelix.h
  \brief Déclaration de la classe RVHelix.
  \author  Leo Donati
  \date    2019-2020
  \version 6.0

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia

  Utilise la classe RVCurve avec l'équation paramétrée de l'hélice
*/

#include "rvcurve.h"

class RVHelix : public RVCurve
{
public:
    RVHelix(double radius = 1.0, double pitch = 0.2);

    double radius() const;
    void setRadius(double radius);

    double frequency() const;
    void setFrequency(double frequency);

    double pitch() const;
    void setPitch(double pitch);

    double numWindings() const;
    void setNumWindings(double numWindings);

protected:
    float x(double t) override;
    float y(double t) override;
    float z(double t) override;

    double m_radius;         //!< rayon de l'hélice
    double m_frequency;      //!< fréquence de rotation (nb tour/s)
    double m_pitch;          //!< pas de l'hélice (de combien elle avance à chaque tour)
    double m_numWindings;    //!< nombre d'enroulements
};

#endif // RVHELIX_H
