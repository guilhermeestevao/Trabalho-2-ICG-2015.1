#ifndef CAR_H
#define CAR_H
#include "bib/objeto.h"
#include "bib/desenha.h"

class Carro : public Objeto
{
public:

    GLUquadric* quad;
    virtual void desenhar();

    Carro();
    ~Carro();
};

#endif // CAR_H
