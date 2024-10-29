// Circle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#ifdef __APPLE__
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#pragma comment(lib, "glew32.lib") 
#endif
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;
#define M_PI 3.14159265358979323846
float r = 0.5;
float tempR = 0.0;

float circlePosX = 0.0;
float circlePosY = 0.0;
float changer = -0.001;
int polygonSides = 50;


void init()
{
    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glClearColor(0, 0, 0, 0);
    glutInitWindowSize(900, 900);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Sleep Mode Animation");
    srand(time(0));
}

void drawCircle()
{
    float t = 0.0;
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINE_LOOP);
        for (int i = 0; i < polygonSides; i++)
        {
            glColor3f((float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX);
            glVertex3f(circlePosX + tempR * cos(t), circlePosY + tempR * sin(t), 0.0);
            t += 2 * M_PI / polygonSides;
        }
    glEnd();
    glFlush();
}

void update(int val) 
{
    if (tempR <= 0.0 || tempR >= r)
        changer *= (-1);

    tempR += changer;
    glutPostRedisplay();
    glutTimerFunc(5, update, 0);
}

void keyInput(unsigned char key, int x, int y)
{
    if (key == 27)
        exit(0);
}

void display()
{
    drawCircle();
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    init();
    glutDisplayFunc(display);
    update(0);
    glutKeyboardFunc(keyInput);
    glutMainLoop();
    return 0;
}