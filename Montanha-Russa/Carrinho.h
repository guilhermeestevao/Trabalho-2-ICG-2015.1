#ifndef CARRINHO_H
#define CARRINHO_H

#include <GL/glut.h>
#include <string.h>
#include <bib/Desenha.h>


class Carrinho
{
    public:

        Carrinho();
        ~Carrinho();
        void percorrer(float& x, float& y, float& z);
        void desenhar(float size, float x, float y, float z);

    protected:
    private:
};

#endif // CARRINHO_H
