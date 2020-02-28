#include "rvcurve.h"

RVCurve::RVCurve()
    :RVBody()
{
    m_minT = 0;
    m_maxT = 1;
    m_numSeg = 100;
    m_lineWidth = 2;
}

void RVCurve::draw()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glLineWidth(m_lineWidth);
    //glLineStipple() //à regarder comment ça fonctionne ?
    glDisable(GL_CULL_FACE);

    m_program.bind();
    m_vao.bind();

    QMatrix4x4 matrix;
    matrix = m_camera->projectionMatrix() * m_camera->viewMatrix() * this->modelMatrix();
    m_program.setUniformValue("u_ModelViewProjectionMatrix", matrix);
    m_program.setUniformValue("u_opacity", m_opacity);
    m_program.setUniformValue("u_color", m_globalColor);

    glDrawArrays(GL_LINE_STRIP, 0, m_numSeg+1);

    m_vao.release();
    m_program.release();
}

void RVCurve::initializeBuffer()
{
    m_numVertices = m_numSeg + 1;

    QVector3D* vertexData = new QVector3D[m_numVertices];
    double t = m_minT;
    double deltaT = (m_maxT - m_minT)/m_numSeg;
    for (int i = 0; i <= m_numSeg; i++, t += deltaT) {
        vertexData[i] = pos(t);
    }

    //remplissage du Vertex Buffer Object
    m_vbo.bind();
    m_vbo.allocate(vertexData, m_numVertices * int(sizeof(QVector3D)));
    m_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vbo.release();
}

void RVCurve::initializeVAO()
{
    //Initialisation du VAO
    m_vao.bind();
    m_vbo.bind();
    m_ibo.bind();

    //Définition du seul attribut position (la couleur est uniforme avec le VS_simpler)
    m_program.setAttributeBuffer("rv_Position", GL_FLOAT, 0, 3);
    m_program.enableAttributeArray("rv_Position");

    //Libération
    m_vao.release();
    m_program.release();
}

float RVCurve::lineWidth() const
{
    return m_lineWidth;
}

void RVCurve::setLineWidth(float lineWidth)
{
    m_lineWidth = lineWidth;
}

int RVCurve::numSeg() const
{
    return m_numSeg;
}

void RVCurve::setNumSeg(int numSeg)
{
    m_numSeg = numSeg;
}


double RVCurve::minT() const
{
    return m_minT;
}

void RVCurve::setMinT(double minT)
{
    m_minT = minT;
}

double RVCurve::maxT() const
{
    return m_maxT;
}

void RVCurve::setMaxT(double maxT)
{
    m_maxT = maxT;
}

