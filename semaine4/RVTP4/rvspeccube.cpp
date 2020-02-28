#include "rvspeccube.h"

RVSpecCube::RVSpecCube()
{
    m_VSFileName = ":/shaders/VS_lit_texture_cube.vsh";
    m_FSFileName = ":/shaders/FS_lit_spec_cube.fsh";
}

void RVSpecCube::setCubeTex(QString leftImage, QString rightImage, QString frontImage, QString backImage, QString topImage, QString bottomImage)
{
    //Je charge en mémoire les 6 images des 6 faces
    QImage posX = QImage(rightImage).convertToFormat(QImage::Format_RGBA8888);
    QImage negX = QImage(leftImage).convertToFormat(QImage::Format_RGBA8888);
    QImage posY = QImage(topImage).convertToFormat(QImage::Format_RGBA8888);
    QImage negY = QImage(bottomImage).convertToFormat(QImage::Format_RGBA8888);
    QImage posZ = QImage(frontImage).convertToFormat(QImage::Format_RGBA8888);
    QImage negZ = QImage(backImage).convertToFormat(QImage::Format_RGBA8888);

    //Je prépare le format de la texture cubique
    m_texture = new QOpenGLTexture(QOpenGLTexture::TargetCubeMap);
    m_texture->create();
    m_texture->setSize(posX.width(), posX.height(), posX.depth());
    m_texture->setFormat(QOpenGLTexture::RGBA8_UNorm);
    m_texture->allocateStorage();

    //Je remplis les données de la texture cuboque
    m_texture->setData(0, 0, QOpenGLTexture::CubeMapPositiveX,
                       QOpenGLTexture::RGBA,
                       QOpenGLTexture::UInt8,
                       posX.constBits(),
                       Q_NULLPTR);
    m_texture->setData(0, 0, QOpenGLTexture::CubeMapNegativeX,
                       QOpenGLTexture::RGBA,
                       QOpenGLTexture::UInt8,
                       negX.constBits(),
                       Q_NULLPTR);
    m_texture->setData(0, 0, QOpenGLTexture::CubeMapPositiveY,
                       QOpenGLTexture::RGBA,
                       QOpenGLTexture::UInt8,
                       posY.constBits(),
                       Q_NULLPTR);
    m_texture->setData(0, 0, QOpenGLTexture::CubeMapNegativeY,
                       QOpenGLTexture::RGBA,
                       QOpenGLTexture::UInt8,
                       negY.constBits(),
                       Q_NULLPTR);
    m_texture->setData(0, 0, QOpenGLTexture::CubeMapPositiveZ,
                       QOpenGLTexture::RGBA,
                       QOpenGLTexture::UInt8,
                       posZ.constBits(),
                       Q_NULLPTR);
    m_texture->setData(0, 0, QOpenGLTexture::CubeMapNegativeZ,
                       QOpenGLTexture::RGBA,
                       QOpenGLTexture::UInt8,
                       negZ.constBits(),
                       Q_NULLPTR);

    //Quelques réglages sur la texture
    m_texture->setWrapMode(QOpenGLTexture::ClampToEdge);
    //ici on ajoutera aussi ceux du filtrage...
    m_texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    m_texture->setMagnificationFilter(QOpenGLTexture::Linear);
    m_texture->generateMipMaps();
}

