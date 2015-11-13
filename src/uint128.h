#ifndef UINT128_H
#define UINT128_H

#include <inttypes.h>

typedef struct uint128_t uint128_t;

uint128_t * GetTimeStamp128();

uint128_t * uint128_new();
uint128_t * uint128_add(uint128_t *, uint128_t *);
uint128_t * uint128_subtract(uint128_t *, uint128_t *);

int print_uint128(FILE * io, uint128_t * u128);

#endif