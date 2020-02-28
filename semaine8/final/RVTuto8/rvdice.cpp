#include "rvdice.h"

RVDice::RVDice()
    :RVTexCube()
{
    //m_VSFileName = ":/shaders/VS_cube_texture.vsh";
    //m_FSFileName = ":/shaders/FS_simple_texture.fsh";
    m_VSFileName = ":/shaders/VS_lit_texture_cube.vsh";
    m_FSFileName = ":/shaders/FS_lit_texture.fsh";
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

    //Définition des vecteurs normaux
    QVector3D Xp(1, 0, 0);
    QVector3D Xn(-1, 0, 0);
    QVector3D Yp(0, 1, 0);
    QVector3D Yn(0, -1, 0);
    QVector3D Zp(0, 0, 1);
    QVector3D Zn(0, 0, -1);

    //On prépare le tableau des données
    QVector3D vertexData[] = {
        A, B, C, D, //face avant = 1
        H, G, F, E, //face arriere = 6
        A, D, H, E, //face gauche = 2
        B, F, G, C, //face droite = 5
        D, C, G, H, //face dessus = 3
        A, E, F, B, //face dessous = 4
        rouge, rouge, rouge, rouge,
        cyan, cyan, cyan, cyan,
        vert, vert, vert, vert,
        magenta, magenta, magenta, magenta,
        bleu, bleu, bleu, bleu,
        jaune, jaune, jaune, jaune,
        QVector3D(0, 0.5f, 0), QVector3D(0.25f, 0.5f, 0), QVector3D(0.25f, 0.75f, 0), QVector3D(0, 0.75f, 0),
        QVector3D(0.5, 0.5f, 0), QVector3D(0.75f, 0.5f, 0), QVector3D(0.75f, 0.75f, 0), QVector3D(0.5, 0.75f, 0),
        QVector3D(0.75f, 0.5f, 0), QVector3D(1, 0.5f, 0), QVector3D(1, 0.75f, 0), QVector3D(0.75f, 0.75f, 0),
        QVector3D(0.25f, 0.5f, 0), QVector3D(0.5f, 0.5f, 0), QVector3D(0.5f, 0.75f, 0), QVector3D(0.25f, 0.75f, 0),
        QVector3D(0, 0.75f, 0), QVector3D(0.25f, 0.75f, 0), QVector3D(0.25f, 1, 0), QVector3D(0, 1, 0),
        QVector3D(0, 0.25f, 0), QVector3D(0.25f, 0.25f, 0), QVector3D(0.25f, 0.5f, 0), QVector3D(0, 0.5f, 0),
        Zp, Zp, Zp, Zp,
        Zn, Zn, Zn, Zn,
        Xn, Xn, Xn, Xn,
        Xp, Xp, Xp, Xp,
        Yp, Yp, Yp, Yp,
        Yn, Yn, Yn, Yn
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

void RVDice::update(float t)
{
    int vitAngulaire = 20; //en degré par seconde
    this->rotate(t*vitAngulaire*0.001, QVector3D(1, 1, 1));
    //this->translate(m_velocity*t*0.001);
}



