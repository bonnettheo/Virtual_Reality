#include "rvdice.h"

RVDice::RVDice()
    :RVBody()
{
    m_VSFileName = ":/shaders/VS_cube_texture.vsh";
    m_FSFileName = ":/shaders/FS_simple_texture.fsh";
}

void RVDice::draw()
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

    QMatrix4x4 matrix;
    matrix = m_camera->projectionMatrix() * m_camera->viewMatrix() * this->modelMatrix();
    m_program.setUniformValue("u_ModelViewProjectionMatrix", matrix);
    m_program.setUniformValue("u_color", m_globalColor);
    m_program.setUniformValue("u_opacity", m_opacity);
    m_program.setUniformValue("texture0", 0);

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

void RVDice::initializeBuffer()
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

    QVector3D SW(0, 0, 0);
    QVector3D SE(1, 0, 0);
    QVector3D NE(1, 1, 0);
    QVector3D NW(0, 1, 0);

    QVector3D f1_origin = QVector3D(0, 0.5, 0);
    QVector3D SW_f1 = SW*0.25+f1_origin;
    QVector3D SE_f1 = SE*0.25+f1_origin;
    QVector3D NE_f1 = NE*0.25+f1_origin;;
    QVector3D NW_f1 = NW*0.25+f1_origin;

    QVector3D f2_origin = QVector3D(0.75, 0.5, 0);
    QVector3D SW_f2 = SW*0.25+f2_origin;
    QVector3D SE_f2 = SE*0.25+f2_origin;
    QVector3D NE_f2 = NE*0.25+f2_origin;;
    QVector3D NW_f2 = NW*0.25+f2_origin;

    QVector3D f3_origin = QVector3D(0, 0.75, 0);
    QVector3D SW_f3 = SW*0.25+f3_origin;
    QVector3D SE_f3 = SE*0.25+f3_origin;
    QVector3D NE_f3 = NE*0.25+f3_origin;;
    QVector3D NW_f3 = NW*0.25+f3_origin;

    QVector3D f4_origin = QVector3D(0, 0.25, 0);
    QVector3D SW_f4 = SW*0.25+f4_origin;
    QVector3D SE_f4 = SE*0.25+f4_origin;
    QVector3D NE_f4 = NE*0.25+f4_origin;;
    QVector3D NW_f4 = NW*0.25+f4_origin;

    QVector3D f5_origin = QVector3D(0.25, 0.5, 0);
    QVector3D SW_f5 = SW*0.25+f5_origin;
    QVector3D SE_f5 = SE*0.25+f5_origin;
    QVector3D NE_f5 = NE*0.25+f5_origin;;
    QVector3D NW_f5 = NW*0.25+f5_origin;

    QVector3D f6_origin = QVector3D(0.5, 0.5, 0);
    QVector3D SW_f6 = SW*0.25+f6_origin;
    QVector3D SE_f6 = SE*0.25+f6_origin;
    QVector3D NE_f6 = NE*0.25+f6_origin;;
    QVector3D NW_f6 = NW*0.25+f6_origin;
    //On prépare le tableau des données
    QVector3D vertexData[] = {
        A, B, C, D, //face avant
        F, E, H, G, //face arriere
        E, A, D, H, //face gauche
        B, F, G, C, //face droite
        D, C, G, H, //face dessus
        E, F, B, A, //face dessous
        rouge, rouge, rouge, rouge,
        cyan, cyan, cyan, cyan,
        vert, vert, vert, vert,
        magenta, magenta, magenta, magenta,
        bleu, bleu, bleu, bleu,
        jaune, jaune, jaune, jaune,
        SW_f1, SE_f1, NE_f1, NW_f1,
        SW_f6, SE_f6, NE_f6, NW_f6,
        SW_f3, SE_f3, NE_f3, NW_f3,
        SW_f4, SE_f4, NE_f4, NW_f4,
        SW_f5, SE_f5, NE_f5, NW_f5,
        SW_f2, SE_f2, NE_f2, NW_f2,
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

QMatrix4x4 RVDice::modelMatrix()
{
    QMatrix4x4 model;
    model.translate(-0.5f, -0.5f, -0.5f);
    return RVBody::modelMatrix() * model;
}

void RVDice::initializeVAO()
{
    //Initialisation du VAO
    m_vao.bind();
    m_vbo.bind();

    //Définition des attributs
    m_program.setAttributeBuffer("rv_Position", GL_FLOAT, 0, 3);
    m_program.enableAttributeArray("rv_Position");

    //Définition de l'attribut de coordonnée texture
    m_program.setAttributeBuffer("rv_TexCoord", GL_FLOAT, sizeof(QVector3D)*6*2*4, 3);
    m_program.enableAttributeArray("rv_TexCoord");

    m_program.setAttributeBuffer("rv_Color", GL_FLOAT, sizeof(QVector3D)*24, 3);
    m_program.enableAttributeArray("rv_Color");

    //Libération
    m_vao.release();
    m_program.release();
}

