#include "vetor3D.h"

Vetor3D::Vetor3D()
{

}

Vetor3D::Vetor3D(const Vetor3D& from)
{
    this->x = from.x;
    this->y = from.y;
    this->z = from.z;
    this->k = from.k;
}

Vetor3D::Vetor3D(const GLfloat &x, const GLfloat &y, const GLfloat z, const GLfloat k)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->k = k;
}

double Vetor3D::module()
{
    return sqrt( (this->x*this->x + this->y*this->y + this->z*this->z) );
}

Vetor3D Vetor3D::normalize()
{
    double mod = this->module();

    if(mod > 0){
        mod = 1.0/mod;

        this->x *= mod;
        this->y *= mod;
        this->z *= mod;
    }

    return *this;
}

Vetor3D Vetor3D::sum(Vetor3D vector)
{
    return Vetor3D(this->x + vector.x, this->y + vector.y, this->z + vector.z);
}

Vetor3D Vetor3D::subtract(Vetor3D vector)
{
    return Vetor3D(this->x - vector.x, this->y - vector.y, this->z - vector.z);
}

Vetor3D Vetor3D::multiply(double value)
{
    return Vetor3D(this->x * value, this->y * value, this->z * value);
}

double Vetor3D::getDistanceTo(Vetor3D vector)
{
    return ((*this) - vector).module();
}

Vetor3D Vetor3D::getVetorialProduct(Vetor3D vector)
{
    return Vetor3D(
                     this->y*vector.z - this->z*vector.y,
                     this->z*vector.x - this->x*vector.z,
                     this->x*vector.y - this->y*vector.x
                );
}

double Vetor3D::getEscalarProduct(float *values, int begin, int end)
{
    return this->x*values[begin]+this->y*values[begin+1]+this->z*values[begin+2]+this->k*values[begin+3];
}

double Vetor3D::getEscalarProduct(Vetor3D vector)
{
    return this->x*vector.x + this->y*vector.y + this->z*vector.z + this->k*vector.k;
}

Vetor3D Vetor3D::getUnitary()
{
    Vetor3D unitaryVector = *this;
    unitaryVector.normalize();

    return unitaryVector;
}

Vetor3D Vetor3D::getProjectionOn(Vetor3D vector)
{
    Vetor3D unitaryVector = vector.getUnitary();
    return unitaryVector * this->getEscalarProduct(unitaryVector);
}

Vetor3D Vetor3D::operator+(Vetor3D vector)
{
    return this->sum(vector);
}

Vetor3D Vetor3D::operator-(Vetor3D vector)
{
    return this->subtract(vector);
}

Vetor3D Vetor3D::operator*(double value)
{
    return this->multiply(value);
}

float Vetor3D::operator[](int i)
{
    switch(i){
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        case 3:
            return k;
    }
}


Vetor3D Vetor3D::multipliedByMatrix(float** values)
{
    float R[4] = {0, 0, 0, 0};

    for (int i = 0; i < 1; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                R[j] += (*this)[k] * values[k][j];
            }
        }
    }

    return Vetor3D(R[0], R[1], R[2], R[3]);
}

Vetor3D::~Vetor3D()
{

}
