#ifndef PARTICLE_H_
#include "../vec2/vec2.h"
#include <GL/freeglut.h>
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>

typedef struct _particle_t {
    vec2 pos, prev, vel, acc;
} particle_t;

particle_t *particle_create();
void particle_update(particle_t *p);
void particle_apply_force(particle_t *p, vec2 f);
void particle_show(particle_t *p);
void particle_wrap_around(particle_t *p, int width, int height);
void particle_follow(particle_t *p, vec2 *flow_field, int cols, int scl);

#endif // !PARTICLE_H_
