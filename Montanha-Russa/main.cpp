/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */
//#include <windows.h>


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <SDL/SDL.h>
#include "bib/CameraDistante.h"
#include "bib/Desenha.h"
#include "Bezier.h"
#include "Hermite.h"
#include "BSpline.h"
#include "CatmullRom.h"
#include "Carrinho.h"


using namespace std;

GLuint texture[6];//the array for our texture

static int slices = 16;
static int stacks = 16;

static float ax = 0.0;
static float ay = 0.0;
static float az = 0.0;

static float trans_obj = false;

static float tx = 0.0;
static float ty = 0.0;
static float tz = 0.0;

static float sx = 1.0;
static float sy = 1.0;
static float sz = 1.0;

static float delta = 5.0;

static bool lbpressed = false;
static bool mbpressed = false;
static bool rbpressed = false;

static float last_x = 0.0;
static float last_y = 0.0;


Camera* cam = new CameraDistante();
static float savedCamera[9];

typedef struct ponto{
    float x, y, z;
}Ponto;

float ctrlPoints[4][3];
static vector<Ponto> listaPontos;
static vector<Ponto> listaPontosTrilha;
static vector<Ponto> listaPontosD1;
static vector<Ponto> listaPontosD2;

static float deltaU = 0.0001;
static float variacao = (int)listaPontosTrilha.size();
Carrinho* car = new Carrinho();

unsigned int tex;

int mult = 100;


//GLUT callback Handlers
// funções
void carregarPontos();
void tempo(int n);
void drawTrilha();
void carregarPontosTrilha();
void calcularPontosTrilha(float pontos[4][3], float delta);
void carregarPontosD1();
void calcularPontosD1(float pontos[4][3], float delta);
void carregarPontosD2();
void calcularPontosD2(float pontos[4][3], float delta);
unsigned int loadTexture(const char* filename);
//funções




void carregarPontosD2(){
    for(unsigned int i=0; i<(unsigned int)listaPontos.size()-2; i++){
        memset(ctrlPoints, 0, sizeof(ctrlPoints));

        for(int k=0; k<4; k++){
            ctrlPoints[k][0] = listaPontos[k+i].x;
            ctrlPoints[k][1] = listaPontos[k+i].y;
            ctrlPoints[k][2] = listaPontos[k+i].z;
        }

        calcularPontosD2(ctrlPoints, deltaU);
    }
    printf("SIZE DA LISTA DE PONTOS D2: %d\n", listaPontosD2.size());
}

void calcularPontosD2(float pontos[4][3], float delta){
    Ponto ponto;
    float u[1][4];
    float ub[1][4];
    float ubp[1][3];
    float catmullrom[4][4] = {
            {-1,  3, -3,  1},
            { 2, -5,  4, -1},
            {-1,  0,  1,  0},
            { 0,  2,  0,  0} };


    for(float t=0; t<=1; t+=delta){

        memset(u,0,sizeof(u));
        memset(ub,0,sizeof(ub));
        memset(ubp, 0, sizeof(ubp));

        u[0][0] = 6*t;
        u[0][1] = 2;
        u[0][2] = 0;
        u[0][3] = 0;

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
        ponto.x = ubp[0][0]*0.5;
        ponto.y = ubp[0][1]*0.5;
        ponto.z = ubp[0][2]*0.5;
        listaPontosD2.push_back(ponto);
    }

}


void carregarPontosD1(){
    for(unsigned int i=0; i<(unsigned int)listaPontos.size()-2; i++){
        memset(ctrlPoints, 0, sizeof(ctrlPoints));

        for(int k=0; k<4; k++){
            ctrlPoints[k][0] = listaPontos[k+i].x;
            ctrlPoints[k][1] = listaPontos[k+i].y;
            ctrlPoints[k][2] = listaPontos[k+i].z;
        }

        calcularPontosD1(ctrlPoints, deltaU);
    }

    printf("SIZE DA LISTA DE PONTOS D1: %d\n", listaPontosD1.size());
}


void calcularPontosD1(float pontos[4][3], float delta){
    Ponto ponto;
    float u[1][4];
    float ub[1][4];
    float ubp[1][3];
    float catmullrom[4][4] = {
            {-1,  3, -3,  1},
            { 2, -5,  4, -1},
            {-1,  0,  1,  0},
            { 0,  2,  0,  0} };


    for(float t=0; t<=1; t+=delta){

        memset(u,0,sizeof(u));
        memset(ub,0,sizeof(ub));
        memset(ubp, 0, sizeof(ubp));

        u[0][0] = 3*t*t;
        u[0][1] = 2*t;
        u[0][2] = 1;
        u[0][3] = 0;

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
        ponto.x = ubp[0][0]*0.5;
        ponto.y = ubp[0][1]*0.5;
        ponto.z = ubp[0][2]*0.5;
        listaPontosD1.push_back(ponto);
    }

}

