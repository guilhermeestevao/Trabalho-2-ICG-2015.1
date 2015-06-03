#include "CatmullRom.h"
#include <Carrinho.h>

CatmullRom::CatmullRom()
{
    //ctor
}

CatmullRom::~CatmullRom()
{
    //dtor
}

void CatmullRom::desenhar(float pontos[4][3], float delta){

    float catmullrom[4][4] = {
            {-1,  3, -3,  1},
            { 2, -5,  4, -1},
            {-1,  0,  1,  0},
            { 0,  2,  0,  0} };


    float u[1][4];
    float ub[1][4];
    float ubp[1][3];

    glPushMatrix();
    glEnable(GL_LINE_SMOOTH);
        glLineWidth(2);

        glBegin(GL_LINES);
        glColor3d(0,1,0);

        for(float t=0; t<=1; t+=delta){

            memset(u,0,sizeof(u));
            memset(ub,0,sizeof(ub));
            memset(ubp, 0, sizeof(ubp));

            u[0][0] = t*t*t;
            u[0][1] = t*t;
            u[0][2] = t;
            u[0][3] = 1;


            for (int i=0; i<1; i++){
                for (int j=0; j<4; j++){
                    for(int k=0; k<4; k++){
                            ub[i][j]+= u[i][k] * catmullrom[k][j];
                    }
                }
            }

            for (int i=0; i<1; i++){
                for (int j=0; j<3; j++){
                    for(int k=0; k<4; k++){
                        ubp[i][j]+= ub[i][k] * pontos[k][j];
                    }
                }
            }

            // 1/2 = 0.5

            glVertex3d(ubp[0][0]*0.5, ubp[0][1]*0.5, ubp[0][2]*0.5);

    }

    glEnd();

    glDisable(GL_LINE_SMOOTH);
    glPopMatrix();

}









