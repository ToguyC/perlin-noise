#include "particle.h"
#include "../utilities/utilities.h"
#include <stdio.h>

particle_t *particle_create() {
    particle_t *new = malloc(sizeof(particle_t));

    new->pos = vec2_create(rand() % 1200, rand() % 800);
    new->vel = vec2_create_zero();
    new->acc = vec2_create_zero();
    new->h = 0;

    new->prev.x = new->pos.x;
    new->prev.y = new->pos.y;

    return new;
}

void particle_update(particle_t *p) {
    p->vel = vec2_add(p->vel, p->acc);
    if (vec2_norm(p->vel) > 4) {
        p->vel.x = p->vel.x * 4 / vec2_norm(p->vel);
        p->vel.y = p->vel.y * 4 / vec2_norm(p->vel);
    }
    p->prev = p->pos;
    p->pos = vec2_add(p->pos, p->vel);
    p->acc = vec2_mul(p->acc, 0);
}

void particle_apply_force(particle_t *p, vec2 f) {
    p->acc = vec2_add(p->acc, f);
}

void particle_show(particle_t *p) {
    rgb_t rgb = hsv2rgb(p->h, 100, 100);
    p->h += 0.5;
    if (p->h >= 360)
        p->h = 0;

    glColor4f(rgb.R, rgb.G, rgb.B, 0.05);
    glBegin(GL_LINES);
    glVertex2d(p->pos.x, p->pos.y);
    glVertex2d(p->prev.x, p->prev.y);
    glEnd();
}

void particle_wrap_around(particle_t *p, int width, int height) {
    if (p->pos.x >= width)
        p->pos.x = 1;
    if (p->pos.x <= 0)
        p->pos.x = width - 1;
    if (p->pos.y >= height)
        p->pos.y = 1;
    if (p->pos.y <= 0)
        p->pos.y = height - 1;
}

void particle_follow(particle_t *p, vec2 *flow_field, int cols, int scl) {
    int x = (int)(p->pos.x / scl);
    int y = (int)(p->pos.y / scl);
    int index = x + y * cols;

    vec2 force = flow_field[index];
    particle_apply_force(p, force);
}
