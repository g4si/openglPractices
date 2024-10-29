// shapeChoice.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <cstdlib>
#include <cmath>
#include <iostream>

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

#define PI 3.14159265358979324
float shapePosX = 0.0;
float shapePosY = 0.0;
float shapeSize = 0.5;
float angleForColor = 0;
char choice = 's';
int smootherCircle = 20;

using namespace std;


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

void drawSquare()
{
    glBegin(GL_QUADS);
        glColor3f(fabs(cos(angleForColor)), fabs(sin(angleForColor)), 1);
        glVertex2f(shapePosX + shapeSize, shapePosY - shapeSize);
        glVertex2f(shapePosX - shapeSize, shapePosY - shapeSize);
        glVertex2f(shapePosX - shapeSize, shapePosY + shapeSize);
        glVertex2f(shapePosX + shapeSize, shapePosY + shapeSize);
    glEnd();
}

void drawCircle()
{
    float t = 0; // Angle parameter.
    glClear(GL_COLOR_BUFFER_BIT);

    //glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
        for (int i = 0; i < smootherCircle; ++i)
        {
            glColor3f((float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX);
            glVertex3f(shapePosX + shapeSize * cos(t), shapePosY + shapeSize * sin(t), 0.0);
            t += 2 * PI / smootherCircle;
        }
    glEnd();
}

void drawTriangle()
{
    glBegin(GL_TRIANGLES);
    glColor3f(fabs(sin(angleForColor)), 1, fabs(cos(angleForColor)));
    glVertex2f(shapePosX - shapeSize, shapePosY - shapeSize);
    glVertex2f(shapePosX + shapeSize, shapePosY - shapeSize);
    glVertex2f(shapePosX, shapePosY + shapeSize);
    glEnd();
}

void display() 
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (choice == 's')
        drawSquare();
    else if (choice == 'c')
        drawCircle();
    else if (choice == 't')
        drawTriangle();
    glFlush();
}

void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 115:
    {
        choice = 's';
        glutPostRedisplay();
        break;
    }
    case 116:
    {
        choice = 't';
        glutPostRedisplay();
        break;
    }
    case 99:
    {
        choice = 'c';
        glutPostRedisplay();
        break;
    }
    case 43:
    {
        if (shapeSize < 0.98) {
            shapeSize += 0.01;
            glutPostRedisplay();
        }
        break;
    }
    case 45:
    {
        if (shapeSize > 0.01) {
            shapeSize -= 0.01;
            glutPostRedisplay();
        }
        break;
    }
    case 27:
    {
        exit(0);
    }
    default:
    {
        break;
    }
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    init();
    glutDisplayFunc(display);
    //update(0);
    glutKeyboardFunc(keyInput);
    glutMainLoop();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
