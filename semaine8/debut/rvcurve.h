#ifndef RVCURVE_H
#define RVCURVE_H

/*!
  \file rvcurve.h
  \brief Déclaration de la classe RVCurve.
  \author  Leo Donati
  \date    2019-2020
  \version 5.0

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia
*/

#include <QtMath>
#include "rvbody.h"

/*!
 * \class RVCurve
 * \brief Classe abstraite, hérite de RVBody. Implémente une courbe dans l'espace
 *
 * Utilise le shader "simpler" avec une couleur uniforme
 * Il faut surcharger x(t), y(t), z(t) pour avoir une vraie courbe
 * Exemple de classe fille : RVHelix
 */
class RVCurve : public RVBody
{
public:
    RVCurve();

    /*!
     * \brief pos donne la position d'un point de la courbe en fonction du temps
     * \param t temps entre minT et maxT
     * \return le QVector3D contenant les coordonnées du point position.
     */
    virtual QVector3D pos(double t) {return QVector3D(x(t), y(t), z(t));}

    void draw() override;
    void initializeVAO() override;

    double minT() const;
    void setMinT(double minT);

    double maxT() const;
    void setMaxT(double maxT);

    int numSeg() const;
    void setNumSeg(int numSeg);

    float lineWidth() const;
    void setLineWidth(float lineWidth);

protected:
    void initializeBuffer() override;

    virtual float x(double t) = 0;              //!< Fonction qui donne l'abscisse en fonction du temps
    virtual float y(double t) {return 0.0f; }      //!< Fonction qui donne l'ordonnée en fonction du temps
    virtual float z(double t) = 0;          //!< Fonction qui donne la côte en fonction du temps

    double m_minT;                       //!< Définit la borne inféreieure de l'intervalle de temps
    double m_maxT;                       //!< Définit la borne supérieure de l(intervalle de temps
    int m_numSeg;                       //!< Nombre de segments utilisé pour découper l'intervalle de temps
    float m_lineWidth;                    //!< Epaisseur du trait en pixels
};

#endif // RVCURVE_H
