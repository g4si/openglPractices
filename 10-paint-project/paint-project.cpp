// lesser version of windows paint 

#include <GL/glut.h>
#include <vector>
#include <utility>
#include <string>
#include <iostream>
#include <cmath> // For sqrt and trigonometric functions

struct Point {
    float x, y;
    Point(float px, float py) : x(px), y(py) {}
};

struct PenStroke {
    std::vector<Point> points;
    float color[3]; // Color of the stroke
    PenStroke(const float* c) {
        color[0] = c[0];
        color[1] = c[1];
        color[2] = c[2];
    }
};

// Structure to hold shapes (lines, rectangles, circles)
struct Shape {
    float startX, startY, endX, endY;
    int tool;
    float color[3]; // Color of the shape
    Shape(float sx, float sy, float ex, float ey, int t, const float* c) : startX(sx), startY(sy), endX(ex), endY(ey), tool(t) {
        color[0] = c[0];
        color[1] = c[1];
        color[2] = c[2];
    }
};

std::vector<PenStroke> penStrokes;
std::vector<Shape> shapes;
std::vector<Shape> history;
std::vector<PenStroke> penHistory; // History stack for pen strokes

int currentTool = 0; // 0: Pen, 1: Line, 2: Rectangle, 3: Circle
bool isMousePressed = false;
float startX, startY; // start position for shapes
float tempEndX, tempEndY; // temporary end position for interactive drawing

const int buttonHeight = 50;
const int buttonWidth = 100;
const int numButtons = 5; // Number of tools
const char* buttonLabels[] = { "Pen", "Line", "Rect", "Circle", "Undo" };

const int paletteSize = 5;
float colors[paletteSize][3] = {
    {0.0f, 0.0f, 0.0f}, 
    {1.0f, 0.0f, 0.0f}, 
    {0.0f, 1.0f, 0.0f}, 
    {0.0f, 0.0f, 1.0f}, 
    {1.0f, 1.0f, 0.0f}  
};
int currentColorIndex = 0;

void display();

