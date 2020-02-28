#ifndef RVPLANE_H
#define RVPLANE_H

#include "rvbody.h"

class RVPlane : public RVBody
{
public:
    RVPlane(int lenX = 10, int lenZ = 10);

protected:
    int lenX;
    int lenZ;

    void initializeBuffer() override;
    void draw() override;
    QMatrix4x4 modelMatrix() override;
    void initializeVAO() override;
};

#endif // RVPLANE_H
