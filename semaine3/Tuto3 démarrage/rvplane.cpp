#include "rvplane.h"

struct RVVertex {
    QVector3D position;         //! position du sommet
    QVector2D texCoord;         //! coordonnées texture

    RVVertex(QVector3D pos = QVector3D(), QVector2D tex = QVector2D())
    {
        position = pos;
        texCoord = tex;
    }
};

RVPlane::RVPlane(float lenght, float width)
    :RVBody(), m_texture()
{
    m_VSFileName = ":/shaders/VS_simple_texture.vsh";
    m_FSFileName = ":/shaders/FS_plan_texture.fsh";
    m_length = lenght;
    m_width = width;
}

void RVPlane::draw()
{
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (m_texture) {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE0);
        m_texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        m_texture->setMagnificationFilter(QOpenGLTexture::Linear);
        //Liaison de la texture
        m_texture->bind();
    }
    m_program.setUniformValue("texture0", 0);

    if (m_wireFrame) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDisable(GL_CULL_FACE);
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glEnable(GL_CULL_FACE);
    }

    m_program.bind();
    m_vao.bind();

    QMatrix4x4 matrix;
    matrix = m_camera->projectionMatrix() * m_camera->viewMatrix() * this->modelMatrix();
    m_program.setUniformValue("u_ModelViewProjectionMatrix", matrix);
    m_program.setUniformValue("u_opacity", m_opacity);
    m_program.setUniformValue("u_color", m_globalColor);

    glDrawArrays(GL_TRIANGLE_FAN, 0, m_numVertices);

    m_vao.release();
    m_program.release();
    if (m_texture) {
        m_texture->release();
        glDisable(GL_TEXTURE0);
        glDisable(GL_TEXTURE_2D);
    }
}

void RVPlane::initializeBuffer()
{
    QVector3D A(-m_length/2, 0, m_width/2);
    QVector3D B(m_length/2, 0, m_width/2);
    QVector3D C(m_length/2, 0, -m_width/2);
    QVector3D D(-m_length/2, 0, -m_width/2);

    QVector2D SW(0, 0);
    QVector2D SE(1, 0);
    QVector2D NE(1, 1);
    QVector2D NW(0, 1);

    RVVertex vertexData[] = {
        RVVertex(A, SW),
        RVVertex(B, SE),
        RVVertex(C, NE),
        RVVertex(D, NW)
    };


    //Initialisation et remplissage du Vertex Buffer Object
    m_vbo.bind();
    m_vbo.allocate(vertexData, sizeof (vertexData));
    m_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vbo.release();

    m_numVertices = 4;
    m_numTriangles = 2;
}


void RVPlane::initializeVAO()
{
    //Initialisation du VAO
    m_vao.bind();
    m_vbo.bind();
    m_ibo.bind();

    //Définition de l'attribut position
    m_program.setAttributeBuffer("rv_Position", GL_FLOAT, 0, 3, sizeof(RVVertex));
    m_program.enableAttributeArray("rv_Position");

    //Définition de l'attribut de coordonnée texture
    m_program.setAttributeBuffer("rv_TexCoord", GL_FLOAT, sizeof(RVVertex::position), 2, sizeof(RVVertex));
    m_program.enableAttributeArray("rv_TexCoord");

    //Libération
    m_vao.release();
    m_program.release();
}

// SETTER AND GETTER


void RVPlane::setTexture(QString textureFilename)
{
    if (m_texture)
        delete m_texture;
    m_texture = new QOpenGLTexture(QImage(textureFilename));
}

