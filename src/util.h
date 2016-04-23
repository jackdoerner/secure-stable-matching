#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>
#include <obliv_common.h>

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

uint64_t current_timestamp();
uint32_t rand_range(uint32_t, uint32_t);

#endif

