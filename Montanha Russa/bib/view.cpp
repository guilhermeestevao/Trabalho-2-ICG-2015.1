#include "view.h"

void View::setMontanhaRussa(Objeto *scene)
{
    this->montanhaRussa = scene;
}

void View::displayInit()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    const float ar = height > 0 ? (float) width / (float) height : 1.0;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.,ar,0.1,1000.);

    glPushMatrix();
        glViewport(0, 0, viewPortLimit*2, height);
        gluLookAt(cameraCar->e.x,cameraCar->e.y,cameraCar->e.z, cameraCar->c.x,cameraCar->c.y,cameraCar->c.z, cameraCar->u.x,cameraCar->u.y,cameraCar->u.z);
        displayDraw();
    glPopMatrix();

}

Camera *View::getCamera(int x, int y)
{
    return cameraCar;
}


View::View(int width, int height)
{
    this->width = width;
    this->height = height;

    this->cameraCar = new Camera();
    this->camera = new Camera();
    this->mouse = new Mouse();
}

View::~View()
{

}



void View::displayEnd()
{
    glutSwapBuffers();
}



void View::displayDraw(){
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();

    if(montanhaRussa != NULL){
        montanhaRussa->desenhar();
    }
}



void View::display(){
    displayInit();

    displayEnd();
}

void View::key(unsigned char key, int x, int y){
    if(key == 23)
        exit(0);
    else if(montanhaRussa != NULL){
        montanhaRussa->key(cameraCar, key, x, y);
    }
}

void View::idle(){
    glutPostRedisplay();
}

void View::mouseMove(int x, int y){

        mouse->x = x;
        mouse->y = y;

        bool moveCamera = true;
        if(montanhaRussa != NULL){
            moveCamera = montanhaRussa->mouseMove(getCamera(x, y), mouse);
        }
        if(moveCamera){
            if(mouse->left && !mouse->right && !mouse->middle){
                getCamera(x, y)->rotateX(mouse->y, Objeto::lastY);
                getCamera(x, y)->rotateY(mouse->x, Objeto::lastX);
            }else if(!mouse->left && mouse->right && !mouse->middle){
                getCamera(x, y)->translateX(mouse->x, Objeto::lastX);
                getCamera(x, y)->translateY(mouse->y, Objeto::lastY);
            }
        }

        Objeto::lastX = x;
        Objeto::lastY = y;

}

void View::mouseButton(int button, int state, int x, int y)   {

    mouse->w = 0;
    if(button == 3){
        mouse->w = camera->e.getDistanceTo(camera->c)*0.1;
    }else if(button == 4){
        mouse->w = camera->e.getDistanceTo(camera->c)*-0.1;
    }
    else{
        if (button == GLUT_LEFT_BUTTON) {
            if (state == GLUT_DOWN) {
                mouse->left = true;

            } else {
                mouse->left = false;

                glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
            }
        }
        if (button == GLUT_MIDDLE_BUTTON) {
            if (state == GLUT_DOWN) {
                mouse->middle = true;
            } else {
                mouse->middle = false;
            }
        }
        if (button == GLUT_RIGHT_BUTTON) {
            if (state == GLUT_DOWN) {
                mouse->right = true;
            } else {
                mouse->right = false;
            }
        }

        if(montanhaRussa != NULL){
            mouse->x = x;
            mouse->y = y;
            montanhaRussa->mouseClick(getCamera(x, y), mouse);
        }
    }


    getCamera(x, y)->zoom(mouse->w);
    Objeto::lastX = mouse->x;
    Objeto::lastY = mouse->y;

}

void View::start()
{
    glutMainLoop();
}


void View::resize(float width, float height){
    this->width = width;
    this->height = height;
    this->viewPortLimit = width/2;
}

void View::show(int argc, char** argv)
{

    glutInit(&argc, argv);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Montanha Russa");

    glClearColor(0,0,0,0);

    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_NORMALIZE);

    glShadeModel(GL_SMOOTH);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHT0);

    const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
    const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat light_position[] = {50, 50, 50, 0};

    const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
    const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
    const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat high_shininess[] = { 100.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
}
