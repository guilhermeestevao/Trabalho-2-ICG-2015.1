#include "Bezier.h"

Bezier::Bezier()
{
    //ctor
}

Bezier::~Bezier()
{
    //dtor
}

void Bezier::desenhar(float pontos[4][3], float delta){

    float bezier[4][4] = {
            { 1.0,   0.0,   0.0,  0.0},
            {-3.0,   3.0,   0.0,  0.0},
            { 3.0,  -6.0,   3.0,  0.0},
            {-1.0,   3.0,  -3.0,  1.0} };


    float u[1][4];
    float ub[1][4];
    float ubp[1][3];

    glEnable(GL_LINE_SMOOTH);
        glLineWidth(3);

        glBegin(GL_LINE_STRIP);
        glColor3d(0,0,1);

        for(float t=0; t<=1; t+=delta){

            u[0][0] = 1;
            u[0][1] = t;
            u[0][2] = t*t;
            u[0][3] = t*t*t;

            //memset(u,0,sizeof(u));
            memset(ub,0,sizeof(ub));
            memset(ubp, 0, sizeof(ubp));

            for (int i=0; i<1; i++){
                for (int j=0; j<4; j++){
                    for(int k=0; k<4; k++){
                            ub[i][j]+= u[i][k] * bezier[k][j];
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

            glVertex3d(ubp[0][0], ubp[0][1], ubp[0][2]);

    }

    glEnd();

    glDisable(GL_LINE_SMOOTH);

}
