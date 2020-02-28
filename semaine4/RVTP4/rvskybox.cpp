#include "rvskybox.h"

RVSkyBox::RVSkyBox()
    :RVBody()
{
    m_VSFileName = ":/shaders/VS_skybox_texture.vsh";
    m_FSFileName = ":/shaders/FS_skybox_texture.fsh";
}

void RVSkyBox::initializeBuffer()
{
    //Definitions des 8 sommets du cube
    //Cette fois le cube a un coté de 2
    //et l'origine est au centre.
    QVector3D A(-1, -1, 1);
    QVector3D B(1, -1, 1);
    QVector3D C(1, 1, 1);
    QVector3D D(-1, 1, 1);
    QVector3D E(-1, -1, -1);
    QVector3D F(1, -1, -1);
    QVector3D G(1, 1, -1);
    QVector3D H(-1, 1, -1);

    //On prépare le tableau des données
    QVector3D vertexData[] = {
        A, B, C, D, //face avant
        H, G, F, E, //face arriere
        A, D, H, E, //face gauche
        B, F, G, C, //face droite
        D, C, G, H, //face dessus
        A, E, F, B, //face dessous
    };

    //Lien du VBO avec le contexte de rendu OpenG
    m_vbo.bind();
    //Allocation des données dans le VBO
    m_vbo.allocate(vertexData, sizeof (vertexData));
    m_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    //Libération du VBO
    m_vbo.release();

    m_numVertices = 24;
    m_numTriangles = 12;
}

void RVSkyBox::initializeVAO()
{
    //Initialisation du VAO
    m_vao.bind();
    m_vbo.bind();

    //Définition des attributs
    m_program.setAttributeBuffer("rv_Position", GL_FLOAT, 0, 3);
    m_program.enableAttributeArray("rv_Position");

    //Libération
    m_vao.release();
    m_program.release();
}

void RVSkyBox::draw()
{
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);
    glEnable(GL_CULL_FACE);

    if (m_texture) {
        glEnable(GL_TEXTURE_CUBE_MAP);
        glEnable(GL_TEXTURE0);
        m_texture->bind();
    }
    m_program.bind();
    m_vao.bind();

    QMatrix4x4 matrix;
    matrix = m_camera->projectionMatrix() * m_camera->viewMatrix() * this->modelMatrix();
    m_program.setUniformValue("u_ModelViewProjectionMatrix", matrix);
    m_program.setUniformValue("texture0", 0);

    for (int i = 0; i<6; i++)
        glDrawArrays(GL_TRIANGLE_FAN, 4*i, 4);

    m_vao.release();
    m_program.release();

    if (m_texture) {
        m_texture->release();
        glDisable(GL_TEXTURE0);
        glDisable(GL_TEXTURE_CUBE_MAP);
    }
    glFrontFace(GL_CCW);
}

void RVSkyBox::setCubeTexture(QString leftImage,
                              QString rightImage,
                              QString frontImage,
                              QString backImage,
                              QString topImage,
                              QString bottomImage)
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