void carregarPontosTrilha(){
    for(unsigned int i=0; i<(unsigned int)listaPontos.size()-2; i++){
        memset(ctrlPoints, 0, sizeof(ctrlPoints));

        for(int k=0; k<4; k++){
            ctrlPoints[k][0] = listaPontos[k+i].x;
            ctrlPoints[k][1] = listaPontos[k+i].y;
            ctrlPoints[k][2] = listaPontos[k+i].z;
        }

        calcularPontosTrilha(ctrlPoints, deltaU);
    }

    printf("SIZE DA LISTA DE PONTOS TRILHA: %d\n", listaPontosTrilha.size());
}

void calcularPontosTrilha(float pontos[4][3], float delta){


    Ponto ponto;
    float u[1][4];
    float ub[1][4];
    float ubp[1][3];
    float catmullrom[4][4] = {
            {-1,  3, -3,  1},
            { 2, -5,  4, -1},
            {-1,  0,  1,  0},
            { 0,  2,  0,  0} };


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
        ponto.x = ubp[0][0]*0.5;
        ponto.y = ubp[0][1]*0.5;
        ponto.z = ubp[0][2]*0.5;
        listaPontosTrilha.push_back(ponto);
    }

}


void drawTrilha(){
    for(unsigned int i=0; i<(unsigned int)listaPontos.size()-2; i++){
        memset(ctrlPoints, 0, sizeof(ctrlPoints));

        for(int k=0; k<4; k++){
            ctrlPoints[k][0] = listaPontos[k+i].x;
            ctrlPoints[k][1] = listaPontos[k+i].y;
            ctrlPoints[k][2] = listaPontos[k+i].z;
        }

        CatmullRom::desenhar(ctrlPoints, deltaU);
    }
}

void tempo(int n){

   if( variacao-1 >= 0 ){
        variacao-= 1; //(int)listaPontosTrilha.size()
        glutPostRedisplay();
        glutTimerFunc(n, tempo,0);
   }else{
        variacao=(int)listaPontosTrilha.size();
   }
}


void carregarPontos(){
    Ponto ponto;

    ponto.x = 2; ponto.y = 5; ponto.z = 5;
    listaPontos.push_back(ponto);
    ponto.x = 0; ponto.y = 5; ponto.z = 10;
    listaPontos.push_back(ponto);
    ponto.x = 3; ponto.y = 0; ponto.z = 6;
    listaPontos.push_back(ponto);
    ponto.x = 6; ponto.y = 0; ponto.z = 4;
    listaPontos.push_back(ponto);
    ponto.x = 14; ponto.y = 8; ponto.z = 1;
    listaPontos.push_back(ponto);
    ponto.x = 20; ponto.y = 16; ponto.z = 3;
    listaPontos.push_back(ponto);
    ponto.x = -18; ponto.y = 16; ponto.z = -9;
    listaPontos.push_back(ponto);
    ponto.x = 3; ponto.y = 5; ponto.z = -5;
    listaPontos.push_back(ponto);
    ponto.x = -10; ponto.y = -2; ponto.z = 1;
    listaPontos.push_back(ponto);
    ponto.x = 3; ponto.y = 0; ponto.z = 2;
    listaPontos.push_back(ponto);
    ponto.x = 0; ponto.y = 4; ponto.z = 1;
    listaPontos.push_back(ponto);
    ponto.x = 0; ponto.y = 5; ponto.z = 10;
    listaPontos.push_back(ponto);


    printf("SIZE DA LISTA DE PONTOS: %d\n", listaPontos.size());

}

unsigned int loadTexture(const char* filename)
{
        SDL_Surface* img = SDL_LoadBMP(filename);
        unsigned int id;
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->w, img->h, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, img->pixels);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

        SDL_FreeSurface(img);
        return id;
}

static void resize(int width, int height)
{
    const float ar = height>0 ? (float) width / (float) height : 1.0;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.,ar,0.1,1000.);

    //testes
    //glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    //glOrtho(-10.0, 10.0, -10.0, 10.0, -1000.0, 1000.0);
    //glOrtho(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    //glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    //gluPerspective(30.,ar,0.1,1000.);
}


