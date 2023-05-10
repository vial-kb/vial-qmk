#include "rndgen.h"

void init_rng(Rndgen *r, uint8_t x, uint8_t y, uint8_t z, uint8_t a, uint8_t t) {
    r->x = x;
    r->y = y;
    r->z = z;
    r->a = a;
    r->t = t;

    for (int i = 0; i < 10; i++) {
        calc_rng(r, 1);
    }
}

uint8_t calc_rng(Rndgen *r, uint16_t p) {
    // p contains a timer variable which is alternative to a random number
    r->y = p;
    r->z = p;

    r->t = r->x ^ (r->x << 4);

    r->x = r->y;
    r->y = r->z;
    r->z = r->a;
    r->a = r->z ^ r->t ^ (r->z >> 1) ^ (r->t << 1);

    return r->a;
}

