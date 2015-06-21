#include "carro.h"

void Carro::desenhar()
{
    beginDraw();

        glColor3d(1, 0, 0);

        Vetor3D begin = Vetor3D(-1.0, -0.3, -0.4);
        Vetor3D end = Vetor3D(1.0, 0.3, 0.4);

        Objeto::r.z = 0;
        Objeto::s = Vetor3D(1, 0.5, 2.5);
        Objeto::t = Vetor3D(0, 0, 0);
        Desenha::drawBox(begin.x, begin.y, begin.z, end.x, end.y, end.z);

        glPopMatrix();

    endDraw();
}

Carro::Carro()
{
}

Carro::~Carro()
{
}

