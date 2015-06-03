#ifndef CATMULLROM_H
#define CATMULLROM_H

#include <GL/glut.h>
#include <string.h>
#include <stdio.h>


class CatmullRom
{
    public:
        CatmullRom();
        ~CatmullRom();

        static void desenhar(float pontos[4][3], float delta);



    protected:
    private:
};

#endif // CATMULLROM_H
