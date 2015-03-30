/**
 * GLUT Teapot
 * A simple GLUT program that draws a teapot and an info screen.
 */

#include <iostream>
#include <GL/glut.h>

#define TEAPOT 0
#define INFO_SCREEN 1
#define QUIT 2

using namespace std;

int currentDisplayObject = TEAPOT;

/**
 * Draws teapot
 */
void drawTeapot() {
    glFlush();
    glClear(GL_COLOR_BUFFER_BIT);
    glutSolidTeapot(0.5);
}

/**
 * Draws info screen
 */
void drawInfoScreen() {
    glFlush();
    glClear(GL_COLOR_BUFFER_BIT);
    glutSolidTeapot(2.0);
}

/**
 * GLUT redraw callback
 */
void draw(void) {
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

/**
 * GLUT window status callback
 * This function is executed when different window related events occur:
 *   - window opened
 *   - minimize/maximize
 *   - resize
 */
void windowStatusHandler(int windowState) {
    cout << "windowStatusHandler - window status! " << windowState << "\n";
    draw();
}

/**
 * Menu item click callback
 * This function is executed when user clicks on a context menu item
 */
void menuItemClickHandler(int menuItem) {
    if (menuItem == QUIT) {
        exit(0);
    }
    currentDisplayObject = menuItem;
    glutPostRedisplay();
}

/**
 * Main function. Program execution starts here.
 */
int main(int argc, char **argv) {
    cout << "Initializating...\n";
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(50, 25);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Teapot");
    glutDisplayFunc(draw); // Drawing function
    glutWindowStatusFunc(windowStatusHandler); // Used to redraw when window status is changed:
                                               // window shown, resize, etc.
    // Context menu
    glutCreateMenu(menuItemClickHandler);
    glutAddMenuEntry("Teapot", TEAPOT);
    glutAddMenuEntry("Developer info", INFO_SCREEN);
    glutAddMenuEntry("Quit", QUIT);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();

    return 0;
}
