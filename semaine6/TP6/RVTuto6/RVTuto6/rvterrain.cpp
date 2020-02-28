#include "rvterrain.h"

RVTerrain::RVTerrain(double width)
    :RVSurface()
{
    m_minS = -width/2;
    m_maxS = +width/2;
    m_minT = -width/2;
    m_maxT = +width/2;
    m_numSegS = 50;
    m_numSegT = 50;

    m_VSFileName = ":/shaders/VS_heightmap.vsh";
}

QOpenGLTexture *RVTerrain::heightmap() const
{
    return m_heightmap;
}

void RVTerrain::setHeightmap(QString textureFilename)
{
    m_heightmap = new QOpenGLTexture(QImage(textureFilename).mirrored());
}

void RVTerrain::draw()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (m_wireFrame)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glDisable(GL_CULL_FACE);

    if (m_heightmap) {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE0);
        m_heightmap->setWrapMode(QOpenGLTexture::ClampToEdge);
        m_heightmap->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        m_heightmap->setMagnificationFilter(QOpenGLTexture::Linear);
        //Liaison de la texture
        m_heightmap->bind();
    }

    m_program.bind();
    m_vao.bind();

    m_program.setUniformValue("u_ModelMatrix", this->modelMatrix());
    m_program.setUniformValue("u_ViewMatrix", m_camera->viewMatrix());
    m_program.setUniformValue("u_ProjectionMatrix", m_camera->projectionMatrix());
    m_program.setUniformValue("u_opacity", m_opacity);
    m_program.setUniformValue("u_color", m_globalColor);
    m_program.setUniformValue("texture0", 0);

    m_program.setUniformValue("light_ambient_color", m_light->ambient());
    m_program.setUniformValue("light_diffuse_color", m_light->diffuse());
    m_program.setUniformValue("light_specular_color", m_light->specular());
    m_program.setUniformValue("light_position", m_light->position());
    m_program.setUniformValue("light_specular_strength", this->specStrength());
    m_program.setUniformValue("u_height_factor", this->heightFactor);

    m_program.setUniformValue("eye_position", m_camera->position());

    glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, nullptr);

    m_vao.release();
    m_program.release();

    if (m_heightmap) {
        m_heightmap->release();
        glDisable(GL_TEXTURE0);
        glDisable(GL_TEXTURE_2D);
    }
}

void RVTerrain::initializeBuffer()
{
    m_numVertices = (m_numSegS + 1) * (m_numSegT + 1);
    m_numTriangles = 2 * m_numSegS * m_numSegT;
    m_numIndices = 3 * m_numTriangles;

    RVVertex * vertexData = new RVVertex [m_numVertices];
    uint* indexData = new uint[m_numIndices];
    double t = m_minT;
    double s = m_minS;
    double deltaT = (m_maxT - m_minT)/m_numSegT;
    double deltaS = (m_maxS - m_minS)/m_numSegS;
    uint cptPoint = 0;
    uint cptIndex = 0;
    for (int i = 0; i <= m_numSegT; i++, t += deltaT) {
        s = m_minS;
        for (int j = 0; j <= m_numSegS; j++, s += deltaS, cptPoint++) {
            vertexData[cptPoint].position = pos(s,t);
            vertexData[cptPoint].texCoord = QVector2D(j/float(m_numSegS),-0.0+1.0f*i/float(m_numSegT));
            vertexData[cptPoint].normal = normal(s,t);
            if ((i < m_numSegT) && (j < m_numSegS)) {
                indexData[cptIndex++] = cptPoint;
                indexData[cptIndex++] = cptPoint + uint(m_numSegS) + 1;
                indexData[cptIndex++] = cptPoint + uint(m_numSegS) + 2;
                indexData[cptIndex++] = cptPoint;
                indexData[cptIndex++] = cptPoint + uint(m_numSegS) + 2;
                indexData[cptIndex++] = cptPoint + 1;
            }
        }
    }

    //Initialisation et remplissage du Vertex Buffer Object
    m_vbo = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vbo.create();
    m_vbo.bind();
    m_vbo.allocate(vertexData, m_numVertices*int(sizeof (RVVertex)));
    m_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vbo.release();

    //Initialisation et remplissage de l'Index Buffer Object
    m_ibo = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    m_ibo.create();
    m_ibo.bind();
    m_ibo.allocate(indexData, m_numIndices*int(sizeof (uint)));
    m_ibo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_ibo.release();
}

float RVTerrain::x(double s, double t)
{
    return s;
}
float RVTerrain::y(double s, double t)
{
    return 0;
}
float RVTerrain::z(double s, double t)
{
    return t;
}
