#include "rvmesh.h"

RVMesh::RVMesh()
    :RVBody()
{
    m_VSFileName = ":/shaders/VS_lit_texture.vsh";
    m_FSFileName = ":/shaders/FS_lit_texture.fsh";
}

RVMesh::~RVMesh()
{
    delete m_vertices;
    delete m_indices;
}

void RVMesh::initializeBuffer()
{
    m_vbo.bind();
    m_vbo.allocate(&m_vertices->at(0), m_numVertices*sizeof (RVVertex));
    m_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vbo.release();

    m_ibo.bind();
    m_ibo.allocate(&m_indices->at(0), m_numIndices*sizeof (uint));
    m_ibo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_ibo.release();
}

void RVMesh::draw()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (m_wireFrame)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glEnable(GL_CULL_FACE);

    if (m_texture) {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE0);
        glActiveTexture(GL_TEXTURE0);
        //m_texture->setWrapMode(QOpenGLTexture::ClampToEdge);
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

    m_program.setUniformValue("light_ambient_color", m_light->ambient());
    m_program.setUniformValue("light_diffuse_color", m_light->diffuse());
    m_program.setUniformValue("light_specular_color", m_light->specular());
    m_program.setUniformValue("light_position", m_light->position());
    m_program.setUniformValue("light_specular_strength", this->specStrength());

    m_program.setUniformValue("eye_position", m_camera->position());

    glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, nullptr);

    m_vao.release();
    m_program.release();

    if (m_texture) {
        m_texture->release();
        glDisable(GL_TEXTURE0);
        glDisable(GL_TEXTURE_2D);
    }
}

void RVMesh::setVertices(QVector<RVVertex> *vertices)
{
    m_vertices = vertices;
    m_numVertices = m_vertices->length();
}

void RVMesh::setIndices(QVector<uint> *indices)
{
    m_indices = indices;
    m_numIndices = m_indices->length();
}


