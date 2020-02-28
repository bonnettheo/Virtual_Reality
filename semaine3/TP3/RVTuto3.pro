#-------------------------------------------------
# Cours de Réalité Virtuelle
# leo.donati@univ-cotedazur.fr
#
# EPU 2019-20
#
# Tutoriel n°3
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    rvbody.cpp \
    rvcamera.cpp \
    rvcube.cpp \
    rvdice.cpp \
    rvplane.cpp \
    rvscene.cpp \
    rvskybox.cpp \
    rvsphere.cpp \
    rvsphericalcamera.cpp \
    rvsurface.cpp \
    rvtexcube.cpp \
    rvtorus.cpp \
    rvwidget.cpp

HEADERS += \
    mainwindow.h \
    rvbody.h \
    rvcamera.h \
    rvcube.h \
    rvdice.h \
    rvplane.h \
    rvscene.h \
    rvskybox.h \
    rvsphere.h \
    rvsphericalcamera.h \
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
    VS_cube_texture.vsh \
    VS_simple.vsh \
    VS_simple_texture.vsh \
    VS_simpler.vsh

RESOURCES += \
    RVResources.qrc

FORMS += \
    mainwindow.ui

windows:LIBS += -lopengl32