static void display(void)
{
    //const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    //cam->e.z += 0.001*t;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(cam->e.x,cam->e.y,cam->e.z, cam->c.x,cam->c.y,cam->c.z, cam->u.x,cam->u.y,cam->u.z);


    tempo(500);

    /*
    gluLookAt(listaPontosTrilha[variacao].x,
              listaPontosTrilha[variacao].y,
              listaPontosTrilha[variacao].z,
              listaPontosTrilha[variacao].x + listaPontosD1[variacao].x,
              listaPontosTrilha[variacao].y + listaPontosD1[variacao].y,
              listaPontosTrilha[variacao].z + listaPontosD1[variacao].z,
              listaPontosD2[variacao].x,
              listaPontosD2[variacao].y,
              listaPontosD2[variacao].x);
    */


    car->desenhar(0.2, listaPontosTrilha[variacao].x, listaPontosTrilha[variacao].y, listaPontosTrilha[variacao].z);

    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        //glRotated(90, 0, 1, 0);
        //glTranslated(0,mult,-mult);
        glBegin(GL_QUADS);

                glTexCoord2f(0.0,1.0); glVertex3f(-2.0*mult,-2.0*mult,-2.0*mult);
                glTexCoord2f(1.0,1.0); glVertex3f(2.0*mult,-2.0*mult,-2.0*mult);
                glTexCoord2f(1.0,0.0); glVertex3f(2.0*mult,2.0*mult,-2.0*mult);
                glTexCoord2f(0.0,0.0); glVertex3f(-2.0*mult,2.0*mult,-2.0*mult);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture[1]);
        //glRotated(180, 0, 0, 1);
        //glTranslated(0,-mult,0);
        glBegin(GL_QUADS);

                glTexCoord2f(0.0,1.0); glVertex3f(-2.0*mult,-2.0*mult,2.0*mult);
                glTexCoord2f(1.0,1.0); glVertex3f(2.0*mult,-2.0*mult,2.0*mult);
                glTexCoord2f(1.0,0.0); glVertex3f(2.0*mult,-2.0*mult,-2.0*mult);
                glTexCoord2f(0.0,0.0); glVertex3f(-2.0*mult,-2.0*mult,-2.0*mult);

        glEnd();
        glDisable(GL_TEXTURE_2D);

        glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture[2]);
        //glRotated(180, 0, 0, 1);
        //glTranslated(0,-mult,0);
        glBegin(GL_QUADS);

                glTexCoord2f(0.0,1.0); glVertex3f(2.0*mult,-2.0*mult,-2.0*mult);
                glTexCoord2f(1.0,1.0); glVertex3f(2.0*mult,-2.0*mult,2.0*mult);
                glTexCoord2f(1.0,0.0); glVertex3f(2.0*mult,2.0*mult,2.0*mult);
                glTexCoord2f(0.0,0.0); glVertex3f(2.0*mult,2.0*mult,-2.0*mult);

        glEnd();
        glDisable(GL_TEXTURE_2D);

        glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture[3]);
        //glRotated(180, 0, 0, 1);
        //glTranslated(0,-mult,0);
        glBegin(GL_QUADS);

                glTexCoord2f(0.0,1.0); glVertex3f(-2.0*mult,-2.0*mult,2.0*mult);
                glTexCoord2f(1.0,1.0); glVertex3f(-2.0*mult,-2.0*mult,-2.0*mult);
                glTexCoord2f(1.0,0.0); glVertex3f(-2.0*mult,2.0*mult,-2.0*mult);
                glTexCoord2f(0.0,0.0); glVertex3f(-2.0*mult,2.0*mult,2.0*mult);

        glEnd();
        glDisable(GL_TEXTURE_2D);

         glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture[4]);
        //glRotated(180, 0, 0, 1);
        //glTranslated(0,-mult,0);
        glBegin(GL_QUADS);

                glTexCoord2f(0.0,1.0); glVertex3f(-2.0*mult,2.0*mult,-2.0*mult);
                glTexCoord2f(1.0,1.0); glVertex3f(2.0*mult,2.0*mult,-2.0*mult);
                glTexCoord2f(1.0,0.0); glVertex3f(2.0*mult,2.0*mult,2.0*mult);
                glTexCoord2f(0.0,0.0); glVertex3f(-2.0*mult,2.0*mult,2.0*mult);

        glEnd();
        glDisable(GL_TEXTURE_2D);


        glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture[5]);
        //glRotated(180, 0, 0, 1);
        //glTranslated(0,-mult,0);
        glBegin(GL_QUADS);

                glTexCoord2f(0.0,1.0); glVertex3f(2.0*mult,-2.0*mult,2.0*mult);
                glTexCoord2f(1.0,1.0); glVertex3f(-2.0*mult,-2.0*mult,2.0*mult);
                glTexCoord2f(1.0,0.0); glVertex3f(-2.0*mult,2.0*mult,2.0*mult);
                glTexCoord2f(0.0,0.0); glVertex3f(2.0*mult,2.0*mult,2.0*mult);

        glEnd();
        glDisable(GL_TEXTURE_2D);






    glPopMatrix();




    //*
    float ctrolPointsBezier[4][3] = {
        {-4.0,-4.0,0.0},
        {-2.0,4.0,0.0},
        {2.0,-4.0,0.0},
        {4.0,4.0,0.0}};


	float ctrolPointsHermite[4][3] = {
        {-4.0,-4.0,0.0},
        {-2.0,4.0,0.0},
        {6.0,24.0,0.0},
        {24.0,36.0,0.0}};
    //*/


    // desenhando os pontos na lista de pontos
    glPointSize(10);
    glBegin(GL_POINTS);
        glColor3d(1, 0.7, 0);
        for(unsigned int i=0; i<listaPontos.size(); i++){
            glVertex3d(listaPontos[i].x, listaPontos[i].y, listaPontos[i].z);
        }

    glEnd();

    drawTrilha();

    // curvas 3D
    glPushMatrix();
        glTranslated(0,0,-10);
        Bezier::desenhar(ctrolPointsBezier, 0.01);
        //Hermite::desenhar(ctrolPointsHermite, 0.01);
        BSpline::desenhar(ctrolPointsBezier, 0.01);
        CatmullRom::desenhar(ctrolPointsBezier, 0.0001);
    glPopMatrix();

    /*
    GLfloat ctrlpoints[4][3] = {
        {-4.0,-4.0,0.0},
        {-2.0,4.0,0.0},
        {2.0,-4.0,0.0},
        {4.0,4.0,0.0}    };
    // we want to draw with t from 0.0 to 1.0
    // and we give the dimensions of the data
    glMap1f(GL_MAP1_VERTEX_3,0.0,1.0,3,4,& ctrlpoints[0][0]);
    glEnable(GL_MAP1_VERTEX_3);
    // draw a curve with 30 steps from t=0.0 to t=1.0
    glBegin(GL_LINE_STRIP);
    for (int i=0;i<=30;i++)
       //glEvalCoord1f((GLfloat) i/30.0);
    glEnd();
    */



    //glColor3d(0.3,0.3,0.3);
    //sistema global
    glPushMatrix();
        //!!!!!!!!!!!!!desenhar eixos do sistema de coordenadas global
        //Desenha::drawEixos( 0.5 );
        //chao
        glColor3d(0,0,0);
        glTranslated(0,-5, 0);
        Desenha::drawGrid( 10, 0, 10, 1 );
    glPopMatrix();

    /*
    //sistema local 1
    glPushMatrix();
        glTranslated(tx,ty,tz);
        glRotated(az,0,0,1);
        glRotated(ay,0,1,0);
        glRotated(ax,1,0,0);
        //!!!!!!!!!!!!!desenhar eixos do sistema de coordenadas local 1
          Desenha::drawEixos( 0.5 );
        glScaled(sx,sy,sz);
        //casa desenhada localmente
        //draw_casa();
        //Desenha::drawBox( -1.0,-1.0,-1.0, 1.0,1.0,1.0 );
        Desenha::drawBox( 0.0,0.0,0.0, 1.0,1.0,1.0 );
    glPopMatrix();

    //sistema local 2
    glPushMatrix();
        glTranslated(0,0,-6);
        glTranslated(tx,ty,tz);
        glRotated(az,0,0,1);
        glRotated(ay,0,1,0);
        glRotated(ax,1,0,0);
        //!!!!!!!!!!!!!desenhar eixos do sistema de coordenadas local 2
          //Desenha::drawEixos( 0.5 );
        glColor3d(1,0,0);
        //glutSolidTorus(0.2,0.8,slices,stacks);
        //glutSolidCone(1,1,slices,stacks);
        //!!!!!!!!!!!!!testar cisalhamento
        //Desenha::drawBox( -1.0,-1.0,-1.0, 1.0,1.0,1.0 );
        //Desenha::drawBox( 0.0,0.0,0.0, 1.0,1.0,1.0 );
    glPopMatrix();
    */

    glutSwapBuffers();
}

