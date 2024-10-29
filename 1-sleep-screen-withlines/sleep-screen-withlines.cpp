#include <GL/glut.h>
#include <cmath>

// Global variables to control animations
float angle = 0.0f;
float squarePosX = -1.0f;
float squareSpeed = 0.005f;
float trianglePosX = 1.0f;
float triangleSpeed = 0.004f;

// Function to draw a square
void drawSquare(float x, float y, float size) {
    glBegin(GL_QUADS);
    glColor3f( fabs(cos(angle)), fabs(sin(angle) ), 1.0f);
    glVertex2f(x - size, y - size);
    glVertex2f(x + size, y - size);
    glVertex2f(x + size, y + size);
    glVertex2f(x - size, y + size);
    glEnd();
}

// Function to draw a triangle
void drawTriangle(float x, float y, float size) {
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, fabs(cos(angle)), fabs(sin(angle)));
    glVertex2f(x, y + size);
    glVertex2f(x - size, y - size);
    glVertex2f(x + size, y - size);
    glEnd();
}

// Function to update animation variables
void update(int value) {
    // Update angles for animation
    angle += 0.01f;

    // Update square position (moving back and forth)
    squarePosX += squareSpeed;
    if (squarePosX > 1.0f || squarePosX < -1.0f) {
        squareSpeed = -squareSpeed;  // Reverse direction
    }

    // Update triangle position (moving back and forth)
    trianglePosX -= triangleSpeed;
    if (trianglePosX > 1.0f || trianglePosX < -1.0f) {
        triangleSpeed = -triangleSpeed;  // Reverse direction
    }

    // Redisplay frame and register next update
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);  // 16ms for ~60fps
}

// Display function to draw the scene
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw a moving square
    drawSquare(squarePosX, 0.5f, 0.4f);

    // Draw a moving triangle
    drawTriangle(trianglePosX, -0.5f, 0.4f);

    glutSwapBuffers();  // Swap buffers for smooth animation
}

// Initialize OpenGL settings
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Set background color to black
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);  // Set 2D orthographic projection
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Simple Sleep Mode Animation");

    init();
    glutDisplayFunc(display);
    glutTimerFunc(16, update, 0);  // Call update function for animation

    glutMainLoop();
    return 0;
}
