/**
 * GLUT Teapot
 * A simple GLUT program that draws a teapot and an info screen.
 */
#include <iostream>
#include <stdarg.h>
#include <GL/glut.h>

// Context menu indexes
#define TEAPOT 0
#define INFO_SCREEN 1
#define QUIT 2

// Teapot size/scale settings
#define INITIAL_TEAPOT_SIZE 0.4
#define MIN_TEAPOT_SIZE 0.05
#define MAX_TEAPOT_SIZE 0.8
#define TEAPOT_SCALE_SPEED 0.025;

using namespace std;

int currentDisplayObject = TEAPOT;      // current screen index saved here
float teapotSize = INITIAL_TEAPOT_SIZE; // current teapot size

// Rotating the scene with mouse
bool isMouseDown = false;
float xRotate = 0.0f;
float yRotate = 0.0f;
int lastMouseXPosition;
int lastMouseYPosition;

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
 * A function wrapper for printing text on the screen using only one line of code
 */
void output(GLfloat x, GLfloat y, const char *format,...) {
    va_list args;
    char buffer[200], *p;

    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);
    glPushMatrix();
    glTranslatef(x, y, 0);
    for (p = buffer; *p; p++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
    }
    glPopMatrix();
}

/**
 * Draws info screen
 */
void addInfoToScene() {
    glPushMatrix();
    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    gluOrtho2D(0, 3000, 0, 3000);
    glMatrixMode(GL_MODELVIEW);

    output(80, 2800, "GLUT Teapot");
    output(80, 2500, "Developer:");
    output(80, 2350, "Andrew Surzhynskyi");
    output(80, 2050, "Task text:");
    output(80, 1900, "Write a program in C++ language (using");
    output(80, 1750, "functions of a glut.h library) that allow");
    output(80, 1600, "user to scale a figure (teapot) via");
    output(80, 1450, "pressing 'b' and 's' keys. Provide the");
    output(80, 1300, "user with necessary information");
    output(80, 1150, "(developers surnames and current task),");
    output(80, 1000, "exit the program upon pressing the Escape");
    output(80, 850,  "key.");

    glPopAttrib();
    glPopMatrix();
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
        glRotatef(xRotate, 0.0f, 1.0f, 0.0f);
        glRotatef(yRotate, 1.0f, 0.0f, 0.0f);
        addTeapotToScene();
    } else {
        addInfoToScene();
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
 * Callback for glutMotionFunc
 * This function will be called each time user the mouse cursor position
 */
void mouseMoveHandler(int x, int y) {
    if (!isMouseDown) {
        return;
    }

    xRotate += lastMouseXPosition - x;
    yRotate += lastMouseYPosition - y;
    lastMouseXPosition = x;
    lastMouseYPosition = y;

    glutPostRedisplay();
}

/**
 * Callback for glutMouseFunc
 * This function will be called each time user changes a mouse button state (hold down, release)
 */
void mouseButtonActionHandler(int button, int state, int x, int y) {
    if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN || currentDisplayObject != TEAPOT) {
        isMouseDown = false;
        return;
    }

    isMouseDown = true;
    lastMouseXPosition = x;
    lastMouseYPosition = y;
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

    // Rotating the scene with mouse
    glutMouseFunc(mouseButtonActionHandler);
    glutMotionFunc(mouseMoveHandler);

    // Context menu
    glutCreateMenu(menuItemClickHandler);
    glutAddMenuEntry("Teapot", TEAPOT);
    glutAddMenuEntry("Developer info", INFO_SCREEN);
    glutAddMenuEntry("Quit", QUIT);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();

    return 0;
}
