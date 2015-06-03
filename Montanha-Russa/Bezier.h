#ifndef BEZIER_H
#define BEZIER_H

#include <GL/glut.h>
#include <string.h>


class Bezier
{
    public:
        Bezier();
        ~Bezier();
        static void desenhar(float pontos[4][3], float delta);

    protected:
    private:
};

#endif // BEZIER_H
