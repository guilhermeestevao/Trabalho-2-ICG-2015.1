#include <iostream>
#include <GL/glut.h>
#include <iomanip>
#include <vector>
#include "bib/view.h"
#include "montanharussa.h"

View* view = new View(800, 500);

void resize(int width, int height){
    view->resize(width, height);
}

void display(){
    view->display();
}

void key(unsigned char key, int x, int y){
    view->key(key, x, y);
}

void idle(){
    view->idle();
}

void mouseButton(int a, int b, int c, int d){
    view->mouseButton(a, b, c, d);
}

void mouseMove(int a, int b){
    view->mouseMove(a, b);
}

int main(int argc, char** argv){

    view->show(argc, argv);
    view->setMontanhaRussa(new MontanhaRussa());
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutPassiveMotionFunc(mouseMove);

    glutIdleFunc(idle);

    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);
    view->start();

    return 0;
}

