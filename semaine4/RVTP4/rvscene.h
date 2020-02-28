#ifndef RVSCENE_H
#define RVSCENE_H

#include <QList>
#include "rvbody.h"

//On pourrait ajouter à scene un background et un hud !
//En fait on lui passe les noms des textures et c'est tout!!

class RVScene : public QList<RVBody*>
{
public:
    RVScene();
    ~RVScene();

    void setCamera(RVCamera* camera);
    void translate(QVector3D vec);
    void rotate(float, QVector3D);
    void draw();
    void setSpecCoeff(float coeff);

protected:
    RVCamera* m_camera;
};

#endif // RVSCENE_H
