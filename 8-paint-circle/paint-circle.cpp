#include <GL/glut.h>
#include <vector>
#include <cmath>

#define M_PI 3.14159265359

struct Circle {
    float x, y;
    float radius;
    bool locked;
    Circle(float cx, float cy, float r) : x(cx), y(cy), radius(r), locked(false) {}
};

std::vector<Circle> circles;
Circle* currentCircle = nullptr;

// Draw a circle
void drawCircle(float x, float y, float radius) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // Center
    for (int i = 0; i <= 360; ++i) {
        float angle = i * M_PI / 180.0f;
        glVertex2f(x + radius * cos(angle), y + radius * sin(angle));
    }
    glEnd();
}

// Display callback
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.7f, 0.7f);

    for (const auto& circle : circles) {
        drawCircle(circle.x, circle.y, circle.radius);
    }

    if (currentCircle && !currentCircle->locked) {
        glColor3f(0.7f, 0.0f, 0.0f);
        drawCircle(currentCircle->x, currentCircle->y, currentCircle->radius);
    }

    glutSwapBuffers();
}

// Mouse callback
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (currentCircle && !currentCircle->locked) {
            currentCircle->locked = true;
            circles.push_back(*currentCircle);
        }
        float cx = (x - 250.0f) / 250.0f;
        float cy = -(y - 250.0f) / 250.0f;
        currentCircle = new Circle(cx, cy, 0.05f);
    }

    // Handle scroll events
    if (button == 3 && state == GLUT_DOWN) { // Scroll up
        if (currentCircle && !currentCircle->locked) {
            currentCircle->radius += 0.01f;
        }
    }
    else if (button == 4 && state == GLUT_DOWN) { // Scroll down
        if (currentCircle && !currentCircle->locked) {
            currentCircle->radius -= 0.01f;
            if (currentCircle->radius < 0.01f) {
                currentCircle->radius = 0.01f;
            }
        }
    }

    glutPostRedisplay();
}


// Keyboard callback
void keyboard(unsigned char key, int x, int y) {
    if (key == 27) { // ESC key
        exit(0);
    }
}

// Initialization
void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Circle Drawer");

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);

    init();
    glutMainLoop();
    return 0;
}
