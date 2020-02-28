#-------------------------------------------------
# Cours de Réalité Virtuelle
# leo.donati@univ-cotedazur.fr
#
# EPU 2019-20
#
# Tutoriel n°2
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
    rvplane.cpp \
    rvpyramid.cpp \
    rvwidget.cpp

HEADERS += \
    mainwindow.h \
    rvbody.h \
    rvcamera.h \
    rvcube.h \
    rvplane.h \
    rvpyramid.h \
    rvwidget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    FS_plan.fsh \
    FS_simple.fsh \
    VS_simple.vsh \
    VS_simpler.vsh

RESOURCES += \
    RVResources.qrc

FORMS += \
    mainwindow.ui

# Nécessaie sous windows pour faire de l'OpenGL
windows:LIBS += -lopengl32
