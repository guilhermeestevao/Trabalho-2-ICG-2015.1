#ifndef ROLLERCOASTER_H
#define ROLLERCOASTER_H

#include "bib/objeto.h"
#include "trilho.h"
#include "carro.h"

class MontanhaRussa : public Objeto
{
public:

    int posicao = 0;
    virtual void desenhar();
    Objeto* obj;
    Carro* car;
    Trilho* trilho;
    void proximo(Camera* camera);
    virtual void key(Camera* camera, unsigned char key, int x, int y);
    virtual bool mouseMove(Camera* camera, Mouse* mouse);
    MontanhaRussa();
    ~MontanhaRussa();
};

#endif // ROLLERCOASTER_H
