#ifndef RVDICE_H
#define RVDICE_H

/*!
  \file rvdice.h
  \brief Déclaration de la classe RVDice.
  \author  Leo Donati
  \date    2019-2020
  \version 5.0

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia
*/

#include "rvtexcube.h"

/*!
 * \class RVDice
 * \brief La classe RVDice hérite de RVTexCube et représente un dé à jouer.
 */
class RVDice : public RVTexCube
{
public:
    RVDice();                           //!< Constructeur
    void initializeBuffer() override;   //!< Prépare le dé à jouer

    void update(float t) override;
};

#endif // RVDICE_H
