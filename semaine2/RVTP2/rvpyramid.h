#ifndef RVPYRAMID_H
#define RVPYRAMID_H

/*!
    \file rvpyramid.h
    \brief Déclaration de la classe RVPyramid.
    \author  Leo Donati
    \date    2019-2020
    \version 1.3

    Cours de Réalité Virtuelle
    Polytech'Nice Sophia
  */

#include "rvbody.h"

/*!
 * \class RVPyramid.
 * \brief Un exemple de classe qui hérite de RVBody.
 *
 * Pas très intéressante (4 sommets). Utilisée dans le Tuto n°2
 * Donne un exemple de comment on crée des classes filles de RVBody
*/
class RVPyramid : public RVBody
{
public:
    RVPyramid();                    //!<    Constructeur

    void draw() override;           //!<    Lance le rendu

protected:
    void initializeBuffer() override;   //!<    Prépare les buffers
    void initializeVAO() override;      //!<    Lie le buffer avec les attributs du shader
};

#endif // RVPYRAMID_H
