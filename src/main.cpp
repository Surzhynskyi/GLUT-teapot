/**
 * GLUT Teapot
 * A simple GLUT program that draws a teapot and an info screen.
 */
#include <iostream>
#include <GL/glut.h>

// Context menu indexes
#define TEAPOT 0
#define INFO_SCREEN 1
#define QUIT 2

// Teapot size/scale settings
#define MIN_TEAPOT_SIZE 0.05
#define MAX_TEAPOT_SIZE 0.8
#define TEAPOT_SCALE_SPEED 0.025;

using namespace std;

int currentDisplayObject = TEAPOT;
float teapotSize = 0.4;

/**
 * Increase the size of the teapot
 */
void increaseTeapotSize() {
    if (teapotSize >= MAX_TEAPOT_SIZE) {
        return;
    }
    teapotSize += TEAPOT_SCALE_SPEED;
    glutPostRedisplay();
}

/**
 * Decrease the size of the teapot
 */
void decreaseTeapotSize() {
    if (teapotSize <= MIN_TEAPOT_SIZE) {
        return;
    }
    teapotSize -= TEAPOT_SCALE_SPEED;
    glutPostRedisplay();
}

/**
 * Draws teapot
 */
void addTeapotToScene() {
    glutSolidTeapot(teapotSize);
}

/**
 * Draws info screen
 */
void addInfoToScene() {
    //TODO: Write some text on the screen
}

/**
 * Adds light
 */
void addLightToScene() {
    GLfloat position[] = {0.0, 0.0, 1.5, 1.0};

    glPushMatrix();
    glRotated((GLdouble) 180, 0.0, 1.0, 0.0);
    glRotated(0.0, 1.0, 0.0, 0.0);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glTranslated(0.0, 0.0, 1.5);
    glDisable(GL_LIGHTING);
    glColor3f(0.0, 1.0, 1.0);
    glutWireCube(0.1);
    glEnable(GL_LIGHTING);
    glPopMatrix();
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

    addLightToScene();

    if (currentDisplayObject == TEAPOT) {
        addTeapotToScene();
    } else {
        addInfoToScene();
    }
    //glFlush();
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
 * Callback for glutKeyboardFunc
 * This function will be called each time user press a keyboard button
 */
void keyPressHandler(unsigned char key, int xmouse, int ymouse) {
    (void)xmouse;
    (void)ymouse;
    switch (key) {
        case 27: // Escape key
            cout << "Escape pressed. Exiting...\n";
            exit(0);
        case 'b': // Make teapot bigger
            if (currentDisplayObject == TEAPOT) {
                cout << "Key 'b' pressed. Increasing teapot size...\n";
                increaseTeapotSize();
            } else {
                cout << "Key 'b' pressed. You are not on the teapot screen. Doing nothing.\n";
            }
            break;
        case 's': // Make teapot smaller
            cout << "Key 's' pressed. Trying to make teapot smaller...\n";
            if (currentDisplayObject == TEAPOT) {
                cout << "Key 's' pressed. Decreasing teapot size...\n";
                decreaseTeapotSize();
            } else {
                cout << "Key 's' pressed. You are not on the teapot screen. Doing nothing.\n";
            }
            break;
        default:
            cout << "Key pressed. There is no action set for that key. Code = " << key << ".\n";
            break;
    }
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

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(draw); // Set the redraw function
    glutWindowStatusFunc(windowStatusHandler); // Used to redraw when window status is changed:
                                               // window shown, resize, etc.
    glutKeyboardFunc(keyPressHandler);

    // Context menu
    glutCreateMenu(menuItemClickHandler);
    glutAddMenuEntry("Teapot", TEAPOT);
    glutAddMenuEntry("Developer info", INFO_SCREEN);
    glutAddMenuEntry("Quit", QUIT);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();

    return 0;
}
