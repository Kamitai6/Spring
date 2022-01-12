#include <stdlib.h>
#include <GL/glut.h>
// #include "./eom.hpp"
#include "./spring.hpp"


constexpr double delta_t = 1.0 / 10.0;
// x, v, k, b, m, dt, n
/Spring spring(delta_t, 100);
// EOM eom(0.0, 0.0, 0.3, 0.1, 2.5, 1.0 / delta_t, 10000);

GLfloat axis[4][2] = {};
GLfloat g[3] = {};

void gtoAxis(GLfloat x, GLfloat y, GLfloat size) {
    axis[0][0] = x - (size / 2);
    axis[0][1] = y - (size / 2);
    axis[1][0] = x + (size / 2);
    axis[1][1] = y - (size / 2);
    axis[2][0] = x + (size / 2);
    axis[2][1] = y + (size / 2);
    axis[3][0] = x - (size / 2);
    axis[3][1] = y + (size / 2);

    template<typename T>
    static inline T Restrain(T x, T limit) {
        return ((x)<(-limit)?(-limit):((x)>(limit)?(limit):(x)));
    }

    for (int i{}; i < 4; ++i) {
        for (int j{}; j < 2; ++j) {
            Restrain<double>(axis[i][j], 0.99);
        }
    }
    return;
}

void timer(int value) {
    auto predict = spring.calculate();
    for(auto& x : predict) {
        if (x == -1.0) {
            printf("Fuck! %f\n", x);
            return;
        }
        else {
            g[1] = x / -100;
            printf("%f\n", y);
        }
    }
    gtoAxis(g[0], g[1], g[2]);
    glutPostRedisplay();
    glutTimerFunc(delta_t, timer, 0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glColor3d(1.0, 0.0, 0.0);

    spring.showObject();

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
