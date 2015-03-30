#include <iostream>
#include <GL/glut.h>

#define TEAPOT 0
#define INFO_SCREEN 1
#define QUIT 2

using namespace std;

int currentDisplayObject = TEAPOT;

void drawTeapot() {
    glFlush();
    glClear(GL_COLOR_BUFFER_BIT);
    glutSolidTeapot(0.5);
}

void drawInfoScreen() {
    glFlush();
    glClear(GL_COLOR_BUFFER_BIT);
    glutSolidTeapot(2.0);
}

void draw(void) {
    //glutTimerFunc(100, draw(void), 0);
    cout << "Redraw.\n";

    // Black background
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (currentDisplayObject == TEAPOT) {
        drawTeapot();
    } else {
        drawInfoScreen();
    }
    glutSwapBuffers();
}

void windowStatusHandler(int windowState) {
    cout << "windowStatusHandler - window status! " << windowState << "\n";
    draw();
}

void menuItemClickHandler(int menuItem) {
    if (menuItem == QUIT) {
        exit(0);
    }
    currentDisplayObject = menuItem;
    glutPostRedisplay();
}

int main(int argc, char **argv) {

    cout << "Initializating...\n";

    glutInit(&argc, argv);

    /*Setting up  The Display
    /    -RGB color model + Alpha Channel = GLUT_RGBA
    */
    //glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    //Configure Window Postion
    glutInitWindowPosition(50, 25);

    //Configure Window Size
    glutInitWindowSize(600, 600);

    // Код ниже относится к OpenGLUT и сюда не подходит. Нужно найти адекватные коды статусов GLUT//Create Wind
    glutCreateWindow("Teapot");

    //Call to the drawing function
    glutDisplayFunc(draw);

    glutCreateMenu(menuItemClickHandler);
    glutAddMenuEntry("Teapot", TEAPOT);
    glutAddMenuEntry("Developer info", INFO_SCREEN);
    glutAddMenuEntry("Quit", QUIT);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutWindowStatusFunc(windowStatusHandler);

    glutMainLoop();

    return 0;
}
