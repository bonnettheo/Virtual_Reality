#include "rvplane.h"

RVPlane::RVPlane(float lenght, float width)
    :RVBody()
{
    m_length = lenght;
    m_width = width;
}

void RVPlane::draw()
{
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (m_wireFrame) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDisable(GL_CULL_FACE);
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glEnable(GL_CULL_FACE);
    }

    if (m_texture) {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE0);
        m_texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        m_texture->setMagnificationFilter(QOpenGLTexture::Linear);
        //Liaison de la texture
        m_texture->bind();
    }

    m_program.bind();
    m_vao.bind();

    m_program.setUniformValue("u_ModelMatrix", this->modelMatrix());
    m_program.setUniformValue("u_ViewMatrix", m_camera->viewMatrix());
    m_program.setUniformValue("u_ProjectionMatrix", m_camera->projectionMatrix());
    m_program.setUniformValue("u_opacity", m_opacity);
    m_program.setUniformValue("u_color", m_globalColor);
    m_program.setUniformValue("texture0", 0);

    m_program.setUniformValue("light_ambient_color", QColor(100, 100, 100));
    m_program.setUniformValue("light_diffuse_color", QColor(255, 255, 255));
    m_program.setUniformValue("light_specular_color", QColor(255, 255, 255));
    m_program.setUniformValue("light_specular_strength", 20.0f);
    m_program.setUniformValue("light_position", QVector3D(10, 0, 10));
    m_program.setUniformValue("eye_position", m_camera->position());

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

    QVector3D up(0, 1, 0);

    RVVertex vertexData[] = {
        RVVertex(A, SW, up),
        RVVertex(B, SE, up),
        RVVertex(C, NE, up),
        RVVertex(D, NW, up)
    };

    //Initialisation et remplissage du Vertex Buffer Object
    m_vbo.bind();
    m_vbo.allocate(vertexData, sizeof(vertexData));
    m_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vbo.release();

    m_numVertices = 4;
    m_numTriangles = 2;
}



