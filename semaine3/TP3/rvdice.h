#ifndef RVDICE_H
#define RVDICE_H

/*!
  \file rvcube.h
  \brief Déclaration de la classe RVCube.
  \author  Leo Donati
  \date    2019-2020
  \version 1.5

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia
*/

#include "rvbody.h"

/*!
 * \class RVCube
 * \brief La classe RVCube hérite de RVBody et représente un cube 3D avec 6 faces colorées.
 */
class RVDice : public RVBody
{
public:
    RVDice();               //!< Constructeur

    void draw() override;   //!< Dessine le cube

    /*!
     * \brief modelMatrix
     * \return une matrice 4x4 qui place le cube par rapport à sa position et a son orientation
     *
     * Dans le cas du cube nous devons d'abord lui appliquer une translation de vecteur
     * (-0.5, -0.5, -0.5) pour que le centre du cube se trouve à l'origine.
     * Voilà pourquoi on doit la surcharger.
     */
    QMatrix4x4 modelMatrix() override;

    void initializeVAO() override;      //!< Prépare le VAO
    void initializeBuffer() override;   //!< Prépare le cube
};

#endif // RVCUBE_H
