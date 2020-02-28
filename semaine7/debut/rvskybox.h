#ifndef RVSKYBOX_H
#define RVSKYBOX_H

/*!
  \file rvskybox.h
  \brief Déclaration de la classe RVDSkybox.
  \author  Leo Donati
  \date    2019-2020
  \version 6.0

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia
*/

#include "rvbody.h"

class RVSkyBox : public RVBody
{
public:
    RVSkyBox();

    void initializeBuffer() override;
    void initializeVAO() override;
    void draw() override;

    void setCubeTexture(QString leftImage, QString rightImage,
                        QString frontImage, QString backImage,
                        QString topImage, QString bottomImage);


};

#endif // RVSKYBOX_H
