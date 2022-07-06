#include "perlin/perlin.h"
#include "vec2/vec2.h"
#include "particle/particle.h"
#include <GL/freeglut.h>
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

// https: //
// stackoverflow.com/questions/3417837/what-is-the-best-way-to-suppress-a-unused-variable-x-warning
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

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

#define PARTICLE_COUNT 10000

int seed = 0;
float inc = 1;
int scale = 2;
int cols, rows;
float zoff = 0;
particle_t **particles;
vec2 *flow_field;

void draw_timer() {
    glutPostRedisplay();
    glutTimerFunc(ONE_SECOND_IN_MILLISECONDS / REFRESH_RATE, draw_timer, 0);
}

void handle_mouse_input(int button, int state, int x, int y) {
    if (state == GLUT_UP)
        return;

    if (button == GLUT_LEFT_BUTTON) {
        glClearColor(1, 1, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    glutPostRedisplay();
}


void display() {
    float yoff = 0;
    for (int y = 0; y < rows; y++) {
        float xoff = 0;

        for (int x = 0; x < cols; x++) {
            int index = x + y * cols;
            float a = perlin3d(xoff, yoff, zoff, 0.1, 4) * (2 * M_PI);
            vec2 v = vec2_create(cos(a), sin(a));

            // glColor3f(0.5, 0.5, 0.5);
            // glBegin(GL_LINES);
            // glVertex2f(x * scale, y * scale);
            // glVertex2f(x * scale + (v.x * scale), y * scale + (v.y * scale));
            // glEnd();

            v.x = v.x * 0.5 / 1;
            v.y = v.y * 0.5 / 1;
            flow_field[index] = v;

            xoff += inc;
        }

        yoff += inc;
    }

    zoff += 0.1;

    glColor4f(0, 0, 0, 0.01);
    for (int i = 0; i < PARTICLE_COUNT; i++) {
        particle_follow(particles[i], flow_field, cols, scale);
        particle_update(particles[i]);
        particle_show(particles[i]);
        particle_wrap_around(particles[i], WINDOW_WIDTH, WINDOW_HEIGHT);
    }

    glutSwapBuffers();
}

int main(int argc, char **argv) {
    srand(time(NULL));

    // Window initialization
    glutInit(&argc, argv);
    glutSetOption(GLUT_MULTISAMPLE, 16);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH |
                        GLUT_MULTISAMPLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    int window = glutCreateWindow("Perlin noise");

    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    struct timeval t;
    gettimeofday(&t, NULL);
    seed = t.tv_usec;

    particles = malloc(PARTICLE_COUNT * sizeof(particle_t *));
    for (int i = 0; i < PARTICLE_COUNT; i++)
        particles[i] = particle_create();

    cols = (int)(WINDOW_WIDTH / scale);
    rows = (int)(WINDOW_HEIGHT / scale);

    flow_field = malloc((cols * rows) * sizeof(vec2));

    glutDisplayFunc(display);
    glutMouseFunc(handle_mouse_input);
    glutTimerFunc(ONE_SECOND_IN_MILLISECONDS / REFRESH_RATE, draw_timer, 0);

    glutMainLoop();

    // Object destroy
    glutDestroyWindow(window);
    for (int i = 0; i < PARTICLE_COUNT; i++)
        free(particles[i]);
    free(particles);
    return EXIT_SUCCESS;
}
