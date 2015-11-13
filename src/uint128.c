#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "uint128.h"


// code from http://stackoverflow.com/questions/11656241/how-to-print-uint128-t-number-using-gcc

/*
** Using documented GCC type unsigned __int128 instead of undocumented
** obsolescent typedef name __uint128_t.  Works with GCC 4.7.1 but not
** GCC 4.1.2 (but __uint128_t works with GCC 4.1.2) on Mac OS X 10.7.4.
*/


/*      UINT64_MAX 18446744073709551615ULL */
#define P10_UINT64 10000000000000000000ULL   /* 19 zeroes */
#define E10_UINT64 19

#define STRINGIZER(x)   # x
#define TO_STRING(x)    STRINGIZER(x)

struct uint128_t {
    unsigned __int128 val;
};

uint128_t * GetTimeStamp128() {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    uint128_t * result = malloc(sizeof(uint128_t));
    result->val = tv.tv_sec*(unsigned __int128)1000000+tv.tv_usec;
    return result;
}

uint128_t * uint128_new() {
    uint128_t * result = malloc(sizeof(uint128_t));
    result->val = 0;
    return result;
}

uint128_t * uint128_add(uint128_t * in1, uint128_t * in2) {
    uint128_t * result = malloc(sizeof(uint128_t));
    result->val = in1->val + in2->val;
    return result;
}

uint128_t * uint128_subtract(uint128_t * in1, uint128_t * in2) {
    uint128_t * result = malloc(sizeof(uint128_t));
    result->val = in1->val - in2->val;
    return result;
}

int print_uint128(FILE * io, uint128_t * u128) {
    int rc;
    if (u128->val > UINT64_MAX)
    {   
        uint128_t leading;
        leading.val = u128->val / P10_UINT64;
        uint64_t  trailing = u128->val % P10_UINT64;
        rc = print_uint128(io, &leading);
        rc += fprintf(io, "%." TO_STRING(E10_UINT64) PRIu64, trailing);
    }
    else
    {
        uint64_t u64 = u128->val;
        rc = fprintf(io, "%" PRIu64, u64);
    }
    return rc;
}