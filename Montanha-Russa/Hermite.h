#ifndef HERMITE_H
#define HERMITE_H

#include <GL/glut.h>
#include <string.h>


class Hermite
{
    public:
        Hermite();
        ~Hermite();
        static void desenhar(float pontos[4][3], float delta);


    protected:
    private:
};

#endif // HERMITE_H
