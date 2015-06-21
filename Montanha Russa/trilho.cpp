#include "trilho.h"

float** Trilho::get_mult_matrix(std::vector<Vetor3D> ps)
{
    int n = 4;
    float** M = new float*[n];
    for(int i = 0; i<n; i++){
        M[i] = new float[n];
        for(int j = 0; j<n; j++){
            M[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                M[i][j] += curvas[selectedMatrix][i][k] * ps[k][j];
            }
        }
    }

    return M;
}

void Trilho::key(Camera *camera, unsigned char key, int x, int y)
{
    if(key == 'd'){
        pontoDeControleCorrente = (pontoDeControleCorrente + 1) % pontosDeControle.size();
    }
    if(key == 'a'){
        pontoDeControleCorrente = (pontoDeControleCorrente - 1);
        if(pontoDeControleCorrente < 0)
            pontoDeControleCorrente = pontosDeControle.size()-1;
    }


    if(key == 'm' || key == 'M'){
        selectedMatrix = (selectedMatrix + 1) % 5;
        points.clear();
        calculate();
    }
    if(key == 's'){
        showControls = showControls ? false : true;
    }
    if(key == 'i'){
        pontoDeControleCorrente = -1;
    }

}

Vetor3D Trilho::getParametrica(float i)
{
    return Vetor3D(i*i*i, i*i, i, 1);
}

Vetor3D Trilho::getDerivadaPrimeira(float i)
{
    return Vetor3D(3*i*i, 2*i, 1, 0);
}

Vetor3D Trilho::getDerivadaSegunda(float i)
{
    return Vetor3D(6*i, 2, 0, 0);
}

void Trilho::desenhar()
{

    glColor3d(1, 1, 0);

    if(showControls){
        for(int i = 0; i<pontosDeControle.size(); i++){
            obj->begin = Vetor3D(-0.3, -0.3, -0.3);
            obj->end = Vetor3D(0.3, 0.3, 0.3);
            obj->t = pontosDeControle[i];
            if(i == pontoDeControleCorrente)
                glColor3d(1, 0, 0);
            else
                glColor3d(0, 1, 0);
            glPushMatrix();
                glPushName(i+1);
                    glTranslated(obj->t.x, obj->t.y, obj->t.z);
                    Desenha::drawBox(obj->begin.x+1, obj->begin.y, obj->begin.z, obj->end.x, obj->end.y, obj->end.z);
                glPopName();
            glPopMatrix();
        }
    }

    glColor3d(1, 0, 0);

    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < points.size()-1; i++) {
       Vetor3D pointBegin = points[i][0];
       Vetor3D pointEnd = points[i+1][0];
       glColor3d(0, 0, 1);
       obj->begin = pointBegin+Vetor3D(0.1, 0.1, 2);
       obj->end = pointEnd+Vetor3D(0.1, 0.1, 0);
       glColor3d(0, 0, 1);
       Objeto::beginDraw();
       Desenha::drawBox(obj->begin.x, obj->begin.y, obj->begin.z, obj->end.x, obj->end.y, obj->end.z);
       Objeto::endDraw();
   }

   glEnd();

}

bool Trilho::mouseMove(Camera *camera, Mouse *mouse)
{
    if(pontoDeControleCorrente != -1){
        obj->begin = Vetor3D(-0.3, -0.3, -0.3);
        obj->end = Vetor3D(0.3, 0.3, 0.3);

        obj->t = pontosDeControle[pontoDeControleCorrente];
        obj->mouseMove(camera, mouse);
        pontosDeControle[pontoDeControleCorrente] = obj->t;

        points.clear();

        calculate();

        return false;
    }else{
        return true;
    }
}

void Trilho::calculate()
{
    float delta = 0.01;
    for (int i = 0; i <= pontosDeControle.size()-4; i++) {
        std::vector<Vetor3D> ps;
        for (int j = i; j < i+4; j++) {
            ps.push_back(pontosDeControle[j]);
        }

        float** M = get_mult_matrix(ps);

        for(float k = 0; k<1; k += delta){
            Vetor3D u = getParametrica(k);
            Vetor3D t = u.multipliedByMatrix(M);
            Vetor3D* vec = new Vetor3D[3];
            vec[0] = t;

            u = getDerivadaPrimeira(k);
            t = u.multipliedByMatrix(M);

            vec[1] = t;

            u = getDerivadaSegunda(k);
            t = u.multipliedByMatrix(M);

            vec[2] = t;

            points.push_back(vec);

        }

        for(int i = 0; i<4; i++)
            delete M[i];
        delete M;
    }
}

Trilho::Trilho()
{

    obj = new Objeto(Vetor3D(), Vetor3D());

    //pontosDeControle.push_back(Vetor3D(0.303733, 6.54, 0.349143));
    //pontosDeControle.push_back(Vetor3D(-0.146103, 5.59, 0.297588));
    pontosDeControle.push_back(Vetor3D(2.65586, 2.85, -0.02129));
    pontosDeControle.push_back(Vetor3D(8.77768, 3.45999, -0.707782));
    pontosDeControle.push_back(Vetor3D(17.2151, 8.88003, -2.01362));
    pontosDeControle.push_back(Vetor3D(20.955, 20.3201, -2.63522));
    pontosDeControle.push_back(Vetor3D(15.2257, 28.22, -12.8058));
    pontosDeControle.push_back(Vetor3D(-0.271426, 26.59, -12.0068));
    pontosDeControle.push_back(Vetor3D(5.60057, 11.88, -13.628));
    pontosDeControle.push_back(Vetor3D(32.1301, 12.6201, -11.1308));
    pontosDeControle.push_back(Vetor3D(28.0218, 42.61, 0.645504));
    pontosDeControle.push_back(Vetor3D(-3.60768, 36.85, -0.483917));
    pontosDeControle.push_back(Vetor3D(-9.77246, 34.7599, -1.31083));
    pontosDeControle.push_back(Vetor3D(-21.3236, 19.57, -4.31963));
    pontosDeControle.push_back(Vetor3D(-16.2609, -5.56001, -1.7164));
    pontosDeControle.push_back(Vetor3D(3.12293, 2.51002, 9.72232));
    pontosDeControle.push_back(Vetor3D(2.44108, 17.37, 9.77238));
    pontosDeControle.push_back(Vetor3D(-13.4604, 21.11, 1.58342));
    pontosDeControle.push_back(Vetor3D(-14.8581, 5.35997, -1.98809));
    pontosDeControle.push_back(Vetor3D(-4.32222, 2.58999, 0.556865));
    //pontosDeControle.push_back(Vetor3D(2.91634, 4.63998, -0.108708));
    //pontosDeControle.push_back(Vetor3D(-2.00798, 20.44, 5.62666));

    calculate();
}

Trilho::~Trilho()
{
    delete obj;
}
