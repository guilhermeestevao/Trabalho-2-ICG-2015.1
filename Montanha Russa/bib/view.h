#ifndef WINDOW_H
#define WINDOW_H

#include "mouse.h"
#include "camera.h"
#include <GL/glut.h>
#include "objeto.h"
#include <iomanip>
#define BUFSIZE 512
#define PADDING 5

class View
{
private:
    Objeto* montanhaRussa;
public:


    float width, height;
    Camera* camera;
    Camera* cameraCar;
    Mouse* mouse;
    float viewPortLimit;
    bool changeDivider = false;
    bool running = true;
    bool drawFloor = true;

    void setMontanhaRussa(Objeto* montanhaRussa);
    void displayInit();
    void displayEnd();
    void displayDraw();
    void display();
    int picking( GLint cursorX, GLint cursorY, int w, int h );
    int processHits( GLint hits, GLuint buffer[] );
    Camera* getCamera(int x, int y);
    bool isChangingDivider(int x, int y);
    void key(unsigned char key, int x, int y);
    void idle();
    void mouseMove(int x, int y);
    void mouseButton(int button, int state, int x, int y);
    void resize(float width, float height);
    void show(int argc, char** argv);
    void start();
    View(int width, int height);
    ~View();
};

#endif // WINDOW_H
