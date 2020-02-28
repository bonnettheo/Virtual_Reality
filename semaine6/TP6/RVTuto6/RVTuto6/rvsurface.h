#ifndef RVSURFACE_H
#define RVSURFACE_H

/*!
  \file rvsurface.h
  \brief Déclaration de la classe RVSurface.
  \author  Leo Donati
  \date    2019-2020
  \version 6.0

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia
*/

#include <QtMath>
#include <QtDebug>
#include "rvbody.h"

/*!
 * \class RVSurface
 * \brief classe abstraite, représente une surface paramètrée P(s, t) et texturée
 *
 * Trois fonctions virtuelles pures sont à surcharger dans toute classe fille.
 * x(s,t)
 * y(s,t)
 * z(s,t)
 * Mais il faut aussi définir le bon intervalle des paramètres t et s
 * ainsi que le nombre de segments de la discrétisation de ces deux intervalles.
 */
class RVSurface : public RVBody
{
public:
    RVSurface();
    void draw() override;
    void initializeBuffer() override;

    virtual QVector3D pos(double s, double t) {
        return QVector3D(x(s,t), y(s,t), z(s,t));
    }

    QVector3D normal(double s, double t) ;


protected:
    virtual float x(double s, double t) = 0;
    virtual float y(double s, double t) = 0;
    virtual float z(double s, double t) = 0;

    QVector3D gradS(double s, double t);
    QVector3D gradT(double s, double t);

    double m_minT, m_maxT;       //!< définit l'intervalle en t
    int m_numSegT;              //!< nb de subdivisions de l'intervalle en t
    double m_minS, m_maxS;       //!< définit l'intervalle en s
    int m_numSegS;              //!< nb de subdivisions de l'intervalle en s
    float m_time = 0;
    double ds = 0.1;
    double dt = 0.1;
};
#endif // RVSURFACE_H
