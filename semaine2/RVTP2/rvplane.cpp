#include "rvplane.h"

RVPlane::RVPlane(int lenX, int lenZ)
    :RVBody()
{
    this->lenX = lenX;
    this->lenZ = lenZ;

    m_VSFileName = ":/shaders/VS_simpler.vsh";
    m_FSFileName = ":/shaders/FS_plan.fsh";
}

void RVPlane::initializeBuffer()
{
    QVector3D A(0, 0, 0);
    QVector3D B(lenX, 0, 0);
    QVector3D C(lenX, 0, lenZ);
    QVector3D D(0, 0 ,lenZ);

    QVector3D vertexData[] = {
        A, B, C, D,
    };

    //Initialisation du Vertex Buffer Object
    m_vbo = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    //Création du VBO
    m_vbo.create();
    //Lien du VBO avec le contexte de rendu OpenG
    m_vbo.bind();
    //Allocation des données dans le VBO
    m_vbo.allocate(vertexData, sizeof (vertexData));
    m_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    //Libération du VBO
    m_vbo.release();
}

void RVPlane::draw()
{
    m_program.bind();
    m_vao.bind();

    //Définition de la variable uniforme
    QMatrix4x4 matrix;
    matrix = m_camera->projectionMatrix() * m_camera->viewMatrix() * this->modelMatrix();

    m_program.setUniformValue("u_ModelViewProjectionMatrix", matrix);
    m_program.setUniformValue("u_Opacity", m_opacity);
    m_program.setUniformValue("u_Color", m_globalColor);

    if(m_wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if(m_culling)
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);


    m_vao.release();
    m_program.release();
}

void RVPlane::initializeVAO()
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

QMatrix4x4 RVPlane::modelMatrix()
{
    QMatrix4x4 model;
    model.translate((float)(-lenX / 2.0f), 0, (float)(-lenZ / 2.0f));
    return RVBody::modelMatrix() * model;
}
