#ifndef RVSPECCUBE_H
#define RVSPECCUBE_H

#include "rvtexcube.h"



class RVSpecCube : public RVTexCube
{
public:
    RVSpecCube();
    void setCubeTex(QString leftImage, QString rightImage,
                    QString frontImage, QString backImage,
                    QString topImage, QString bottomImage);
};

#endif // RVSPECCUBE_H
