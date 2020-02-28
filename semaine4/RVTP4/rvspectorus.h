#ifndef RVSPECTORUS_H
#define RVSPECTORUS_H

#include "rvtorus.h"



class RVSpecTorus : public RVTorus
{
public:
    RVSpecTorus(double smallRadius = 1.0, double bigRadius = 4.0);
    void setTorusTex(QString leftImage, QString rightImage,
                    QString frontImage, QString backImage,
                    QString topImage, QString bottomImage);
};

#endif // RVSPECTORUS_H