static void mouseButton(int button, int state, int x, int y) {

	// if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {
		// when the button is pressed
		if (state == GLUT_DOWN) {
            lbpressed = true;
		} else {// state = GLUT_UP
            lbpressed = false;
		}
	}
	// if the middle button is pressed
	if (button == GLUT_MIDDLE_BUTTON) {
		// when the button is pressed
		if (state == GLUT_DOWN) {
            mbpressed = true;
		} else {// state = GLUT_UP
            mbpressed = false;
		}
	}
	// if the left button is pressed
	if (button == GLUT_RIGHT_BUTTON) {
		// when the button is pressed
		if (state == GLUT_DOWN) {
            rbpressed = true;
		} else {// state = GLUT_UP
            rbpressed = false;
		}
	}

    last_x = x;
    last_y = y;
}

static void mouseMove(int x, int y) {
    float fator = 10.0;
    if (lbpressed && !rbpressed && !mbpressed) {
        if (!trans_obj) {
            cam->rotatex(y,last_y);
            cam->rotatey(x,last_x);
        } else {
            ax += (y - last_y)/fator;
            ay += (x - last_x)/fator;
        }
    }
    fator = 100.0;
    if (!lbpressed && rbpressed && !mbpressed) {
        if (!trans_obj) {
            cam->translatex(x,last_x);
            cam->translatey(y,last_y);
        } else {
            tx += (x - last_x)/fator;
            ty += -(y - last_y)/fator;
        }
    }
    if (lbpressed && rbpressed && !mbpressed) {
        if (!trans_obj) {
            cam->zoom(y,last_y);
        } else {
            tz += (y - last_y)/fator;
            fator = 10.0;
            az += -(x - last_x)/fator;
        }
    }
    fator = 100.0;
    if (!lbpressed && !rbpressed && mbpressed) {
        if (!trans_obj) {
        } else {
            sx += (x - last_x)/fator;
            sy += -(y - last_y)/fator;
        }
    }
    if (lbpressed && !rbpressed && mbpressed) {
        if (!trans_obj) {
        } else {
            sz += (y - last_y)/fator;
        }
    }

    last_x = x;
    last_y = y;
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;

        case '+':
            slices++;
            stacks++;
            break;

        case '-':
            if (slices>3 && stacks>3)
            {
                slices--;
                stacks--;
            }
            break;

        case 'X':
            ax+=delta;
            break;

        case 'Y':
            ay+=delta;
            break;

        case 'Z':
            az+=delta;
            break;

        case 'x':
            ax-=delta;
            break;

        case 'y':
            ay-=delta;
            break;

        case 'z':
            az-=delta;
            break;

        case 'i':
            ax=ay=az=0.0;
            tx=ty=tz=0.0;
            sx=sy=sz=1.0;
            break;

        case 't':
            trans_obj = !trans_obj;
            break;

        case 'c':
            static int posCam = 0;
            posCam++;
            if (cam->estilo == 1) {
                delete cam;
                if (posCam%5==0) cam = new CameraDistante(); //CameraDistante(0,1,5, 0,1,0, 0,1,0);
                if (posCam%5==1) cam = new CameraDistante(5,1,0, 0,1,0, 0,1,0);
                if (posCam%5==2) cam = new CameraDistante(0,1,-5, 0,1,0, 0,1,0);
                if (posCam%5==3) cam = new CameraDistante(-5,1,0, 0,1,0, 0,1,0);
                if (posCam%5==4) cam = new CameraDistante(savedCamera[0],savedCamera[1],savedCamera[2],savedCamera[3],savedCamera[4],savedCamera[5],savedCamera[6],savedCamera[7],savedCamera[8]);
            } else if (cam->estilo == 2) {
                delete cam;
                cam = new CameraDistante();
            }
            break;

        case 's':
            //save current camera location
            savedCamera[0] = cam->e.x;
            savedCamera[1] = cam->e.y;
            savedCamera[2] = cam->e.z;
            savedCamera[3] = cam->c.x;
            savedCamera[4] = cam->c.y;
            savedCamera[5] = cam->c.z;
            savedCamera[6] = cam->u.x;
            savedCamera[7] = cam->u.y;
            savedCamera[8] = cam->u.z;
            break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

// Program entry point

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    //key('s',0,0);
    glutIdleFunc(idle);

	// here are the two new functions
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);

    carregarPontos();
    carregarPontosTrilha();
    carregarPontosD1();
    carregarPontosD2();

    texture[0] = loadTexture("left.bmp");
    texture[1] = loadTexture("bottom.bmp");
    texture[2] = loadTexture("back.bmp");
    texture[3] = loadTexture("front.bmp");
    texture[4] = loadTexture("top.bmp");
    texture[5] = loadTexture("right.bmp");


    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    //glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);


    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);



    glutMainLoop();

    return EXIT_SUCCESS;
}
