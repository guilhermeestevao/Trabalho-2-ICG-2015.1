TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += \
    bib/Camera.h \
    bib/CameraDistante.h \
    bib/CameraJogo.h \
    bib/Desenha.h \
    bib/Vetor3D.h \
    bib/stanfordbunny.h \
    Bezier.h \
    BSpline.h \
    Carrinho.h \
    CatmullRom.h \
    Hermite.h \
    Skybox.h \

SOURCES += \
    bib/Camera.cpp \
    bib/CameraDistante.cpp \
    bib/CameraJogo.cpp \
    bib/Desenha.cpp \
    bib/Vetor3D.cpp \
    Bezier.cpp \
    BSpline.cpp \
    Carrinho.cpp \
    CatmullRom.cpp \
    Hermite.cpp \
    Skybox.cpp \
    main.cpp \

DEFINES += USE_SDL
LIBS += -lglut -lgsl -l3ds -lGLU -lGL -lm -lSDL -lSDL_image
#LIBS += -lGL -lGLU -lglut

include(deployment.pri)
qtcAddDeployment()

