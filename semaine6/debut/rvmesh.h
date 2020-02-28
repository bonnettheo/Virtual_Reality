#ifndef RVMESH_H
#define RVMESH_H

#include "rvbody.h"

class RVMesh : public RVBody
{
public:
    RVMesh();
    ~RVMesh() override;

    void initializeBuffer() override;
    void draw() override;

    void setVertices(QVector<RVVertex> *vertices);
    void setIndices(QVector<uint> *indices);

protected:
    QVector<RVVertex> *m_vertices;
    QVector<uint> *m_indices;
};

#endif // RVMESH_H
