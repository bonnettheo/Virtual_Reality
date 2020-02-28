#ifndef RVMODEL_H
#define RVMODEL_H

/*!
  \file rvmesh.h
  \brief Déclaration de la classe RVMesh.
  \author  Leo Donati
  \date    2019-2020
  \version 6.0

  Inspiré de travail de Joey de Vries sur learnopengl.com

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia
*/

#include <QString>
#include <QDir>
#include <QVector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/matrix4x4.h>
#include <QtDebug>

#include "rvmesh.h"


class RVModel : public RVBody
{
public:
    RVModel(QString nomFichier);

    void draw() override;
    void initializeBuffer() override;
    void initializeVAO() override {}

    void setCamera(RVCamera* cam) override;
    void setLight(RVLight* light) override;
    void rotate(float angle, QVector3D axis) override;
    void translate(QVector3D position) override;
    void setOrientation(float yaw, float pitch, float roll) override;

protected:
    QVector<RVMesh*> m_meshes;
    QDir m_directory;
    int m_nbMeshes;

private:
    void loadModel(QString nomFichier);
    void processNode(aiNode* node, const aiScene* scene);
    RVMesh* processMesh(aiMesh* mesh, const aiScene* scene);
};

#endif // RVMODEL_H
