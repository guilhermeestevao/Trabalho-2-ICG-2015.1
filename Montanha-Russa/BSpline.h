#ifndef BSPLINE_H
#define BSPLINE_H

#include <GL/glut.h>
#include <string.h>

class BSpline
{
    public:
        BSpline();
        ~BSpline();
        static void desenhar(float pontos[4][3], float delta);

    protected:
    private:
};

#endif // BSPLINE_H
