#include "montanharussa.h"

void MontanhaRussa::desenhar()
{
    beginDraw();

    trilho->desenhar();

    glColor3d(1, 0, 0);

    glPushMatrix();

    Vetor3D* item = trilho->points[posicao];

    Vetor3D zl = Vetor3D(item[1]);
    Vetor3D yl = Vetor3D(item[2]);

    Vetor3D xl = yl.getVetorialProduct(zl);

    yl = zl.getVetorialProduct(xl);

    xl.normalize();
    yl.normalize();
    zl.normalize();

    float M[16] = {
        xl.x, yl.x, zl.x, item[0].x,
        xl.y, yl.y, zl.y, item[0].y,
        xl.z, yl.z, zl.z, item[0].z,
        0, 0, 0, 1
    };

    glMultTransposeMatrixf(M);
    car->t = Vetor3D(-1, 1.0, 0.5);
    car->r.x = 180;
    car->desenhar();

    glColor3d(1, 1, 1);

    glPopMatrix();

    endDraw();


}

void MontanhaRussa::proximo(Camera* camera)
{
    posicao = (posicao + 5)%trilho->points.size();
    if(posicao < trilho->points.size()-1){
        Vetor3D point = trilho->points[posicao][0];
        Vetor3D der1 = trilho->points[posicao][1];
        Vetor3D der2 = trilho->points[posicao][2];

        camera->c = point + der1;
        camera->e = point;
        camera->u = der2;
        camera->e = camera->e + camera->u.normalize()*2;
        camera->e = camera->e + (camera->e - camera->c).normalize()*5;
    }
}

void MontanhaRussa::key(Camera *camera, unsigned char key, int x, int y)
{
    if(key == 'w'){
        proximo(camera);
    }else{
        trilho->key(camera, key, x, y);
    }
}

bool MontanhaRussa::mouseMove(Camera *camera, Mouse *mouse)
{
    return trilho->mouseMove(camera, mouse);
}

MontanhaRussa::MontanhaRussa()
{
    trilho = new Trilho();
    car = new Carro();
    obj = new Objeto(Vetor3D(-200, -10, -200), Vetor3D(200, -9, 200));
    car->r = Vetor3D(0, 0, 0);
}

MontanhaRussa::~MontanhaRussa()
{
    delete trilho;
    delete car;
    delete obj;
}

