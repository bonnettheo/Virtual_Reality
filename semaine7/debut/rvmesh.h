#ifndef RVMESH_H
#define RVMESH_H

/*!
  \file rvmesh.h
  \brief Déclaration de la classe RVMesh.
  \author  Leo Donati
  \date    2019-2020
  \version 6.0

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia
*/

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