// rectangle 
void drawButton(float x, float y, float width, float height, const char* label, bool active) {
    glColor3f(active ? 0.7f : 0.5f, 0.5f, 0.5f);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(x + 10, y + height / 2 - 5);
    for (const char* c = label; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

void drawPalette() {
    for (int i = 0; i < paletteSize; i++) {
        glColor3f(colors[i][0], colors[i][1], colors[i][2]);
        glBegin(GL_QUADS);
        glVertex2f(500 + i * 50, 0);
        glVertex2f(500 + (i + 1) * 50, 0);
        glVertex2f(500 + (i + 1) * 50, buttonHeight);
        glVertex2f(500 + i * 50, buttonHeight);
        glEnd();

        if (i == currentColorIndex) {
            glColor3f(1.0, 1.0, 1.0);
            glBegin(GL_LINE_LOOP);
            glVertex2f(500 + i * 50, 0);
            glVertex2f(500 + (i + 1) * 50, 0);
            glVertex2f(500 + (i + 1) * 50, buttonHeight);
            glVertex2f(500 + i * 50, buttonHeight);
            glEnd();
        }
    }
}

void drawUI() {
    for (int i = 0; i < numButtons; i++) {
        drawButton(i * buttonWidth, 0, buttonWidth, buttonHeight, buttonLabels[i], currentTool == i);
    }
    drawPalette();
}

void drawCanvas() {
    // Draw pen strokes
    for (const auto& stroke : penStrokes) {
        glColor3f(stroke.color[0], stroke.color[1], stroke.color[2]);
        glBegin(GL_LINE_STRIP);
        for (const auto& point : stroke.points) {
            glVertex2f(point.x, point.y);
        }
        glEnd();
    }

    // draw shapes
    for (const auto& shape : shapes) {
        glColor3f(shape.color[0], shape.color[1], shape.color[2]);
        switch (shape.tool) {
        case 1: // line
            glBegin(GL_LINES);
            glVertex2f(shape.startX, shape.startY);
            glVertex2f(shape.endX, shape.endY);
            glEnd();
            break;
        case 2: // rectangle
            glBegin(GL_LINE_LOOP);
            glVertex2f(shape.startX, shape.startY);
            glVertex2f(shape.endX, shape.startY);
            glVertex2f(shape.endX, shape.endY);
            glVertex2f(shape.startX, shape.endY);
            glEnd();
            break;
        case 3: { // circle
            float dx = shape.endX - shape.startX;
            float dy = shape.endY - shape.startY;
            float radius = sqrt(dx * dx + dy * dy);
            glBegin(GL_LINE_LOOP);
            for (int i = 0; i < 360; i++) {
                float angle = i * 3.14159 / 180;
                glVertex2f(shape.startX + cos(angle) * radius, shape.startY + sin(angle) * radius);
            }
            glEnd();
            break;
        }
        }
    }

    // Draw shape if mouse is pressed
    if (isMousePressed && currentTool != 0) {
        glColor3f(colors[currentColorIndex][0], colors[currentColorIndex][1], colors[currentColorIndex][2]); // Temporary shape color
        switch (currentTool) {
        case 1: // Line
            glBegin(GL_LINES);
            glVertex2f(startX, startY);
            glVertex2f(tempEndX, tempEndY);
            glEnd();
            break;
        case 2: // Rectangle
            glBegin(GL_LINE_LOOP);
            glVertex2f(startX, startY);
            glVertex2f(tempEndX, startY);
            glVertex2f(tempEndX, tempEndY);
            glVertex2f(startX, tempEndY);
            glEnd();
            break;
        case 3: { // Circle
            float dx = tempEndX - startX;
            float dy = tempEndY - startY;
            float radius = sqrt(dx * dx + dy * dy);
            glBegin(GL_LINE_LOOP);
            for (int i = 0; i < 360; i++) {
                float angle = i * 3.14159 / 180;
                glVertex2f(startX + cos(angle) * radius, startY + sin(angle) * radius);
            }
            glEnd();
            break;
        }
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawUI();

    glPushMatrix();
    glTranslatef(0, buttonHeight, 0);
    drawCanvas();
    glPopMatrix();

    glFlush();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, width, height, 0.0);
    glMatrixMode(GL_MODELVIEW);
}

void undoLastShape() {
    if (!shapes.empty()) {
        history.push_back(shapes.back());
        shapes.pop_back();
    }
    else if (!penStrokes.empty()) {
        penHistory.push_back(penStrokes.back());
        penStrokes.pop_back();
    }
}

void mouse(int button, int state, int x, int y) {
    if (y <= buttonHeight) { // Click on UI
        if (state == GLUT_DOWN) {
            int buttonIndex = x / buttonWidth;
            if (buttonIndex >= 0 && buttonIndex < numButtons) {
                if (buttonIndex == 4) { // Undo button
                    undoLastShape();
                }
                else {
                    currentTool = buttonIndex;
                }
            }
            else if (x >= 500 && x < 500 + paletteSize * 50) { // Color palette
                int colorIndex = (x - 500) / 50;
                if (colorIndex >= 0 && colorIndex < paletteSize) {
                    currentColorIndex = colorIndex;
                }
            }
        }
    }
    else { // click on canvas
        if (button == GLUT_LEFT_BUTTON) {
            if (state == GLUT_DOWN) {
                isMousePressed = true;
                startX = x;
                startY = y - buttonHeight;
                tempEndX = startX;
                tempEndY = startY;

                if (currentTool == 0) {
                    penStrokes.emplace_back(colors[currentColorIndex]);
                    penStrokes.back().points.emplace_back(startX, startY);
                }
            }
            else if (state == GLUT_UP) {
                isMousePressed = false;
                float endX = x;
                float endY = y - buttonHeight;
                if (currentTool != 0) { // Add shape to shapes vector
                    shapes.push_back(Shape(startX, startY, endX, endY, currentTool, colors[currentColorIndex]));
                }
            }
        }
    }
    glutPostRedisplay();
}

void motion(int x, int y) {
    if (isMousePressed && y > buttonHeight) {
        tempEndX = x;
        tempEndY = y - buttonHeight;

        if (currentTool == 0) { // Pen tool
            if (!penStrokes.empty()) {
                penStrokes.back().points.emplace_back(tempEndX, tempEndY);
            }
        }
    }
    glutPostRedisplay();
}


void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    glColor3f(0.0, 0.0, 0.0);          // Black drawing color
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL Paint Program");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    glutMainLoop();
    return 0;
}
