#include <stdlib.h>
#include <GL/glut.h>
#include "./eom.hpp"


constexpr double delta_t = 10.0;
EOM eom(1.0, 2.0, 0.7, 5.0, 1.0 / delta_t, 10000);

GLfloat axis[4][2] = {
        {0.0, 0.0},
        {0.0, 0.0},
        {0.0, 0.0},
        {0.0, 0.0}
};

GLfloat g[3] = {
    0.0, 0.0, 0.0
};

void gtoAxis(GLfloat x, GLfloat y, GLfloat size) {
    axis[0][0] = x - (size / 2);
    axis[0][1] = y - (size / 2);
    axis[1][0] = x + (size / 2);
    axis[1][1] = y - (size / 2);
    axis[2][0] = x + (size / 2);
    axis[2][1] = y + (size / 2);
    axis[3][0] = x - (size / 2);
    axis[3][1] = y + (size / 2);

    for (int i{}; i < 4; ++i) {
        for (int j{}; j < 2; ++j) {
            if (axis[i][j] >= 0.99) {
                axis[i][j] = 0.99;
            }
            else if (axis[i][j] < -0.99) {
                axis[i][j] = -0.99;
            }
        }
    }

    return;
}

void timer(int value) {
    double y = eom.calculate();
    if (y == -1.0) {
        printf("%f\n", y);
        return;
    }
    printf("%f\n", y);

    for (int i{}; i < 3; ++i) {
        g[i] = y / 5;
    }

    glutPostRedisplay();
    glutTimerFunc(delta_t, timer, 0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glColor3d(1.0, 0.0, 0.0);
    
    gtoAxis(g[0], g[1], g[2]);

    glBegin(GL_LINE_LOOP);
    for (int i{}; i < 4; ++i) {
        glVertex2d(axis[i][0], axis[i][1]);
    }
    glEnd();

    glBegin(GL_LINE_LOOP);
    for (int i{}; i < 4; ++i) {
        glVertex2d(axis[i][0]+0.1, axis[i][1]-0.1);
    }
    glEnd();

    glFlush();
}

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    init();
    glutTimerFunc(delta_t, timer, 0);
    glutMainLoop();
    return 0;
}
