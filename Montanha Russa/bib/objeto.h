#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "GL/gl.h"
#include "GL/glu.h"
#include "camera.h"
#include "mouse.h"
#include <iostream>
#include <stdio.h>
#include <vector>
#include "vetor3D.h"

#define CLICK 1
#define MOVE 1

class Objeto
{
public:
    static std::vector<Objeto*> itens;
    Vetor3D t, r, s;
    Vetor3D begin, end;
    int selectedObject;
    void beginDraw();
    void endDraw();

    static int lastX;
    static int lastY;

    virtual bool mouseClick(Camera* camera, Mouse* mouse);
    virtual bool mouseMove(Camera* camera, Mouse* mouse);
    virtual bool mouseWheel(Camera* camera, Mouse* mouse);
    virtual bool translate(Camera* camera, Mouse* mouse);
    virtual bool rotate(Camera* camera, Mouse* mouse);
    virtual bool scale(Camera* camera, Mouse* mouse);
    virtual void key(Camera* camera, unsigned char key, int x, int y);
    Vetor3D transVertex(Vetor3D vec);

    virtual void desenhar();
    bool showAxes;
    bool selected;

    Objeto();
    Objeto(Vetor3D begin, Vetor3D end);
    ~Objeto();

};

#endif // OBJECT3D_H
