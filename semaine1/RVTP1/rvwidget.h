#ifndef RVWIDGET_H
#define RVWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QVector3D>
#include <QOpenGLShaderProgram>
#include <QTimer>
#include <QMouseEvent>

class RVWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
    QOpenGLBuffer m_vbo;
    QOpenGLShaderProgram m_program;
    float m_angleY;
    float m_angleX;
    QTimer *m_timer;
    QPoint m_oldPos;
private slots:
    void update();

public:
    RVWidget(QWidget *parent = nullptr);
    ~RVWidget() override;
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
    void initializeBuffer();
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

protected :
    void initializeShader();
};
#endif // RVWIDGET_H
