#ifndef RVLIGHT_H
#define RVLIGHT_H

#include <QVector3D>
#include <QColor>



class RVLight
{
public:
    RVLight(QVector3D light_pos = QVector3D(10, 0, 10),
            QColor ambient = QColor(100, 100, 100),
            QColor diffuse = QColor(255, 255, 255),
            QColor specular = QColor(255, 255, 255)
            );

    QColor ambient() const;
    void setAmbient(const QColor &ambient);

    QColor diffuse() const;
    void setDiffuse(const QColor &diffuse);

    QColor specular() const;
    void setSpecular(const QColor &specular);

protected:
    QVector3D m_position;
    QColor m_ambient;
    QColor m_diffuse;
    QColor m_specular;


};

#endif // RVLIGHT_H
