#ifndef RVTEXCUBE_H
#define RVTEXCUBE_H

/*!
  \file rvtexcube.h
  \brief Déclaration de la classe RVTexCube.
  \author  Leo Donati
  \date    2019-2020
  \version 6.0

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia
*/

#include "rvbody.h"

/*!
 * \class RVTexCube
 * \brief La classe RVTexCube hérite de RVBody et représente un cube 3D avec 6 faces colorées et texturées.
 */
class RVTexCube : public RVBody
{
public:
    RVTexCube();               //!< Constructeur

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

#endif // RVTEXCUBE_H
