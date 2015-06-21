#ifndef ROLLER_H
#define ROLLER_H

#include "bib/objeto.h"
#include "bib/desenha.h"
#include <vector>


class Trilho : public Objeto
{
public:

    int pontoDeControleCorrente = -1;

    double curvas[5][4][4] = {
        //b-splines
        {
            {-1/6.0, 3/6.0, -3/6.0, 1/6.0},
            {3/6.0, -6/6.0, 3/6.0, 0/6.0},
            {-3/6.0, 0/6.0, 3/6.0, 0/6.0},
            {1/6.0, 4/6.0, 1/6.0, 0/6.0}
        },
        //hermit
        {
            {2, -2, 1, 1},
            {-3, 3, -2, -1},
            {0, 0, 1, 0},
            {1, 0, 0, 0}
        },
        //bezier
        {
            {-1, 3, -3, 1},
            {3, -6, 3, 0},
            {-3, 3, 0, 0},
            {1, 0, 0, 0}
        },
        //catmull-rom
        {
            {-1/2.0, 3/2.0, -3/2.0, 1/2.0},
            {2/2.0, -5/2.0, 4/2.0, -1/2.0},
            {-1/2.0, 0/2.0, 1/2.0, 0/2.0},
            {0/2.0, 2/2.0, 0/2.0, 0/2.0}
        },
        //interpoladora
        {
            {-4.5,  13.5, -13.5,  4.5},
            { 9.0, -22.5,  18.0, -4.5},
            {-5.5,   9.0,  -4.5,  1.0},
            {   1,     0,     0,    0}
        }
    };

    int selectedMatrix = 0;

    float** get_mult_matrix(std::vector<Vetor3D> ps);

    virtual void key(Camera* camera, unsigned char key, int x, int y);
    Vetor3D getParametrica(float i);
    Vetor3D getDerivadaPrimeira(float i);
    Vetor3D getDerivadaSegunda(float i);
    std::vector<Vetor3D*> points;
    std::vector<Vetor3D> pontosDeControle;
    Objeto* obj;

    bool showControls = true;

    void desenhar();
    virtual bool mouseMove(Camera* camera, Mouse* mouse);
    void calculate();

    Trilho();
    ~Trilho();

};

#endif // ROLLER_H
