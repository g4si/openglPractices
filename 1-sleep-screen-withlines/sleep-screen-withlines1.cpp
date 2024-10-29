//#ifdef __APPLE__
//#  include <GL/glew.h>
//#  include <GL/freeglut.h>
//#  include <OpenGL/glext.h>
//#else
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
//#pragma comment(lib, "glew32.lib") 
//#endif
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;
#define M_PI 3.14159265358979323846

// Global variables to control animations
float trianglePosX = 1;
float trianglePosY = -0.5;
float triangleSpeedX = 0.005;
float triangleSpeedY = 0.005;

float squarePosX = -1;
float squarePosY = 0.5;
float squareSpeedX = 0.005;
float squareSpeedY = 0.005;

float linePosX = 0.0;
float linePosY = 0.0;
float lineSpeedX = 0.005;
float lineSpeedY = 0.005;

float angle = 0; // for color
float shapeSize = 0.3;

// gwt random direction (mostly when shape want to go out of window)
void randomizeDirection(float& speedX, float& speedY) {
    float angle = rand() % 360 * (M_PI / 180.0); // random angle in radians
    speedX = 0.005 * cos(angle); // random new X speed
    speedY = 0.005 * sin(angle); // random new Y speed
}

void init()
{
    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glClearColor(0, 0, 0, 0);
    glutInitWindowSize(1400, 800);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Sleep Mode Animation");
    srand(time(0));
}

void drawLine()
{
    glBegin(GL_LINES);
        glColor3f(1, fabs(sin(angle)), fabs(cos(angle)));
        glVertex2f(linePosX - 0.4, linePosY - 0.4);
        glVertex2f(linePosX + 0.4, linePosY + 0.4);
    glEnd();
}

void drawSquare()
{
    glBegin(GL_QUADS);
        glColor3f(fabs(cos(angle)), fabs(sin(angle)), 1);
        glVertex2f(squarePosX + shapeSize, squarePosY - shapeSize);
        glVertex2f(squarePosX - shapeSize, squarePosY - shapeSize);
        glVertex2f(squarePosX - shapeSize, squarePosY + shapeSize);
        glVertex2f(squarePosX + shapeSize, squarePosY + shapeSize);
    glEnd();
}

void drawTriangle()
{
    glBegin(GL_TRIANGLES);
        glColor3f(fabs(sin(angle)), 1, fabs(cos(angle)));
        glVertex2f(trianglePosX - shapeSize, trianglePosY - shapeSize);
        glVertex2f(trianglePosX + shapeSize, trianglePosY - shapeSize);
        glVertex2f(trianglePosX, trianglePosY + shapeSize);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawSquare();
    drawTriangle();
    drawLine();
    glutSwapBuffers();
}

void update(int val)
{
    angle += 0.01;

    // Update square
    squarePosX += squareSpeedX;
    squarePosY += squareSpeedY;
    if (squarePosX < -1 || squarePosX > 1 || squarePosY < -1 || squarePosY > 1) {
        randomizeDirection(squareSpeedX, squareSpeedY);
        // objects doesn't go beyond bounds '*'
        if (squarePosX < -1) squarePosX = -1;
        if (squarePosX > 1) squarePosX = 1;
        if (squarePosY < -1) squarePosY = -1;
        if (squarePosY > 1) squarePosY = 1;
    }

    // Update triangle
    trianglePosX += triangleSpeedX;
    trianglePosY += triangleSpeedY;
    if (trianglePosX < -1 || trianglePosX > 1 || trianglePosY < -1 || trianglePosY > 1) {
        randomizeDirection(triangleSpeedX, triangleSpeedY);
        // '*'
        if (trianglePosX < -1) trianglePosX = -1;
        if (trianglePosX > 1) trianglePosX = 1;
        if (trianglePosY < -1) trianglePosY = -1;
        if (trianglePosY > 1) trianglePosY = 1;
    }

    // update line
    linePosX += lineSpeedX;
    linePosY += lineSpeedY;
    if (linePosX < -1 || linePosX > 1 || linePosY < -1 || linePosY > 1) {
        randomizeDirection(lineSpeedX, lineSpeedY);
        // '*'
        if (linePosX < -1) linePosX = -1;
        if (linePosX > 1) linePosX = 1;
        if (linePosY < -1) linePosY = -1;
        if (linePosY > 1) linePosY = 1;
    }

    glutPostRedisplay(); // calls display function again
    glutTimerFunc(20, update, 0);
}

void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
    default:
        break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    init();
    glutDisplayFunc(display);
    update(0);
    glutKeyboardFunc(keyInput);
    glutMainLoop();
    return 0;
}
