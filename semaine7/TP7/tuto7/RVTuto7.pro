#-------------------------------------------------
# Cours de Réalité Virtuelle
# leo.donati@univ-cotedazur.fr
#
# EPU 2019-20
#
# TP n°3
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    rvbb8.cpp \
    rvbody.cpp \
    rvbounce.cpp \
    rvcamera.cpp \
    rvcurve.cpp \
    rvdice.cpp \
    rvhelix.cpp \
    rvlight.cpp \
    rvmesh.cpp \
    rvmodel.cpp \
    rvplane.cpp \
    rvscene.cpp \
    rvskybox.cpp \
    rvsphere.cpp \
    rvsphericalcamera.cpp \
    rvstereocamera.cpp \
    rvsubjectivcamera.cpp \
    rvsurface.cpp \
    rvtexcube.cpp \
    rvtorus.cpp \
    rvwidget.cpp

HEADERS += \
    mainwindow.h \
    rvbb8.h \
    rvbody.h \
    rvbounce.h \
    rvcamera.h \
    rvcurve.h \
    rvdice.h \
    rvhelix.h \
    rvlight.h \
    rvmesh.h \
    rvmodel.h \
    rvplane.h \
    rvscene.h \
    rvskybox.h \
    rvsphere.h \
    rvsphericalcamera.h \
    rvstereocamera.h \
    rvsubjectivcamera.h \
    rvsurface.h \
    rvtexcube.h \
    rvtorus.h \
    rvwidget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    FS_plan.fsh \
    FS_simple.fsh \
    VS_simple.vsh \
    VS_simple_texture.vsh \
    VS_simpler.vsh

RESOURCES += \
    RVResources.qrc

FORMS += \
    mainwindow.ui

windows:LIBS += -lopengl32

macx: LIBS += -L$$PWD/../../../Projects/assimp-master/lib/Release/ -lassimp.5.0.1

INCLUDEPATH += $$PWD/../../../../../Projects/assimp-master/include
DEPENDPATH += $$PWD/../../../Projects/assimp-master/include

unix:!macx: LIBS += -L$$PWD/../../../../../git-project/assimp/lib/ -lassimp

INCLUDEPATH += $$PWD/../../../../../git-project/assimp/include
DEPENDPATH += $$PWD/../../../../../git-project/assimp/include
