#include "objeto.h"

std::vector<Objeto*> Objeto::itens;
int Objeto::lastX;
int Objeto::lastY;

Objeto::Objeto()
{
    this->selectedObject = -1;
    this->lastX = this->lastY = -1;
    this->s = Vetor3D(1, 1, 1);
    this->r = Vetor3D(0, 0, 0);
    this->t = Vetor3D(0, 0, 0);
}

Objeto::Objeto(Vetor3D begin, Vetor3D end)
{
    this->begin = begin;
    this->end = end;
}

void Objeto::beginDraw()
{
    glPushMatrix();

    glTranslated(t.x, t.y, t.z);
    glRotated(r.x, 1, 0, 0);
    glRotated(r.y, 0, 1, 0);
    glRotated(r.z, 0, 0, 1);
    glScaled(s.x, s.y, s.z);
}

void Objeto::endDraw()
{
    glPopMatrix();
}

bool Objeto::mouseClick(Camera *camera, Mouse *mouse)
{
    lastX = mouse->x;
    lastY = mouse->y;
}

bool Objeto::mouseMove(Camera *camera, Mouse *mouse)
{
    if(mouse->left && !mouse->middle && !mouse->right){
        rotate(camera, mouse);
    }else if(!mouse->left && !mouse->middle && mouse->right){
        translate(camera, mouse);
    }
}

bool Objeto::mouseWheel(Camera *camera, Mouse *mouse)
{
    this->scale(camera, mouse);
}

bool Objeto::translate(Camera *camera, Mouse *mouse)
{
    this->t = this->t + (camera->c - camera->e).getVetorialProduct(camera->u).normalize()*( (mouse->x - lastX)/100 );
    this->t = this->t + (camera->u.normalize() * ((lastY-mouse->y)/100));
    //std::cout << lastX << ", " << lastY << ", " << mouse->x << ", " << mouse->y << std::endl;
}

bool Objeto::rotate(Camera *camera, Mouse *mouse)
{
//    this->r.y += (mouse->x - lastX)/10;
}

bool Objeto::scale(Camera *camera, Mouse *mouse)
{
    this->s = this->s + this->s*(mouse->w);
}

void Objeto::key(Camera *camera, unsigned char key, int x, int y)
{

}

Vetor3D Objeto::transVertex(Vetor3D vec)
{
    return vec;
}

void Objeto::desenhar()
{

}

Objeto::~Objeto()
{

}

