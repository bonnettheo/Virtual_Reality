#ifndef RVTERRAIN_H
#define RVTERRAIN_H

#include "rvsurface.h"



class RVTerrain : public RVSurface
{
public:
    RVTerrain(double width = 1);

    QOpenGLTexture *heightmap() const;
    void setHeightmap(QString heightmapFile);

protected:
    QOpenGLTexture *m_heightmap;
    float heightFactor = 100;

    // RVBody interface
public:
    void draw();
    void initializeBuffer();

    // RVSurface interface
protected:
    float x(double s, double t);
    float y(double s, double t);
    float z(double s, double t);
};

#endif // RVTERRAIN_H
