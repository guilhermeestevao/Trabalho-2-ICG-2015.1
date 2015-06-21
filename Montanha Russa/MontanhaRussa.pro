TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lGL -lGLU -lglut -lSDL_image

SOURCES += main.cpp \
    bib/camera.cpp \
    bib/mouse.cpp \
    bib/desenha.cpp \
    montanharussa.cpp \
    carro.cpp \
    bib/vetor3D.cpp \
    bib/objeto.cpp \
    trilho.cpp \
    bib/view.cpp


include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    bib/camera.h \
    bib/mouse.h \
    bib/desenha.h \
    bib/vetor3D.h \
    montanharussa.h \
    carro.h \
    bib/objeto.h \
    trilho.h \
    bib/view.h

