#include <QString>
#include <QDir>
#include <QVector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/matrix4x4.h>

#include "rvmesh.h"

class RVModel : public RVBody
{
public:
    RVModel(QString nomFichier);

    void draw() override;
    void initializeBuffer() override;
    void initializeVAO() override {}
    void update(float t) override;

    void rotate(float angle, QVector3D axis) override;
    void translate(QVector3D position) override;
    void setCamera(RVCamera *camera) override;
    void setLight(RVLight *light) override;
    void setPosition(const QVector3D &position) override;
    void setOrientation(float yaw, float pitch, float roll) override;
    void setScale(float scale) override;

protected:
    QVector<RVMesh*> m_meshes;
    QDir m_directory;
    int m_nbMeshes;

private:
    void loadModel(QString nomFichier);
    void processNode(aiNode* node, const aiScene* scene);
    RVMesh* processMesh(aiMesh* mesh, const aiScene* scene);
};
