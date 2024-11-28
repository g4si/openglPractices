#include <GL/glut.h>
#include <cmath>
#include <ctime>
#include <string>

const float CLOCK_RADIUS = 100.0f;
const float PI = 3.14159265358979323846f;

void drawText(float x, float y, const char* text, float angle) {
    angle = angle * 180 / PI;
    glPushMatrix();
    glTranslatef(x, y, 0.0);
    glRotatef(angle, 0.0, 0.0, 1.0);
    glScalef(0.1, 0.1, 0.1);
    for (const char* c = text; *c != '\0'; c++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    }
    glPopMatrix();
}

void drawHand(float angle, float length, float width) {
    glLineWidth(width);
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(length * cos(angle), length * sin(angle));
    glEnd();
}


void drawClockFace() {
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        float theta = i * (PI / 180);
        glVertex2f(CLOCK_RADIUS * cos(theta), CLOCK_RADIUS * sin(theta));
    }
    glEnd();

    for (int i = 1; i <= 12; i++) {
        float angle = (360 - (i * 30) + 90) * (PI / 180); // Offset by +90 degrees to place 12 at the top and clockwise
        float x = (CLOCK_RADIUS - 15) * cos(angle);
        float y = (CLOCK_RADIUS - 15) * sin(angle);
        std::string num = std::to_string(i);
        drawText(x - 5, y - 5, num.c_str(), 0); // Offset to center the numbers
    }
}

void displayClock() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    time_t now = time(0);
    struct tm currentTime;
    localtime_s(&currentTime, &now);

    int hours = currentTime.tm_hour;
    int minutes = currentTime.tm_min;
    int seconds = currentTime.tm_sec;

    float hourAngle = (360 - ((hours % 12 + minutes / 60.0f) * 30) + 90) * (PI / 180);
    float minuteAngle = (360 - ((minutes + seconds / 60.0f) * 6) + 90) * (PI / 180);
    float secondAngle = (360 - (seconds * 6) + 90) * (PI / 180);

    drawClockFace();


    glColor3f(0.8, 0.0, 0.0);
    drawHand(hourAngle, CLOCK_RADIUS * 0.4, 5.0);
    std::string hourText = std::to_string(hours % 12 == 0 ? 12 : hours % 12);
    drawText(CLOCK_RADIUS * 0.4 * cos(hourAngle), CLOCK_RADIUS * 0.4 * sin(hourAngle), hourText.c_str(), hourAngle);

    glColor3f(0.0, 0.8, 0.0);
    drawHand(minuteAngle, CLOCK_RADIUS * 0.6, 3.0);
    std::string minuteText = std::to_string(minutes);
    drawText(CLOCK_RADIUS * 0.6 * cos(minuteAngle), CLOCK_RADIUS * 0.6 * sin(minuteAngle), minuteText.c_str(), minuteAngle);


    glColor3f(0.0, 0.8, 0.8);
    drawHand(secondAngle, CLOCK_RADIUS * 0.8, 1.0);

    std::string secondText = std::to_string(seconds);
    drawText(CLOCK_RADIUS * 0.8 * cos(secondAngle), CLOCK_RADIUS * 0.8 * sin(secondAngle), secondText.c_str(), secondAngle);

    glutSwapBuffers();
}


void timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(1000, timer, 0);
}

void initializeDisplay() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-CLOCK_RADIUS - 20, CLOCK_RADIUS + 20, -CLOCK_RADIUS - 20, CLOCK_RADIUS + 20);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("OpenGL Clock");

    initializeDisplay();
    glutDisplayFunc(displayClock);
    glutTimerFunc(1000, timer, 0);

    glutMainLoop();
    return 0;
}
