#include "Carrinho.h"

Carrinho::Carrinho()
{

}

Carrinho::~Carrinho()
{
    //dtor
}

void Carrinho::percorrer(float& x, float& y, float& z){

            desenhar(0.2, x, y, z);
}


void Carrinho::desenhar(float size, float x, float y, float z){

    glPushMatrix();
        glTranslated(x,y,z);
        glScaled(size,size,size);


        glPushMatrix();
            glColor3d(1,0,0);
            Desenha::drawBox(0,0,0,4,1,2);
        glPopMatrix();

        glPushMatrix();
            glTranslated(1,0,0);
            glColor3d(0,0,0);
            glutSolidSphere(0.4,20,20);
        glPopMatrix();

        glPushMatrix();
            glTranslated(3,0,0);
            glColor3d(0,0,0);
            glutSolidSphere(0.4,20,20);
        glPopMatrix();

        glPushMatrix();
            glTranslated(1,0,2);
            glColor3d(0,0,0);
            glutSolidSphere(0.4,20,20);
        glPopMatrix();

        glPushMatrix();
            glTranslated(3,0,2);
            glColor3d(0,0,0);
            glutSolidSphere(0.4,20,20);
        glPopMatrix();

        glPushMatrix();
            glTranslated(0.1,0.5,0.5);
            glColor3d(1,1,1);
            glutSolidSphere(0.25,20,20);
        glPopMatrix();

        glPushMatrix();
            glTranslated(0.1,0.5,1.5);
            glColor3d(1,1,1);
            glutSolidSphere(0.25,20,20);
        glPopMatrix();
    glPopMatrix();

}


