#include <stdlib.h>
#include <GL/glut.h>
#include "./eom.hpp"
// #include "./spring.hpp"


constexpr double delta_t = 10.0;
// x, v, k, b, m, dt, n
// Spring spring(0.0, 1.0, 1.0, 1.0, 1.0 / delta_t, 10000);
EOM eom(0.0, 0.0, 0.3, 0.1, 2.5, 1.0 / delta_t, 10000);

GLfloat axis[4][2] = {
        {0.0, 0.0},
        {0.0, 0.0},
        {0.0, 0.0},
        {0.0, 0.0}
};

GLfloat g[3] = {
    0.0, 0.0, 0.5
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
        printf("Fuck! %f\n", y);
        return;
    }
    printf("%f\n", y);

    g[1] = y / -100; 
    // g[2] = y / -200;
    gtoAxis(g[0], g[1], g[2]);

    glutPostRedisplay();
    glutTimerFunc(delta_t, timer, 0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glColor3d(1.0, 0.0, 0.0);

    // born(axis[i][0], axis[i][1]);

    glBegin(GL_LINE_LOOP);
    for (int i{}; i < 4; ++i) {
        glVertex2d(axis[i][0], axis[i][1]);
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
