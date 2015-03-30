#include <iostream>
#include <GL/glut.h>

#define TEAPOT 0
#define INFO_SCREEN 1
#define QUIT 2

using namespace std;

int currentDisplayObject = TEAPOT;

//void init() {
//    glClearColor(0, 0, 0, 0); // moved this line to be in the init function
//    //glDisable(GL_DEPTH_TEST);
//
//    // next four lines are new
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glOrtho(0.0, 600-1, 600-1, 0, -1.0, 1.0);
//    glMatrixMode(GL_MODELVIEW);
//}

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
    // Код ниже относится к OpenGLUT и сюда не подходит. Нужно найти адекватные коды статусов GLUT
    //switch (windowState) {
    //    case GLUT_VISIBLE:
    //        cout << "windowStatusHandler - window is visible now!\n";
    //        break;
    //    case GLUT_VISIBLE:
    //        cout << "windowStatusHandler - window is visible now!\n";
    //        break;
    //    case GLUT_VISIBLE:
    //        cout << "windowStatusHandler - window is visible now!\n";
    //        break;
    //    default:
    //        cout << "windowStatusHandler - unknown status!\n";
    //}
    draw();
}

void menuItemClickHandler(int menuItem) {
    if (menuItem == QUIT) {
        exit(0);
    }
    currentDisplayObject = menuItem;
    glutPostRedisplay();
}

//Main program

int main(int argc, char **argv) {

    cout << "Initializating...\n";

    glutInit(&argc, argv);

    /*Setting up  The Display
    /    -RGB color model + Alpha Channel = GLUT_RGBA
    */
    //glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    // Поменять GLUT_SINGLE на GLUT_DOUBLE (погуглить как решить баг с отсутствием перерисовки)
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    //Configure Window Postion
    glutInitWindowPosition(50, 25);

    //Configure Window Size
    glutInitWindowSize(600, 600);

    // Код ниже относится к OpenGLUT и сюда не подходит. Нужно найти адекватные коды статусов GLUT//Create Wind
    glutCreateWindow("Teapot");

    //init();

    //Call to the drawing function
    glutDisplayFunc(draw);

    glutCreateMenu(menuItemClickHandler);
    glutAddMenuEntry("Teapot", TEAPOT);
    glutAddMenuEntry("Developer info", INFO_SCREEN);
    glutAddMenuEntry("Quit", QUIT);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutWindowStatusFunc(windowStatusHandler);

    //glutTimerFunc(100, My_timer_event, 1);

    // Loop require by OpenGL
    glutMainLoop();

    return 0;
}
