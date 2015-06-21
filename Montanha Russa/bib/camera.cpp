#include "camera.h"

Camera::Camera()
{
  e = Vetor3D(0, 15, 50);
  c = Vetor3D(0, 0, 0);
  u = Vetor3D(0, 1, 0);
}

Camera::Camera(Vetor3D e, Vetor3D c, Vetor3D u)
{
    this->e = e;
    this->c = c;
    this->u = u;
}

Camera::Camera(GLfloat ex, GLfloat ey, GLfloat ez, GLfloat cx, GLfloat cy, GLfloat cz, GLfloat ux, GLfloat uy, GLfloat uz)
{
    this->e = Vetor3D(ex, ey, ez);
    this->c = Vetor3D(cx, cy, cz);
    this->u = Vetor3D(ux, uy, uz);
}

Camera::~Camera()
{

}

void Camera::zoom(GLfloat zoomLevel)
{
    Vetor3D be = c - e;
    be.normalize();
    be = be * zoomLevel;

    e = be + e;
}

void Camera::translateX(GLfloat newX, GLfloat lastX)
{
    Vetor3D eyeToCenter = c - e;
    Vetor3D whereTrans = e.getVetorialProduct(u);
    whereTrans.normalize();
    whereTrans = whereTrans * (eyeToCenter.module() * (newX - lastX)/500);

    this->e = this->e + whereTrans;
    this->c = this->c + whereTrans;
}

void Camera::translateY(GLfloat newY, GLfloat lastY)
{
    Vetor3D eyeToCenter = c - e;
    Vetor3D whereTrans = e.getVetorialProduct(eyeToCenter.getVetorialProduct(u));
    whereTrans.normalize();

    whereTrans = whereTrans * (eyeToCenter.module() * (newY - lastY)/500);

    this->e = this->e + whereTrans;
    this->c = this->c + whereTrans;
}

void Camera::rotateX(GLfloat newX, GLfloat lastX)
{
    Vetor3D pe = e;
    Vetor3D xc = (c-e).getVetorialProduct(u);

    Vetor3D whereSpin = u;
    whereSpin = whereSpin * (e.module()*(newX-lastX)/200);
    e = e + whereSpin;

    e = e-c;
    e.normalize();
    e = e*(pe-c).module();
    e = e+c;
}

void Camera::rotateY(GLfloat newY, GLfloat lastY)
{
    Vetor3D pe = e;

    Vetor3D eyeToCenter = c-e;
    Vetor3D whereSpin = eyeToCenter.getVetorialProduct(u);

    whereSpin.normalize();
    whereSpin = whereSpin*(e.module()*(lastY-newY)/200);
    e = whereSpin + e;

    e = e-c;
    e.normalize();
    e = e*(pe-c).module();
    e = e+c;

}

void Camera::rotateZ(GLfloat newX, GLfloat lastX)
{
    Vetor3D pu = u;

    Vetor3D eyeToCenter = c-e;
    Vetor3D whereSpin = eyeToCenter.getVetorialProduct(u);

    whereSpin.normalize();
    whereSpin = whereSpin*(e.module()*(lastX-newX)/20000);
    u = whereSpin + u;

    u = u-c;
    u.normalize();
    u = u*(pu-c).module();
    u = u+c;
}

Vetor3D Camera::getPickedPoint(GLfloat x, GLfloat y)
{

}

void Camera::draw(float scale)
{

}
