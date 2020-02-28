#include "rvwidget.h"

void RVWidget::update()
{
    m_angleY +=5;
    QOpenGLWidget::update();
}

RVWidget::RVWidget(QWidget *parent)
    : QOpenGLWidget(parent), QOpenGLFunctions(), m_angleY(0), m_angleX(0)
{
    m_timer = new QTimer();
}

RVWidget::~RVWidget()
{
}

void RVWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.566f, 0.867f, 1.0f);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    initializeBuffer();
    initializeShader();
    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
}

void RVWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_program.bind();
    m_vbo.bind();

    m_program.setAttributeBuffer("rv_Position", GL_FLOAT, 0, 3);
    m_program.enableAttributeArray("rv_Position");

    m_program.setAttributeBuffer("rv_Color", GL_FLOAT, sizeof(QVector3D)*24, 3);
    m_program.enableAttributeArray("rv_Color");

    QMatrix4x4 model, proj, view, matrix;

    //Définition de la matrice de projetcion
    proj.perspective(45, 1.33f, 0.1f, 100.0f);

    //Définiion de la matrice de vue
    view  = QMatrix4x4();

    //Définition de la matrice de placement
    model.translate(0, 0, -3);
    model.rotate(m_angleX,QVector3D(1,0,0));
    model.rotate(m_angleY,QVector3D(0,1,0));
    model.translate(-0.5, -0.5, -0.5);

    //Produit des trois matrices (dans ce sens!)
    matrix = proj * view * model;

    m_program.setUniformValue("u_ModelViewProjectionMatrix", matrix);
    for (int i = 0; i < 6; i++) {
        glDrawArrays(GL_TRIANGLE_FAN, i*4, 4);
    }

    m_vbo.release();
    m_program.release();
}

void RVWidget::resizeGL(int w, int h)
{
    //transformation de viewport
    glViewport(0, 0, w, h);
}

void RVWidget::initializeBuffer()
{
    //Définition de 4 points
    QVector3D A(0, 0, 1);
    QVector3D B(1, 0, 1);
    QVector3D C(1, 1, 1);
    QVector3D D(0, 1, 1);
    
    QVector3D E(0, 0, 0);
    QVector3D F(1, 0, 0);
    QVector3D G(1, 1, 0);
    QVector3D H(0, 1, 0);
    

    //Définition de 4 couleurs
    QVector3D rouge(1, 0, 0);
    QVector3D vert(0, 1, 0);
    QVector3D bleu(0, 0, 1);

    QVector3D magenta(1, 0, 1);
    QVector3D yellow(1, 1, 0);
    QVector3D cyan(0, 1, 1);

    //On prépare le tableau des données
    QVector3D vertexData[] = {
        A, B, C, D,
        B, F, G, C,
        A, E, F, B,
        E, H, G, F,
        A, D, H, E,
        C, G, H, D,

        yellow, yellow, yellow, yellow,
        magenta, magenta, magenta,magenta,
        cyan, cyan, cyan, cyan,
        vert, vert, vert, vert,
        rouge, rouge, rouge, rouge,
        bleu, bleu, bleu, bleu,
    };

    //Initialisation du Vertex Buffer Object
    m_vbo = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    //Création du VBO
    m_vbo.create();
    //Lien du VBO avec le contexte de rendu OpenGL
    m_vbo.bind();
    //Allocation des données dans le VBO
    m_vbo.allocate(vertexData, sizeof (vertexData));
    m_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    //Libération du VBO
    m_vbo.release();
}

void RVWidget::mousePressEvent(QMouseEvent *event)
{
    m_oldPos = event->pos();
}

void RVWidget::mouseMoveEvent(QMouseEvent *event)
{
    float dx, dy;
    dx = (m_oldPos.rx() - pos().rx())/width();
    dy = (m_oldPos.ry() - pos().ry())/height();
    m_angleX += dx*180;
    m_angleY += dy*180;
    m_oldPos = event->pos();
    QOpenGLWidget::update();
}

void RVWidget::initializeShader()
{
    bool resultat;
    m_program.create();
    m_program.bind();

    resultat = m_program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/VS_simple.vsh");
    if (!resultat){
        exit(1);
    }

    resultat = m_program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/FS_simple.fsh");
    if (!resultat){
        exit(1);
    }

    resultat = m_program.link();
    if (!resultat){
        exit(1);
    }

    m_program.release();
}

