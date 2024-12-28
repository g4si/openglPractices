#include <GL/glut.h>
#include <vector>

struct Line {
    int startX, startY, endX, endY;
    float thickness;
    bool locked;
};

std::vector<Line> lines;

Line currentLine;

bool isDrawing = false;
bool canAdjustThickness = false;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    for (const auto& line : lines) {
        glLineWidth(line.thickness);
        glColor3f(1.0f, 1.0f, 1.0f); // White color
        glBegin(GL_LINES);
        glVertex2f(line.startX, line.startY);
        glVertex2f(line.endX, line.endY);
        glEnd();
    }

    if (isDrawing || canAdjustThickness) {
        glLineWidth(currentLine.thickness);
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINES);
        glVertex2f(currentLine.startX, currentLine.startY);
        glVertex2f(currentLine.endX, currentLine.endY);
        glEnd();
    }

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
    int flippedY = glutGet(GLUT_WINDOW_HEIGHT) - y; // flip y-axis

    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN && !isDrawing && !canAdjustThickness) {
            isDrawing = true;
            currentLine.startX = x;
            currentLine.startY = flippedY;
            currentLine.endX = x;
            currentLine.endY = flippedY;
            currentLine.thickness = 1.0f;
            currentLine.locked = false;
        }
        else if (state == GLUT_UP && isDrawing) {
            isDrawing = false;
            canAdjustThickness = true;
        }
        else if (state == GLUT_DOWN && canAdjustThickness) {
            currentLine.locked = true;
            lines.push_back(currentLine);
            canAdjustThickness = false;
        }
    }
    else if (canAdjustThickness && (button == 3 || button == 4)) {
        if (button == 3 && currentLine.thickness < 10.0f) { // scroll up
            currentLine.thickness += 1.0f;
        }
        else if (button == 4 && currentLine.thickness > 1.0f) { // scroll down
            currentLine.thickness -= 1.0f;
        }
    }

    glutPostRedisplay();
}

void motion(int x, int y) {
    if (isDrawing) {
        currentLine.endX = x;
        currentLine.endY = glutGet(GLUT_WINDOW_HEIGHT) - y; // flip y-axis
        glutPostRedisplay();
    }
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Interactive Line Drawing");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}
