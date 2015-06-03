#include "BSpline.h"

BSpline::BSpline()
{
    //ctor
}

BSpline::~BSpline()
{
    //dtor
}

void BSpline::desenhar(float pontos[4][3], float delta){
     float u[1][4];
    float ub[1][4];
    float ubp[1][3];

    float bspline[4][4] = {
            { -1,  3,  -3,  1},
            {  3, -6,   3,  0},
            { -3,  0,   3,  0},
            {  1,  4,   1,  0} };

    glEnable(GL_LINE_SMOOTH);
        glLineWidth(3);

        glBegin(GL_LINE_STRIP);
        glColor3d(0,1,1);

        for(float t=0; t<=1; t+=delta){

            u[0][0] = t*t*t;
            u[0][1] = t*t;
            u[0][2] = t;
            u[0][3] = 1;

            //memset(u,0,sizeof(u));
            memset(ub,0,sizeof(ub));
            memset(ubp, 0, sizeof(ubp));

            for (int i=0; i<1; i++){
                for (int j=0; j<4; j++){
                    for(int k=0; k<4; k++){
                            ub[i][j]+= u[i][k] * bspline[k][j];
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

            // 1/6 = 0.16666
            glVertex3d(ubp[0][0]*0.16666, ubp[0][1]*0.16666, ubp[0][2]*0.16666);

    }

    glEnd();

    glDisable(GL_LINE_SMOOTH);

}
