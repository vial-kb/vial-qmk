#ifndef RNDGEN_H
#define RNDGEN_H

typedef struct {
    uint8_t x;
    uint8_t y;
    uint8_t z;
    uint8_t a;
    uint8_t t;
} Rndgen;

void init_rng(Rndgen *r, uint8_t x, uint8_t y, uint8_t z, uint8_t a, uint8_t t);
uint8_t calc_rng(Rndgen *r, uint16_t p);

#endif // RNDGEN_H
