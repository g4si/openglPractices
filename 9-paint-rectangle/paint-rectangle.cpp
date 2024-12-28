#include <GL/glut.h>

struct Point {
    float x, y;
};

Point startPoint, endPoint;
bool isDrawing = false;
bool isFilled = false;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (isDrawing || (startPoint.x != endPoint.x && startPoint.y != endPoint.y)) {
        if (isFilled) {
            glBegin(GL_QUADS); // Filled rectangle
        }
        else {
            glBegin(GL_LINE_LOOP); // Rectangle outline
        }
        glVertex2f(startPoint.x, startPoint.y);
        glVertex2f(startPoint.x, endPoint.y);
        glVertex2f(endPoint.x, endPoint.y);
        glVertex2f(endPoint.x, startPoint.y);
        glEnd();
    }

    glFlush();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            
            startPoint.x = (float)x / glutGet(GLUT_WINDOW_WIDTH) * 2 - 1;
            startPoint.y = 1 - (float)y / glutGet(GLUT_WINDOW_HEIGHT) * 2;
            endPoint = startPoint;
            isDrawing = true;
        }
        else if (state == GLUT_UP) {
            endPoint.x = (float)x / glutGet(GLUT_WINDOW_WIDTH) * 2 - 1;
            endPoint.y = 1 - (float)y / glutGet(GLUT_WINDOW_HEIGHT) * 2;
            isDrawing = false;
        }
    }
    else if (button == 3 && state == GLUT_DOWN) { // Scroll up
        isFilled = true;
    }
    else if (button == 4 && state == GLUT_DOWN) { // Scroll down
        isFilled = false;
    }

    glutPostRedisplay();
}

void motion(int x, int y) {
    if (isDrawing) {
        
        endPoint.x = (float)x / glutGet(GLUT_WINDOW_WIDTH) * 2 - 1;
        endPoint.y = 1 - (float)y / glutGet(GLUT_WINDOW_HEIGHT) * 2;
        glutPostRedisplay();
    }
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glColor3f(1.0f, 1.0f, 1.0f);         
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1); 
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Rectangle with Drag and Drop");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutMainLoop();

    return 0;
}
