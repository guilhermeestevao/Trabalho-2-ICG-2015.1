#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>

class Vetor3D
{
public:

    GLfloat x, y, z, k;
    Vetor3D();
    Vetor3D(const Vetor3D& from);
    Vetor3D(const GLfloat& x, const GLfloat& y, const GLfloat z, const GLfloat k = 1);

    double module();
    Vetor3D normalize();

    Vetor3D sum(Vetor3D vector);
    Vetor3D subtract(Vetor3D vector);
    Vetor3D multiply(double value);
    double getDistanceTo(Vetor3D vector);
    Vetor3D getVetorialProduct(Vetor3D vector);
    double getEscalarProduct(float* values, int begin, int end);
    double getEscalarProduct(Vetor3D vector);
    Vetor3D getUnitary();
    Vetor3D getProjectionOn(Vetor3D vector);
    Vetor3D operator+(Vetor3D vector);
    Vetor3D operator-(Vetor3D vector);
    Vetor3D operator*(double value);
    float operator[](int);
    Vetor3D multipliedByMatrix(float** values);

    ~Vetor3D();
};

#endif // VECTOR3D_H
