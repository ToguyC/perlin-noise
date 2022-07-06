#include "perlin/perlin.h"
#include "vec2/vec2.h"
#include <GL/freeglut.h>
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

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

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

int seed = 0;
float inc = 1;
int scale = 5;
int cols, rows;
float zoff = 0;

void draw_timer() {
    glutPostRedisplay();
    glutTimerFunc(ONE_SECOND_IN_MILLISECONDS / REFRESH_RATE, draw_timer, 0);
}

void display() {
    glClearColor(0.2, 0.2, 0.2, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    float yoff = 0;
    for (int y = 0; y < rows; y++) {
        float xoff = 0;

        for (int x = 0; x < cols; x++) {
            float b = perlin3d(xoff, yoff, zoff, 0.1, 4);
            glColor3f(1, 1, 1);
            float a = b * (2 * M_PI);
            vec2 v = vec2_create(cos(a), sin(a));

            glBegin(GL_LINES);
            glVertex2f(x * scale, y * scale);
            glVertex2f(x * scale + (v.x * scale), y * scale + (v.y * scale));
            glEnd();
            xoff += inc;
        }

        yoff += inc;
    }

    zoff += 0.1;

    glutSwapBuffers();
}

int main(int argc, char **argv) {
    // Window initialization
    glutInit(&argc, argv);
    glutSetOption(GLUT_MULTISAMPLE, 16);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH |
                        GLUT_MULTISAMPLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    int window = glutCreateWindow("Perlin noise");

    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    struct timeval t;
    gettimeofday(&t, NULL);
    seed = t.tv_usec;

    cols = (int)(WINDOW_WIDTH / scale);
    rows = (int)(WINDOW_HEIGHT / scale);

    glutDisplayFunc(display);
    glutTimerFunc(ONE_SECOND_IN_MILLISECONDS / REFRESH_RATE, draw_timer, 0);

    glutMainLoop();

    // Object destroy
    glutDestroyWindow(window);
    return EXIT_SUCCESS;
}

// #include <stdio.h>
// #include <time.h>
// //#include <unistd.h>
// #include "perlin/perlin.h"

// // 0123456789
// //  `'"+*0&#@
// char d[11] = " `'\"+*0&#@";

// int main() {
//     int i = 0, j = 0, c = 0, z = 0;
//     double n;
//     clock_t stall;

//     while (1) {
//         stall = clock();
//         for (i = 0; i < 50; i++) {
//             for (j = 0; j < 50; j++) {
//                 n = pnoise3d(j * 0.1, i * 0.1, z * 0.1, 0.7, 5, 12124);
//                 c = (int)((n + 1) * 4);
//                 if (c < 0)
//                     c = 0;
//                 if (c > 9)
//                     c = 9;
//                 printf("%c", d[c]);
//             }
//             printf("\n");
//         }
//         printf("\n\n");
//         z++;

//         while (clock() - stall < 100000) {
//         }
//     }

//     return 0;
// }
