#ifndef CAMERA_H
#define CAMERA_H

#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "vetor3D.h"

class Camera
{
public:
    Vetor3D e, c, u;
    Camera();
    Camera(Vetor3D e, Vetor3D c, Vetor3D u);
    Camera(GLfloat ex, GLfloat ey, GLfloat ez, GLfloat cx, GLfloat cy, GLfloat cz, GLfloat ux, GLfloat uy, GLfloat uz);
    ~Camera();

    void zoom(GLfloat zoomLevel);
    void translateX(GLfloat newX, GLfloat lastX);
    void translateY(GLfloat newY, GLfloat lastY);
    void rotateX(GLfloat newX, GLfloat lastX);
    void rotateY(GLfloat newY, GLfloat lastY);
    void rotateZ(GLfloat newX, GLfloat lastX);
    Vetor3D getPickedPoint(GLfloat x, GLfloat y);

    void draw(float scale = 1);
};

#endif // CAMERA_H
