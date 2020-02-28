#include "rvtexcube.h"

RVTexCube::RVTexCube()
    :RVBody()
{
    m_VSFileName = ":/shaders/VS_lit_texture_cube.vsh";
    m_FSFileName = ":/shaders/FS_lit_texture.fsh";
}

void RVTexCube::draw()
{
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (m_wireFrame)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if (m_culling)
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);

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

    m_program.setUniformValue("light_ambient_color", m_light->ambient()); //QColor(100, 100, 100));
    m_program.setUniformValue("light_diffuse_color", m_light->diffuse()); //QColor(255, 255, 255));
    m_program.setUniformValue("light_specular_color", m_light->specular()); //QColor(255, 255, 255));
    m_program.setUniformValue("light_specular_strength", m_specStrength);
    m_program.setUniformValue("light_position", m_light->position()); //QVector3D(10, 0, 10));
    m_program.setUniformValue("eye_position", m_camera->position());

    for (int i = 0; i<6; i++)
        glDrawArrays(GL_TRIANGLE_FAN, 4*i, 4);

    m_vao.release();
    m_program.release();

    if (m_texture) {
        m_texture->release();
        glDisable(GL_TEXTURE0);
        glDisable(GL_TEXTURE_2D);
    }
}

void RVTexCube::initializeBuffer()
{
    //Definitions des 8 sommets du cube
    QVector3D A(0, 0, 1);
    QVector3D B(1, 0, 1);
    QVector3D C(1, 1, 1);
    QVector3D D(0, 1, 1);
    QVector3D E(0, 0, 0);
    QVector3D F(1, 0, 0);
    QVector3D G(1, 1, 0);
    QVector3D H(0, 1, 0);

    //Définitions des 6 couleurs primaires
    QVector3D rouge(1, 0, 0);
    QVector3D vert(0, 1, 0);
    QVector3D bleu(0, 0, 1);
    QVector3D cyan(0, 1, 1);
    QVector3D magenta(1, 0, 1);
    QVector3D jaune(1, 1, 0);

    //Définition des coordonnées textures des coins
    QVector3D SW(0, 0, 0);
    QVector3D SE(1, 0, 0);
    QVector3D NE(1, 1, 0);
    QVector3D NW(0, 1, 0);


    //Normal vectors
    QVector3D front = QVector3D(0, 0, 1);
    QVector3D back = QVector3D(0, 0, -1);
    QVector3D right = QVector3D(1, 0, 0);
    QVector3D left = QVector3D(-1, 0, 0);
    QVector3D down = QVector3D(0, -1, 0);
    QVector3D up = QVector3D(0, 1, 0);


    //On prépare le tableau des données
    QVector3D vertexData[] = {
        A, B, C, D, //face avant
        H, G, F, E, //face arriere
        A, D, H, E, //face gauche
        B, F, G, C, //face droite
        D, C, G, H, //face dessus
        A, E, F, B, //face dessous
        rouge, rouge, rouge, rouge,
        cyan, cyan, cyan, cyan,
        vert, vert, vert, vert,
        magenta, magenta, magenta, magenta,
        bleu, bleu, bleu, bleu,
        jaune, jaune, jaune, jaune,
        SW, SE, NE, NW,
        SW, SE, NE, NW,
        SW, SE, NE, NW,
        SW, SE, NE, NW,
        SW, SE, NE, NW,
        SW, SE, NE, NW,
        front, front, front, front,
        back, back, back, back,
        left, left, left, left,
        right, right, right, right,
        up, up, up, up,
        down, down, down, down
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

QMatrix4x4 RVTexCube::modelMatrix()
{
    QMatrix4x4 model;
    model.translate(-0.5f, -0.5f, -0.5f);
    return RVBody::modelMatrix() * model;
}

void RVTexCube::initializeVAO()
{
    //Initialisation du VAO
    m_vao.bind();
    m_vbo.bind();

    //Définition du seul attribut position (la couleur est uniforme avec le VS_simpler)
    m_program.setAttributeBuffer("rv_Position", GL_FLOAT, 0, 3);
    m_program.enableAttributeArray("rv_Position");

    m_program.setAttributeBuffer("rv_Color", GL_FLOAT, sizeof(QVector3D)*24, 3);
    m_program.enableAttributeArray("rv_Color");

    //Définition de l'attribut de coordonnée texture
    m_program.setAttributeBuffer("rv_TexCoord", GL_FLOAT, sizeof(QVector3D) * 48, 3);
    m_program.enableAttributeArray("rv_TexCoord");

    //Définition de l'attribut de coordonnée vecteur normal
    m_program.setAttributeBuffer("rv_Normal", GL_FLOAT, sizeof(QVector3D) * 72, 3);
    m_program.enableAttributeArray("rv_Normal");

    //Libération
    m_vao.release();
    m_program.release();
}

