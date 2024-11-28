#include <GL/glut.h>
#include <cmath>

float gravity = 0.004f;   
float initPosX = -0.9f;             
float initPosY = 0.70f;             
float velocityX = 0.01f;        
float velocityY = 0.04f;        
bool isMoving = true;

void reset() {
    initPosX = -0.9f;
    initPosY = 0.7f;
    velocityY = 0.04f;
    isMoving = true;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // ground
    glColor3f(0.0f, 0.5f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, -0.9f);
        glVertex2f(1.0f, -0.9f);
        glVertex2f(1.0f, -1.0f);
        glVertex2f(-1.0f, -1.0f);
    glEnd();

    // sphere
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(initPosX, initPosY, 0.0f);
    glutWireSphere(0.05f, 16, 10); 
    glPopMatrix();
    
    glFlush();
    
}

void update(int value) {
    if (isMoving) {
        initPosX += velocityX;
        initPosY += velocityY;

        velocityY -= gravity;

        
        if (initPosY <= -0.85f) {  
            initPosY = -0.85f;     

            velocityY = -velocityY * 0.7f;

            if (fabs(velocityY) < 0.005f) {
                isMoving = false;
            }
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void keyInput(unsigned char key, int x, int y) {
    if (key == 'r' || key == 'R') {
        reset();
    }
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);  
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Parabolic Motion of a Wireframe Sphere");
    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyInput);
    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}
