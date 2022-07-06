#include "perlin/perlin.h"
#include <GL/freeglut.h>
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>

// https://stackoverflow.com/questions/3417837/what-is-the-best-way-to-suppress-a-unused-variable-x-warning
#ifdef UNUSED
#elif defined(__GNUC__)
#define UNUSED(x) UNUSED_##x __attribute__((unused))
#elif defined(__LCLINT__)
#define UNUSED(x) /*@unused@*/ x
#else
#define UNUSED(x) x
#endif

#define ONE_SECOND_IN_MILLISECONDS 1000
#define REFRESH_RATE 60

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

float inc = 0.1;

void draw_timer() {
    glutPostRedisplay();
    glutTimerFunc(ONE_SECOND_IN_MILLISECONDS / REFRESH_RATE, draw_timer, 0);
}

void display() {
    glClearColor(0.2, 0.2, 0.2, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POINTS);
    float yoff = 0;
    for (int y = 0; y < WINDOW_HEIGHT; y++) {
        float xoff = 0;

        for (int x = 0; x < WINDOW_WIDTH; x++) {
            float b = perlin2d(xoff, yoff, 0.1, 4);
            glColor3f(b, b, b);
            glVertex2f(x, y);
            xoff += inc;
        }

        yoff += inc;
    }
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    // Window initialization
    glutInit(&argc, argv);
    glutSetOption(GLUT_MULTISAMPLE, 16);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    int window = glutCreateWindow("Perlin noise");

    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    struct timeval t;
    gettimeofday(&t, NULL);
    pseed(t.tv_usec);
    glutDisplayFunc(display);
    glutTimerFunc(ONE_SECOND_IN_MILLISECONDS / REFRESH_RATE, draw_timer, 0);

    glutMainLoop();

    // Object destroy
    glutDestroyWindow(window);
    return EXIT_SUCCESS;
}
